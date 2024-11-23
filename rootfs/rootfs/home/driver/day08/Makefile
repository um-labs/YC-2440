ifneq ($(KERNELRELEASE),)
obj-m += led_ioremap_drv.o
else
	KERNELDIR = /git/kernel/kernel-for-YC2440/linux-2.6.35.7
all:
	$(MAKE) -C $(KERNELDIR) M=$(PWD)
clean:
	rm .tmp_versions .*cmd *.mod* *.ko *.o Module.* modules.* -fr
endif
