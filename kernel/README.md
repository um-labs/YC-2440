 Git 全局设置:

 git config --global user.name "uucall"
 git config --global user.email "uucall@126.com"

 创建 git 仓库

 mkdir kernel-for-YC2440
 cd kernel-for-YC2440
 git init
 touch README.md
 git add README.md
 git commit -m "first commit"
 git remote add origin http://git.oschina.net/uucall/kernel-for-YC2440.git
 git push -u origin master

 已有项目?

 cd existing_git_repo
 git remote add origin http://git.oschina.net/uucall/kernel-for-YC2440.git
 git push -u origin master



// kernel-for-YC2440 项目说明 -----------------------
// kernel linux-2.6.35.7 在YC2440开发板（型号UTU2440-F-T35C）上的移植
// 交叉编译器版本: arm-linux-gcc 4.3.2
// NAND FLASH: K9F1208UOM 64M 
// SDRAM: HY57V561620BT-H 32M*2=64M.
// 网卡: DM9000A
// 显示器: NEC NL2432HC22-22B QVGA 240 × 320

// 版本 v1.0.0
// 1. 初始版本，基本实现了kernel对S3C2440平台的支持

// 版本 v1.0.1
// 1. 修改Boot options：noinitrd root=/dev/mtdblock4 init=/linuxrc console=ttySAC0，重新编译了生成了zImage。
// 2. 修改arch/arm/mach-s3c2440/mach-smdk2440.c，在数组smdk2440_devices中添加&s3c_device_rtc。

// 版本 v1.0.2
// 1. 关闭ECC校验
// 2. 移植声音UDA1341驱动
// 3. 移植DM9000驱动，实现NFS挂载文件系统

// 版本 v1.0.3
// 1. 修改了driver/net/dm9000.c，增加
// 		#define GPGUP 			 (0x56000068)
//    及修改Disable pull-up功能。

// 版本 v1.0.4
// 1. 增加sd卡支持

// 版本 v1.0.5
// 1. 根据DM9000A规格书，PIN34 INT: This pin is high active at default 
//    修改arch/arm/plat-s3c24xx/devs.c中.flags = IORESOURCE_IRQ为.flags = IORESOURCE_IRQ | IRQF_TRIGGER_HIGH
//    消除 WARNING: no IRQ resource flags set. 警告 
