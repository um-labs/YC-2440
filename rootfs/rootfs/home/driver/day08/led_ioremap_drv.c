#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/io.h>

#define LED_ON	0x100001
#define LED_OFF	0x100002

static int major;
static struct cdev led_cdev;
static struct class *cls;
static void *regs_base;
static unsigned long *gpiocon, *gpiodata;

static int led_ioctl(struct inode *inode,
			struct file *file,
			unsigned int cmd,
			unsigned long arg)
{
	int index;
	//1.拷贝用户空间要操作的灯的编号
	copy_from_user(&index, (int *)arg, 4);
	
	//2.解析命令
	switch(cmd) {
		case LED_ON:
			if (index == 1)
				*gpiodata &= ~(1 << 4);
			else if (index == 2)
				*gpiodata &= ~(1 << 5); 
			else if (index == 3)
				*gpiodata &= ~(1 << 6); 
			else if (index == 4)
				*gpiodata &= ~(1 << 7); 
			break;
		case LED_OFF:
			if (index == 1)
				*gpiodata |= (1 << 4);
			else if (index == 2)
				*gpiodata |= (1 << 5); 
			else if (index == 3)
				*gpiodata |= (1 << 6); 
			else if (index == 4)
				*gpiodata |= (1 << 7); 
			break;
		default:
			return -1;
	}
	printk("GPIOCON = %#x, GPIODATA = %#x\n", *gpiocon, *gpiodata);
	return 0;
}

static struct file_operations led_fops = {
	.owner = THIS_MODULE,
	.ioctl = led_ioctl
};

static int led_init(void) {
	dev_t dev;
	//1.分配设备号
	alloc_chrdev_region(&dev, 0, 1, "leds");
	major = MAJOR(dev);
	//2.初始化注册cdev
	cdev_init(&led_cdev, &led_fops);
	cdev_add(&led_cdev, dev, 1);
	//3.自动创建设备节点
	cls = class_create(THIS_MODULE, "leds");
	device_create(cls, NULL, dev, NULL, "myled");
	//4.地址映射
	regs_base = ioremap(0x56000050, 8);
	gpiocon = (unsigned long *)regs_base;
	gpiodata = (unsigned long *)(regs_base + 0x04);
	//5.配置输出口
	*gpiocon &= ~((0x3 << 8) | (0x3 << 10) | (0x3 << 12) | (0x3 << 14));
	*gpiocon |= ((1 << 8) | (1 << 10) | (1 << 12) | (1 << 14));
	*gpiodata |= ((1 << 4) | (1 << 5) | (1 << 6) | (1 << 7));

	return 0;
}

static void led_exit(void) {
	dev_t dev = MKDEV(major, 0);
	//1.关灯
	*gpiodata |= ((1 << 4) | (1 << 5) | (1 << 6) | (1 << 7));
	//2.解除映射
	iounmap(regs_base);
	//3.删除设备节点，删除cdev，释放设备号
	device_destroy(cls, dev);
	class_destroy(cls);
	cdev_del(&led_cdev);
	unregister_chrdev_region(dev, 1);
}

module_init(led_init);
module_exit(led_exit);
MODULE_LICENSE("GPL");
