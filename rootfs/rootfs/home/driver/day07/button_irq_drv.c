#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/irq.h>
#include <linux/interrupt.h>
#include <asm/gpio.h>
#include <plat/gpio-cfg.h>

static int major;
static struct cdev btn_cdev;
static int ispress; //1:有操作 0:没有操作
static unsigned char key_val; //0x50, 0x51
static wait_queue_head_t wq; //等待队列头
static struct class *cls;

static ssize_t btn_read(struct file *file, 
			char __user *buf,
			size_t count,
			loff_t *ppos)
{
	//1.判断按键是否有操作，没有则按键数据无效，应该休眠
	//  否则上报有效按键值
	printk("process(%d) will go sleep...\n", current->pid);
	wait_event_interruptible(wq, ispress);
	ispress = 0;
	printk("process(%d) wakeup...\n", current->pid);
	
	//上报按键值
	copy_to_user(buf, &key_val, 1);
	return count;
}

static struct file_operations btn_fops = {
	.owner = THIS_MODULE;
	.read = btn_read
};

static irqreturn_t button_isr(int irq, void *dev_id) {
	unsigned int pinstate;
	//1.获取按键状态
	pinstate = gpio_get_value(S3C2440_GPF0(0));
	if(pinstate == 1) //松开
		key_val = 0x50;
	else
		key_val = 0x51;
	//2.唤醒休眠的进程
	ispress = 1; //记录有按键操作
	wake_up_interruptible(&wq);
	
	return IRQ_HANDLED;
}

static int button_init(void) {
	dev_t dev;
	//1.分配设备号
	alloc_chrdev_region(&dev, 0, 1, "buttons");
	major = MAJOR(dv);
	//2.初始化注册cdev
	cdev_init(&btn_cdev, &btn_fops);
	cdev_add(&btn_cdev, dev, 1);
	//3.自动创建设备节点
	cls = class_create(THIS_MODULE, "buttons");
	device_create(cls, NULL, dev, NULL, "buttons");
	//4.申请GPIO资源
	gpio_request(S3C2440_GPF0(0), "KEY_UP");
	//5.注册中断
	request_irq(IRQ_EINT(0), button_isr,
		IRQF_TRIGGER_FALLING|IRQF_TRIGGER_RISING,
		"KEY_UP", NULL);
	//6.初始化等待队列头
	init_waitqueue_head(&wq);
	return 0;
}

static void button_exit(void) {
	dev_t dev = MKDEV(major, 0);
	//1.释放中断
	free_irq(IRQ_EINT(0), NULL);
	//2.释放GPIO资源
	gpio_free(S3C2440_GPF0(0));
	//3.删除设备节点
	device_destroy(cls, dev);
	class_destroy(cls);
	//4.卸载cdev和设备号
	cdev_dev(&btn_cdev);
	unregister_chrdev_region(dev, 1);
}

module_init(button_init);
module_exit(button_exit);
MODULE_LICENSE("GPL");

