Git全局设置

git config --global user.name "uucall"
git config --global user.email "uucall@126.com"

创建 git 仓库

mkdir u-boot-2010.06-for-YC2440
cd u-boot-2010.06-for-YC2440
git init
touch README.md
git add README.md
git commit -m "first commit"
git remote add origin http://git.oschina.net/uucall/u-boot-2010.06-for-YC2440.git
git push -u origin master

已有项目?

cd existing_git_repo
git remote add origin http://git.oschina.net/uucall/u-boot-2010.06-for-YC2440.git
git push -u origin master


// u-boot-2010.06-for-YC2440 项目说明 -----------------------
// u-boot-2010.06 在YC2440开发板（型号UTU2440-F-T35C）上的移植
// 交叉编译器版本: arm-linux-gcc 4.3.2
// NAND FLASH: K9F1208UOM 64M 
// SDRAM: HY57V561620BT-H 32M*2=64M.
// 网卡: DM9000A
// 显示器: NEC NL2432HC22-22B QVGA 240 × 320

// 版本 v1.0
// 1. 初始版本，实现了u-boot对S3C2440平台的支持
// 2. 添加了NAND驱动
// 3. 增加了对NAND启动方式的支持

// 版本 v1.01
// 1. 消除BEEP鸣叫
// 2. 去除NorFlash初始化（开发板上没有NorFlash）
// 3. 将u-boot命令行提示符由SMDK2410改成SMDK2440

// 版本 v1.1.0
// 1. 加入网卡DM9000A驱动支持

// 版本 v1.1.1
// 1. 实现Tab键命令自动补齐、上下箭头键调用历史命令。

// 版本 v1.1.2
// 1. 加入MTD(NAND)分区

// 版本 v1.1.3
// 1. 启动zImage内核的支持
// 2. 增加启动时 Hit any key to stop autoboot:

// 版本 v1.1.4
// 1. 烧写YAFFS2文件系统支持

// 版本 v1.1.5
// 1. 使U-BOOT支持jffs2文件系统

// 版本 v1.1.6
// 1. 注销include/configs/smdk2440.h中的#define CONFIG_BOOTCOMMAND
// 2. 修改arch/arm/lib/boot_zImage.c的U_BOOT_CMD，使排列整齐些
// 3. 注销common/main.c中的boot_zImage(0x100000, 0x400000);

// 版本 v1.1.7
// 1. /net/nfs.c 对于 NFS,增加了延时,否则会出现“*** ERROR: Cannot mount”的错误。
