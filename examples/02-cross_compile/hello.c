/*
 * hello.c - ARM 开发板内核模块（交叉编译版）
 *
 * 本示例演示如何编写一个简单的内核模块，
 * 并使用交叉编译工具链编译后在 ARM 开发板上运行。
 *
 * 与 x86 虚拟机版本的区别：
 *   1. 使用 arm-poky-linux-gnueabi- 交叉编译器
 *   2. 指定 ARM 架构参数（cortex-a7, armv7ve, neon）
 *   3. 指定 sysroot（目标板文件系统根目录）
 *   4. 通过 NFS 将 .ko 文件传到开发板执行
 */

#include <linux/init.h>    /* module_init() / module_exit() 宏 */
#include <linux/module.h>  /* MODULE_* 宏、printk() 等 */

/* ─────────────────────────────────────────────────────────────────
 * 模块初始化函数
 * 当开发板上执行 insmod 时调用
 * ───────────────────────────────────────────────────────────────── */
static int __init hello_init(void)
{
    printk(KERN_INFO "hello, dry, i am linux driver.\n");
    return 0; /* 返回 0 表示初始化成功 */
}

/* ─────────────────────────────────────────────────────────────────
 * 模块退出函数
 * 当开发板上执行 rmmod 时调用
 * ───────────────────────────────────────────────────────────────── */
static void __exit hello_exit(void)
{
    printk(KERN_INFO "goodbye, dry, i am exiting.\n");
}

/* ─────────────────────────────────────────────────────────────────
 * 模块入口/出口声明
 * ───────────────────────────────────────────────────────────────── */
module_init(hello_init);
module_exit(hello_exit);

/* ─────────────────────────────────────────────────────────────────
 * 模块元信息
 * ───────────────────────────────────────────────────────────────── */
MODULE_LICENSE("Dual BSD/GPL");             /* 许可证（必须） */
MODULE_AUTHOR("king");                      /* 作者 */
MODULE_DESCRIPTION("A simple hello world driver"); /* 描述 */
