# 02 - ARM 开发板交叉编译

将内核模块交叉编译后在 ARM 开发板上运行。

## 与 01-x86 版本的核心区别

| 对比项 | 01-x86 虚拟机版 | 02-ARM 开发板版 |
|--------|----------------|-----------------|
| 编译 | 本地 GCC 编译 | 交叉编译器编译 |
| 内核源码 | `/lib/modules/$(uname -r)/build` | 开发板内核源码路径 |
| 运行 | `sudo insmod` | 开发板串口/SSH 执行 |
| 文件传输 | 本地直接执行 | NFS 挂载共享 |

## 🔨 编译

```bash
make
```

成功生成 `hello_dry_driver.ko`。

> ⚠️ **注意**：C 文件名 `hello_dry_driver.c` 必须与 Makefile 中 `obj-m := hello_dry_driver.o` 一致。

## 🚀 在开发板上运行

### 通过 NFS 传输文件

```bash
# 开发板上，创建挂载目录
mkdir -p /mnt/king

# 开发板上，编辑 fstab 添加自动挂载
vi /etc/fstab
# 在文件尾部添加：
# 192.168.100.101:/home/king/project  /mnt/king  nfs  nolock,vers=3 0 0

# 手动挂载
mount -t nfs -o nolock,vers=3 192.168.100.101:/home/king/project /mnt/king

# 进入挂载目录
cd /mnt/king
```

### 加载和卸载

```bash
# 加载模块
insmod hello_dry_driver.ko

# 查看日志
dmesg | tail
dmesg -w             # 实时查看
dmesg -wT            # 显示人类可读时间戳
```

预期输出：
```
hello, dry, i am linux driver.
```

```bash
# 卸载模块
rmmod hello_dry_driver

# 再次查看日志
dmesg | tail
```

预期输出：
```
goodbye, dry, i am exiting.
```

## 🔍 关键知识点

### 交叉编译工具链

```
arm-poky-linux-gnueabi-
  │    │    │    └── ABI（应用二进制接口）
  │    │    └── 目标系统（Linux）
  │    └── 发行商（Yocto Project）
  └── 目标架构（ARM）
```

### 架构参数含义

| 参数 | 含义 |
|------|------|
| `-march=armv7ve` | ARMv7 虚拟化扩展指令集 |
| `-mfpu=neon` | 启用 NEON SIMD 协处理器 |
| `-mcpu=cortex-a7` | 目标 CPU 型号 |
| `--sysroot=/path` | 目标板根文件系统路径 |

### dmesg 常用技巧

```bash
dmesg | tail                          # 查看最后几条日志
dmesg -w                              # 实时跟踪（Ctrl+C 退出）
dmesg -wT                             # 带人类可读时间戳
dmesg -w | grep -E 'mnt|nfs|umount'  # 实时过滤 NFS 挂载日志
```

## 📝 作业

1. 修改 `hello.c` 中的打印内容，重新编译并测试
2. 尝试使用 `dmesg -w` 实时观察模块加载/卸载
3. 了解你的开发板 CPU 型号，对应的交叉编译器是什么

## 🔗 相关资料

- [Yocto Project](https://www.yoctoproject.org/)
- [ARM 交叉编译工具链](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain)
