#!/bin/bash

# 教师发布单个阶段到minic-student仓库
# 使用Git标签实现阶段解锁 - 纯Git版本

set -e

STAGE_NUM=$1
MESSAGE=$2

if [ -z "$STAGE_NUM" ]; then
    echo "用法: ./publish-stage.sh <阶段号> [发布消息]"
    echo "示例: ./publish-stage.sh 0 '发布加法计算器阶段'"
    exit 1
fi

GITHUB_USER="zhnt"
REPO_NAME="minic-student"
STAGE_DIR="stage-${STAGE_NUM}"

# 颜色输出
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'

echo -e "${GREEN}🎯 发布阶段${STAGE_NUM}到${REPO_NAME}${NC}"

# 检查参数
if [ ! -d "$STAGE_DIR" ]; then
    echo -e "${RED}❌ 阶段目录 ${STAGE_DIR} 不存在${NC}"
    exit 1
fi

# 检查Git配置
echo -e "${YELLOW}🔑 检查Git配置...${NC}"
if ! git config user.name >/dev/null 2>&1; then
    echo -e "${RED}❌ Git未配置用户名${NC}"
    echo "请先配置: git config --global user.name 'Your Name'"
    exit 1
fi

if ! git config user.email >/dev/null 2>&1; then
    echo -e "${RED}❌ Git未配置邮箱${NC}"
    echo "请先配置: git config --global user.email 'your.email@example.com'"
    exit 1
fi

# 测试阶段构建
make clean >/dev/null 2>&1 || true
make >/dev/null 2>&1


# 返回根目录
cd ..

# 创建发布标签
echo -e "${YELLOW}🏷️  创建Git标签...${NC}"
TAG_NAME="stage-${STAGE_NUM}"
TAG_MESSAGE=${MESSAGE:-"Minic阶段${STAGE_NUM}发布"}

# 确保git已初始化
if [ ! -d ".git" ]; then
    git init
    git add .
    git commit -m "初始化Minic学生代码库"
fi

# 添加所有文件
git add stage-${STAGE_NUM}/
git add README.md
git add publish-stage.sh

# 检查是否有更改需要提交
if ! git diff-index --quiet HEAD -- 2>/dev/null; then
    git commit -m "发布阶段${STAGE_NUM}: ${TAG_MESSAGE}"
else
    echo -e "${YELLOW}⚠️  无更改需要提交${NC}"
fi

# 创建标签（如果已存在则强制更新）
git tag -a "$TAG_NAME" -m "$TAG_MESSAGE" -f || git tag "$TAG_NAME" -f

echo -e "${GREEN}✅ 阶段${STAGE_NUM}准备就绪！${NC}"
echo
echo "📋 下一步操作："
echo "1. 创建GitHub仓库: https://github.com/new"
echo "2. 仓库名: ${REPO_NAME}"
echo "3. 执行以下命令推送："
echo
echo "   # 首次推送："
echo "   git remote add origin https://github.com/${GITHUB_USER}/${REPO_NAME}.git"
echo "   git branch -M main"
echo "   git push -u origin main"
echo "   git push origin ${TAG_NAME}"
echo
echo "   # 后续推送："
echo "   git push origin main"
echo "   git push origin ${TAG_NAME}"
echo
echo "📱 学生使用方式："
echo "   git clone https://github.com/${GITHUB_USER}/${REPO_NAME}.git"
echo "   git checkout ${TAG_NAME}"
