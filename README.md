# Linux 驱动开发学习仓库

<!-- 徽章区 -->
[![Stars](https://img.shields.io/github/stars/yourusername/linux-driver-learning?style=social)](https://github.com/yourusername/linux-driver-learning)
[![Forks](https://img.shields.io/github/forks/yourusername/linux-driver-learning?style=social)](https://github.com/yourusername/linux-driver-learning)
[![License](https://img.shields.io/github/license/yourusername/linux-driver-learning)](LICENSE)
[![Last Commit](https://img.shields.io/github/last-commit/yourusername/linux-driver-learning)](https://github.com/yourusername/linux-driver-learning/commits)

<!-- 中文说明 -->
> 从零开始学习 Linux 驱动开发，记录每一个学习脚印。本仓库将持续更新，涵盖从基础模块到高级驱动的完整学习路径。

## 📖 目录导航

- [📚 学习路线](#-学习路线)
- [🚀 快速开始](#-快速开始)
- [📂 仓库结构](#-仓库结构)
- [🔧 环境要求](#-环境要求)
- [📝 示例列表](#-示例列表)
- [🤝 贡献指南](#-贡献指南)
- [📄 开源协议](#-开源协议)

---

## 📚 学习路线

```
┌─────────────────────────────────────────────────────────────────┐
│                     Linux 驱动开发学习路径                        │
├─────────────────────────────────────────────────────────────────┤
│                                                                  │
│  第一阶段：入门基础                                                │
│  ├── 01-Hello World 模块 ◄── 当前进度                            │
│  ├── 02-模块参数传递                                              │
│  └── 03-模块依赖关系                                              │
│                                                                  │
│  第二阶段：字符设备                                                │
│  ├── 04-字符设备驱动框架                                          │
│  ├── 05-设备号注册                                                │
│  └── 06-文件操作接口                                              │
│                                                                  │
│  第三阶段：设备类与设备节点                                        │
│  ├── 07-自动创建设备节点                                          │
│  └── 08-设备类实现                                                │
│                                                                  │
│  第四阶段：进阶主题                                                │
│     ... 更多内容持续更新                                          │
│                                                                  │
└─────────────────────────────────────────────────────────────────┘
```

---

## 🚀 快速开始

### 1. 环境准备

```bash
# Ubuntu/Debian
sudo apt update
sudo apt install build-essential linux-headers-$(uname -r)

# CentOS/RHEL
sudo yum install gcc make kernel-devel
```

### 2. 编译内核模块

```bash
# 进入示例目录
cd examples/01-hello_module

# 编译
make

# 查看生成的 .ko 文件
ls -la *.ko
```

### 3. 加载和卸载模块

```bash
# 加载模块
sudo insmod hello.ko

# 查看内核日志
dmesg | tail -f

# 卸载模块
sudo rmod hello

# 再次查看日志确认卸载
dmesg | tail
```

### 4. 带参数加载（可选）

```bash
# 指定参数加载
sudo insmod hello.ko name="World" count=5

# 查看参数
cat /sys/module/hello/parameters/name
cat /sys/module/hello/parameters/count
```

---

## 📂 仓库结构

```
linux-driver-learning/
│
├── README.md              # 主说明文档
├── LICENSE                # 开源协议 (GPL-2.0)
├── .gitignore             # Git 忽略规则
│
├── docs/                  # 教程文档
│   ├── 00-环境搭建.md      # 开发环境配置指南
│   └── 01-第一个内核模块.md # Hello World 教程
│
├── examples/              # 示例代码
│   └── 01-hello_module/   # 第一个示例：Hello World
│       ├── hello.c        # 模块源码
│       ├── Makefile       # 编译脚本
│       └── README.md      # 示例说明
│
└── scripts/               # 辅助脚本
    └── clean.sh           # 清理编译产物
```

---

## 🔧 环境要求

| 项目 | 要求 |
|------|------|
| 操作系统 | Linux (Ubuntu 20.04+ / CentOS 8+ 测试通过) |
| GCC | GCC 7.0+ |
| Make | GNU Make 4.0+ |
| 内核头文件 | `linux-headers-$(uname -r)` |
| root 权限 | 加载/卸载模块需要 root 权限 |

> ⚠️ **注意**: 不建议在生产环境直接编译和测试内核模块，请在虚拟机中进行。

---

## 📝 示例列表

### [01 - Hello World 模块](./examples/01-hello_module/)

最简单的内核模块示例，演示：
- 内核模块的基本结构
- `module_init()` 和 `module_exit()` 的使用
- `printk()` 内核日志输出
- 模块参数传递

---

## 🤝 贡献指南

欢迎提交 Issue 和 Pull Request！

1. **Fork 本仓库**
2. **创建特性分支** (`git checkout -b feature/AmazingFeature`)
3. **提交更改** (`git commit -m 'Add some AmazingFeature'`)
4. **推送到分支** (`git push origin feature/AmazingFeature`)
5. **创建 Pull Request**

---

## 📄 开源协议

本项目基于 [GPL-2.0 License](LICENSE) 开源，欢迎自由使用、修改和分发。

---

<!-- 底部信息 -->
<p align="center">
  <sub>如果你觉得这个仓库对你有帮助，请点个 ⭐ 支持一下！</sub>
</p>
