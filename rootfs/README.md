Git 全局设置:

git config --global user.name "uucall"
git config --global user.email "uucall@126.com"

创建 git 仓库

mkdir rootfs-for-YC2440
cd rootfs-for-YC2440
git init
touch README.md
git add README.md
git commit -m "first commit"
git remote add origin http://git.oschina.net/uucall/rootfs-for-YC2440.git
git push -u origin master

已有项目?

cd existing_git_repo
git remote add origin http://git.oschina.net/uucall/rootfs-for-YC2440.git
git push -u origin master



// rootfs-for-YC2440 项目说明 -----------------------
// rootfs 文件系统 在YC2440开发板（型号UTU2440-F-T35C）上的建立
// 交叉编译器版本: arm-linux-gcc 4.3.2
// NAND FLASH: K9F1208UOM 64M 
// SDRAM: HY57V561620BT-H 32M*2=64M.
// 网卡: DM9000A
// 显示器: NEC NL2432HC22-22B QVGA 240 × 320

// 版本 v1.0.0
// 1. 初始版本

// 版本 v1.0.1
// 1. 实现了基本文件系统并nfs挂载成功
