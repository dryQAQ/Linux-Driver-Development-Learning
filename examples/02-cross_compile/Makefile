# ============================================================
# 交叉编译 Makefile — 用于 ARM 开发板内核模块编译
# ============================================================
#
# 核心概念：
#   在 x86 PC 上编译出 ARM 架构的内核模块 (.ko)
#   需要三个关键要素：
#     1. 目标板的内核源码路径（用于获取内核头文件和构建系统）
#     2. 交叉编译器（arm-poky-linux-gnueabi-gcc）
#     3. 目标板的 sysroot（文件系统根目录）
#
# 修改说明：
#   本 Makefile 相较于 01-hello_module 版本，主要区别在于：
#     - 不再使用当前 PC 的内核源码（/lib/modules/...）
#     - 改用开发板的内核源码路径
#     - 指定交叉编译器和 ARM 架构参数
#     - 不再需要双遍(ifeq/else)设计，直接指定内核路径即可
# ============================================================

# ── 1. 内核源码路径 ──────────────────────────────────────────
# 必须指向开发板上运行的内核版本对应的源码目录
# 此路径需要根据你的实际环境修改
LINUX_KERNEL_PATH = /home/king/code/kernel/linux-4.1.15-elf1

# ── 2. 当前模块源码路径 ─────────────────────────────────────
CURRENT_PATH := $(shell pwd)

# ── 3. 交叉编译器 ───────────────────────────────────────────
# arm-poky-linux-gnueabi- 是 Yocto 项目生成的 ARM 交叉编译器前缀
# 常见的交叉编译器前缀：
#   arm-linux-gnueabihf-     (硬浮点)
#   arm-linux-gnueabi-       (软浮点)
#   arm-none-linux-gnueabi-  (CodeSourcery)
#   aarch64-linux-gnu-       (ARM 64位)
CROSS_COMPILE = arm-poky-linux-gnueabi-

# ── 4. 编译器与架构参数 ─────────────────────────────────────
# -march=armv7ve   : ARMv7 虚拟化扩展架构（Cortex-A7 支持）
# -mfpu=neon       : 启用 NEON SIMD 浮点单元
# -mcpu=cortex-a7  : 目标 CPU 为 Cortex-A7
# --sysroot=...    : 指定目标文件系统根目录
#                    编译器会在 sysroot/usr/include 找头文件
#                    在 sysroot/usr/lib    找库文件
CC = $(CROSS_COMPILE)gcc -march=armv7ve -mfpu=neon -mcpu=cortex-a7 --sysroot=/home/king/code/rootfs/rootfs

# ── 5. 目标模块 ─────────────────────────────────────────────
# obj-m 告诉内核构建系统将此文件编译为内核模块(.ko)
# 注意：这里的名字必须和 C 文件名对应
#       hello_dry_driver.o 对应 hello_dry_driver.c
obj-m := hello_dry_driver.o

# ── 6. 编译目标 ─────────────────────────────────────────────
all:
	$(MAKE) -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) modules
#        │        │                   │               └── 构建目标：modules（内核模块）
#        │        │                   └── M= 指定模块源码所在目录
#        │        └── -C 切换到内核源码目录去执行 Make
#        └── 调用 make，继承当前的 CC、CROSS_COMPILE 等变量

# ── 7. 清理目标 ─────────────────────────────────────────────
clean:
	$(MAKE) -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) modules clean
#        │        │                   │               └── clean（清理目标）
#        │        │                   └── 必须指定 M=，否则会清理整个内核源码
#        │        └── 同样在内核源码目录执行
#        └── 调用 make

# ── 8. 伪目标声明 ──────────────────────────────────────────
# .PHONY 告诉 make 这些目标不是文件名
# 避免与同名文件冲突
.PHONY: all clean
