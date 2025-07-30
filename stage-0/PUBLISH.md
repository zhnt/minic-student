# 教师发布指南：将Stage-0发布到GitHub

## 🚀 一键发布流程

### 1. 准备阶段0代码
```bash
cd /Users/zhnt/workspace/compile/minic-s0

# 清理不必要的文件
make clean
rm -rf build/
```

### 2. 创建GitHub仓库

#### 方法A：使用GitHub CLI
```bash
# 安装gh（如果未安装）
brew install gh

# 登录GitHub
gh auth login

# 创建仓库
gh repo create zhnt/minic-teaching --private --description "渐进式编译器教学框架"
```

#### 方法B：网页创建
1. 访问 https://github.com/new
2. 创建仓库 `minic-teaching`
3. 保持为公开仓库

### 3. 推送阶段0代码

#### 创建s0分支作为独立发布
```bash
cd /Users/zhnt/workspace/compile/minic-s0

# 初始化Git仓库
git init
git add .
git commit -m "Minic阶段0：加法计算器 - 教学用"

# 添加远程仓库
git remote add origin https://github.com/zhnt/minic-teaching.git

# 推送到s0分支
git checkout -b s0
git push -u origin s0
```

### 4. 创建GitHub Release

#### 方法A：GitHub CLI
```bash
# 创建发布
tar -czf minic-s0.tar.gz *
gh release create s0 --title "阶段0：加法计算器" --notes "15分钟体验编译器魔力" minic-s0.tar.gz
```

#### 方法B：网页操作
1. 访问 https://github.com/zhnt/minic-teaching/releases/new
2. 创建新标签 `s0`
3. 标题："阶段0：加法计算器"
4. 上传 `minic-s0.tar.gz`
5. 发布

### 5. 学生下载方式

#### 提供给学生3种下载方式：

**方式1：直接下载（推荐）**
```bash
wget https://github.com/zhnt/minic-teaching/releases/download/s0/minic-s0.tar.gz
tar -xzf minic-s0.tar.gz
cd minic-s0
make run
```

**方式2：Git克隆**
```bash
git clone https://github.com/zhnt/minic-teaching.git
cd minic-teaching/s0
make run
```

**方式3：一键脚本**
创建 `get-s0.sh`：
```bash
#!/bin/bash
curl -L https://github.com/zhnt/minic-teaching/releases/download/s0/minic-s0.tar.gz | tar -xz
cd minic-s0
make run
```

### 6. 课堂使用模板

#### 教师课前准备（5分钟）
```bash
# 生成二维码指令（学生扫码即下载）
echo "https://github.com/zhnt/minic-teaching/releases/download/s0/minic-s0.tar.gz" | qrencode -t ansi
```

#### 课堂演示脚本（1分钟）
```bash
# 课前在教室电脑运行
curl -sSL https://raw.githubusercontent.com/zhnt/minic-teaching/main/scripts/demo-s0.sh | bash
```

### 7. 验证发布
```bash
# 测试下载流程
mkdir /tmp/test-student
cd /tmp/test-student
wget https://github.com/zhnt/minic-teaching/releases/download/s0/minic-s0.tar.gz
tar -xzf minic-s0.tar.gz
cd minic-s0
make
echo "3 + 5" | ./build/minic  # 应输出：8.00
```

## 📋 发布清单

### ✅ 发布前检查
- [ ] 代码能正常编译运行
- [ ] README.md包含完整说明
- [ ] 包含测试脚本
- [ ] 清理了临时文件

### ✅ 发布后验证
- [ ] GitHub Release可正常下载
- [ ] 三种下载方式都可用
- [ ] 在干净环境中测试通过

### ✅ 学生通知模板
```markdown
## 🎯 第1课：15分钟体验编译器

### 📥 下载（任选一种）
1. **一键下载**：`curl -sSL https://raw.githubusercontent.com/zhnt/minic-teaching/main/scripts/get-s0.sh | bash`
2. **手动下载**：https://github.com/zhnt/minic-teaching/releases/tag/s0

### 🚀 立即开始
```bash
cd minic-s0
make
echo "3 + 5" | ./build/minic
```

### 📚 学习目标
- 体验编译器的神奇之处
- 理解基础加法运算
- 建立学习信心

有问题随时提问！
```

## 🎯 关键成功要素
1. **零依赖**：学生只需gcc和make
2. **零配置**：下载即用
3. **即时反馈**：15秒见效
4. **多渠道**：提供多种下载方式
5. **可追踪**：GitHub统计下载量