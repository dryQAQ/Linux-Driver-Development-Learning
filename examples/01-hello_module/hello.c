/*
 * hello.c - 第一个 Linux 内核模块
 *
 * 这是学习 Linux 驱动开发的第一个示例程序。
 * 演示了内核模块的基本结构、初始化/退出函数以及模块参数的使用。
 */

/* ─────────────────────────────────────────────────────────────────
 * 头文件说明：
 *
 * <linux/init.h>    - 包含 module_init() 和 module_exit() 宏定义
 * <linux/module.h>  - 包含模块相关的核心定义（如 MODULE_* 宏）
 * <linux/moduleparam.h> - 包含模块参数相关的定义
 * ───────────────────────────────────────────────────────────────── */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>

/* ─────────────────────────────────────────────────────────────────
 * 模块信息宏：
 *
 * MODULE_LICENSE()  - 必须声明，标识模块的许可证
 *   常见值："GPL" / "GPL v2" / "GPL AND MIT" / "BSD" / "Proprietary"
 *   使用 "Dual BSD/GPL" 表示兼容 BSD 和 GPL 许可证
 *
 * 其他可选宏：
 * MODULE_AUTHOR()   - 作者信息
 * MODULE_DESCRIPTION() - 模块描述
 * MODULE_VERSION()  - 模块版本
 * ───────────────────────────────────────────────────────────────── */
MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Your Name <your.email@example.com>");
MODULE_DESCRIPTION("A simple Hello World module for learning Linux driver development");
MODULE_VERSION("1.0");

/* ─────────────────────────────────────────────────────────────────
 * 模块参数：
 *
 * module_param(name, type, perm)
 *   - name : 参数名（在用户空间可见）
 *   - type : 参数类型 (int, charp, long, bool 等)
 *   - perm : 权限掩码 (S_IRUGO = 所有人可读)
 *
 * 这些参数可以通过 insmod 时传入，如：
 *   insmod hello.ko name="World" count=5
 * ───────────────────────────────────────────────────────────────── */

/* 默认值：打印次数 */
static int count = 2;
module_param(count, int, S_IRUGO);

/* 默认值：名称字符串 */
static char *name = "none";
module_param(name, charp, S_IRUGO);

/* ─────────────────────────────────────────────────────────────────
 * 内核模块的初始化函数
 *
 * 当使用 insmod 加载模块时，此函数会被内核调用。
 * 返回 0 表示成功，负数表示失败（模块将不会被加载）。
 *
 * 注意：
 *   - 函数必须是 static 类型
 *   - 使用 printk() 而非 printf() 输出日志
 *   - KERN_INFO 是日志级别，等同于 "Information" 级别
 * ───────────────────────────────────────────────────────────────── */
static int __init hello_init(void)
{
    int i;

    /* 循环打印 count 次欢迎信息 */
    for (i = 0; i < count; i++) {
        /*
         * printk() - 内核空间的日志输出函数
         * 格式与 printf() 类似，但需要指定日志级别前缀
         * KERN_INFO = 级别 6，表示一般信息
         *
         * 日志级别从小到大：
         *   KERN_EMERG   (0) - 紧急情况
         *   KERN_ALERT   (1) - 必须立即处理
         *   KERN_CRIT    (2) - 严重情况
         *   KERN_ERR     (3) - 错误情况
         *   KERN_WARNING (4) - 警告
         *   KERN_NOTICE  (5) - 正常但重要
         *   KERN_INFO    (6) - 一般信息
         *   KERN_DEBUG   (7) - 调试信息
         */
        printk(KERN_INFO "hello [%d] times, [%s], the hello module has loaded.\n",
               i + 1, name);
    }

    /* 返回 0 表示初始化成功 */
    return 0;
}

/* ─────────────────────────────────────────────────────────────────
 * 内核模块的退出/清理函数
 *
 * 当使用 rmmod 卸载模块时，此函数会被内核调用。
 * 用于释放初始化时分配的资源。
 * ───────────────────────────────────────────────────────────────── */
static void __exit hello_exit(void)
{
    /* 打印卸载信息 */
    printk(KERN_INFO "goodbye, hello module has exited.\n");
}

/* ─────────────────────────────────────────────────────────────────
 * 模块入口/出口声明
 *
 * module_init()  - 指定模块的初始化函数（加载时调用）
 * module_exit() - 指定模块的退出函数（卸载时调用）
 *
 * __init 和 __exit 是内核的标记：
 *   __init  - 告诉内核该函数只在初始化期间使用，初始化后可释放内存
 *   __exit  - 告诉内核该函数只在模块卸载时使用，如果内核不支持模块卸载则可忽略
 * ───────────────────────────────────────────────────────────────── */
module_init(hello_init);
module_exit(hello_exit);
