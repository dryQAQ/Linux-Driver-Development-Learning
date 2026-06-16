#!/bin/bash
# 清理内核模块编译产物
#
# 用法: ./scripts/clean.sh
#

echo "Cleaning kernel module build artifacts..."

# 切换到脚本所在目录的父目录（项目根目录）
cd "$(dirname "$0")/.."

# 清理 examples 目录下的编译产物
find examples -name "*.ko" -delete
find examples -name "*.o" -delete
find examples -name "*.mod*" -delete
find examples -name ".*.cmd" -delete
find examples -name ".tmp_versions" -type d -exec rm -rf {} + 2>/dev/null || true
find examples -name "Module.symvers" -delete
find examples -name "modules.order" -delete

# 清理根目录下的编译产物（如果有）
rm -f *.ko *.o *.mod* .*.cmd Module.symvers modules.order
rm -rf .tmp_versions

echo "Clean complete."
