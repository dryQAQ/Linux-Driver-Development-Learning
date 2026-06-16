# Makefile for Linux Kernel Module
#
# 这个 Makefile 采用双遍(pass)设计：
#   第一遍：检测 KERNELRELEASE 是否定义
#   第二遍：实际执行内核模块编译
#

# ─────────────────────────────────────────────────────────────────
# 第一遍：检测是否由内核构建系统调用
# ─────────────────────────────────────────────────────────────────
ifeq ($(KERNELRELEASE),)
    # KERNELRELEASE 未定义，说明是直接从命令行调用 make

    # 内核源码目录：优先使用环境变量 KERNELDIR，否则使用默认路径
    KERNELDIR ?= /lib/modules/$(shell uname -r)/build

    # 当前目录路径
    PWD := $(shell pwd)

    # 目标：编译内核模块
modules:
	@echo "========================================="
	@echo "  Building Linux Kernel Module..."
	@echo "  Kernel: $(KERNELDIR)"
	@echo "  Source: $(PWD)"
	@echo "========================================="
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

    # 目标：安装内核模块到系统
modules_install:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules_install

    # 目标：清理编译产物
clean:
	@echo "Cleaning build artifacts..."
	rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c \
	       .tmp_versions Module.symvers modules.order \
	       hello.mod
	@echo "Clean complete."

# 声明这些是伪目标(phony target)，避免与同名文件冲突
.PHONY: modules modules_install clean

else
    # ─────────────────────────────────────────────────────────────
    # 第二遍：由内核构建系统调用，此时 KERNELRELEASE 已定义
    # ─────────────────────────────────────────────────────────────

    # obj-m 指定要编译成内核模块的目标文件
    # hello.o 会根据 hello.c 自动构建
    obj-m := hello.o

endif
