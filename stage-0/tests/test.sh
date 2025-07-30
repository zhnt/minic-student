#!/bin/bash

# 阶段0简单验证脚本

set -e

STAGE_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
TARGET="$STAGE_DIR/build/minic"

echo "🧪 阶段0验证开始..."

# 构建项目
cd "$STAGE_DIR"
make clean > /dev/null
make > /dev/null

if [ ! -f "$TARGET" ]; then
    echo "❌ 构建失败"
    exit 1
fi

echo "✅ 构建成功"

# 简单验证
echo "🎯 验证基础加法："
result=$(echo "3 + 5" | "$TARGET" 2>/dev/null | grep -E '^[0-9]+\.[0-9]+$' || echo "未找到结果")
echo "   3 + 5 = $result"

echo "🎯 验证变量赋值："
result=$(echo "x = 10 + 20; x" | "$TARGET" 2>/dev/null | grep -E '^[0-9]+\.[0-9]+$' || echo "未找到结果")
echo "   x = 10 + 20; x = $result"

echo ""
echo "🎉 阶段0验证完成！"
echo "🚀 可以体验更多功能："
echo "  ./build/minic -h    # 查看帮助"
echo "  ./build/minic -vt   # 观察token"
echo "  ./build/minic -v    # 完整调试"