# 01 - Hello World 模块

最简单的 Linux 内核模块示例。

## 📚 学习要点

本示例演示了以下核心概念：

1. **内核模块基本结构**
   - 头文件引入
   - 模块初始化函数 `hello_init()`
   - 模块退出函数 `hello_exit()`
   - `module_init()` 和 `module_exit()` 宏

2. **内核日志输出**
   - `printk()` 函数的使用
   - 日志级别 `KERN_INFO`
   - 查看日志：`dmesg` 命令

3. **模块信息声明**
   - `MODULE_LICENSE()` - 许可证声明（必须）
   - `MODULE_AUTHOR()` - 作者信息
   - `MODULE_DESCRIPTION()` - 模块描述

4. **模块参数传递**
   - `module_param()` 宏
   - 支持的参数类型
   - 权限掩码 `S_IRUGO`

## 🔨 编译

```bash
make
```

成功编译后生成 `hello.ko` 文件。

## 🚀 运行

```bash
# 加载模块（默认参数）
sudo insmod hello.ko

# 查看内核日志
dmesg | tail

# 卸载模块
sudo rmmod hello

# 带参数加载
sudo insmod hello.ko name="Linux" count=3

# 查看模块参数
cat /sys/module/hello/parameters/name
cat /sys/module/hello/parameters/count
```

## 📤 预期输出

### 加载时 (`insmod hello.ko`)

```
hello [1] times, [none], the hello module has loaded.
hello [2] times, [none], the hello module has loaded.
```

### 卸载时 (`rmmod hello`)

```
goodbye, hello module has exited.
```

## 🔍 关键代码解析

### 模块入口点

```c
module_init(hello_init);   // 注册初始化函数
module_exit(hello_exit);   // 注册退出函数
```

### printk 日志级别

| 级别 | 宏定义 | 含义 |
|------|--------|------|
| 0 | KERN_EMERG | 系统不可用 |
| 1 | KERN_ALERT | 需要立即处理 |
| 2 | KERN_CRIT | 严重情况 |
| 3 | KERN_ERR | 错误 |
| 4 | KERN_WARNING | 警告 |
| 5 | KERN_NOTICE | 正常但重要 |
| 6 | KERN_INFO | 一般信息 |
| 7 | KERN_DEBUG | 调试信息 |

### Makefile 工作原理

```
┌─────────────────────────────────────────────────────┐
│  make 命令行执行 (KERNELRELEASE 未定义)              │
│                         │                           │
│                         ▼                           │
│  make -C /lib/modules/.../build M=$(PWD) modules   │
│                         │                           │
│                         ▼                           │
│  内核构建系统被调用，再次执行此 Makefile              │
│  (此时 KERNELRELEASE 已定义，跳过第一遍)              │
│                         │                           │
│                         ▼                           │
│  obj-m := hello.o  ← 告诉内核要编译成模块            │
└─────────────────────────────────────────────────────┘
```

## 📝 作业

1. 修改 `count` 参数，观察输出变化
2. 尝试添加一个新的参数（如 `message`）
3. 修改日志级别为 `KERN_DEBUG`，观察区别

## 🔗 相关资料

- [Linux Kernel Module Programming Guide](https://www.tldp.org/LDP/lkmpg/)
- [内核文档](https://www.kernel.org/doc/html/latest/)
