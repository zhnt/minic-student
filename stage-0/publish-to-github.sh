#!/bin/bash

# 一键发布Stage-0到GitHub

set -e

REPO_NAME="minic-teaching"
GITHUB_USER="zhnt"
REPO_URL="https://github.com/$GITHUB_USER/$REPO_NAME.git"

# 颜色输出
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo -e "${GREEN}🚀 开始发布Minic阶段0...${NC}"

# 1. 验证环境
echo -e "${YELLOW}📋 检查环境...${NC}"
command -v git >/dev/null 2>&1 || { echo -e "${RED}❌ git未安装${NC}"; exit 1; }
command -v gh >/dev/null 2>&1 || { echo -e "${RED}❌ GitHub CLI未安装${NC}"; echo "安装: brew install gh"; exit 1; }

# 2. 清理和测试
echo -e "${YELLOW}🧪 测试阶段0功能...${NC}"
make clean > /dev/null 2>&1
make > /dev/null 2>&1

if [ ! -f "build/minic" ]; then
    echo -e "${RED}❌ 构建失败${NC}"
    exit 1
fi

# 测试基本功能
echo "3 + 5" | ./build/minic 2>/dev/null | grep -q "8.00" || {
    echo -e "${RED}❌ 功能测试失败${NC}"
    exit 1
}

echo -e "${GREEN}✅ 功能测试通过${NC}"

# 3. 创建发布包
echo -e "${YELLOW}📦 创建发布包...${NC}"
make clean > /dev/null 2>&1
rm -rf .git/ minic-s0.tar.gz 2>/dev/null || true

# 创建干净的发布包
tar -czf minic-s0.tar.gz --exclude='.git' --exclude='build' --exclude='*.o' --exclude='minic' .
echo -e "${GREEN}✅ 发布包创建完成${NC}"

# 4. 登录GitHub
echo -e "${YELLOW}🔑 检查GitHub登录...${NC}"
gh auth status >/dev/null 2>&1 || {
    echo -e "${YELLOW}请登录GitHub...${NC}"
    gh auth login
}

# 5. 检查或创建仓库
echo -e "${YELLOW}📁 检查GitHub仓库...${NC}"
if gh repo view "$GITHUB_USER/$REPO_NAME" >/dev/null 2>&1; then
    echo -e "${GREEN}✅ 仓库已存在${NC}"
else
    echo -e "${YELLOW}📁 创建仓库...${NC}"
    gh repo create "$GITHUB_USER/$REPO_NAME" --public --description "渐进式编译器教学框架 - 12阶段学习路径"
fi

# 6. 创建s0分支
echo -e "${YELLOW}🌿 创建s0分支...${NC}"
git init
git add .
git commit -m "Minic阶段0：加法计算器 - 教学用发布版"

# 添加远程并推送
git remote add origin "$REPO_URL" 2>/dev/null || true
git checkout -b s0 2>/dev/null || true
git push -f origin s0

echo -e "${GREEN}✅ 代码已推送到s0分支${NC}"

# 7. 创建GitHub Release
echo -e "${YELLOW}🚀 创建GitHub Release...${NC}"

# 删除旧release（如果存在）
gh release delete s0 --yes 2>/dev/null || true

# 创建新release
gh release create s0 \
    --title "阶段0：加法计算器" \
    --notes "🎯 15分钟体验编译器的神奇之处

✅ 功能特点：
- 支持基础加法运算
- 变量赋值功能
- 交互式REPL环境
- 可视化调试工具
- 文件编译支持

🚀 快速开始：
```bash
make
echo '3 + 5' | ./build/minic    # 8.00
```

📚 学习目标：
- 体验编译器的神奇之处
- 建立学习信心
- 准备好进入下一阶段

🎓 教学用途：专为编译器入门课程设计
" \
    minic-s0.tar.gz

echo -e "${GREEN}✅ GitHub Release创建完成${NC}"

# 8. 验证发布
echo -e "${YELLOW}🔍 验证发布...${NC}"
sleep 2

# 测试下载链接
if curl -s --head "https://github.com/$GITHUB_USER/$REPO_NAME/releases/download/s0/minic-s0.tar.gz" | head -n 1 | grep -q "200 OK"; then
    echo -e "${GREEN}✅ 发布验证成功${NC}"
else
    echo -e "${RED}⚠️  发布可能需要几分钟生效${NC}"
fi

# 9. 生成学生使用指南
echo -e "${GREEN}📝 学生使用指南：${NC}"
echo ""
echo "📥 下载地址："
echo "  直接下载： https://github.com/$GITHUB_USER/$REPO_NAME/releases/download/s0/minic-s0.tar.gz"
echo "  Git克隆：  https://github.com/$GITHUB_USER/$REPO_NAME.git"
echo "  分支：     s0"
echo ""
echo "🚀 学生使用："
echo "  wget https://github.com/$GITHUB_USER/$REPO_NAME/releases/download/s0/minic-s0.tar.gz"
echo "  tar -xzf minic-s0.tar.gz"
echo "  cd minic-s0"
echo "  make"
echo "  echo '3 + 5' | ./build/minic"
echo ""
echo -e "${GREEN}🎉 发布完成！${NC}"
echo -e "${YELLOW}📊 访问：https://github.com/$GITHUB_USER/$REPO_NAME/releases/tag/s0${NC}"