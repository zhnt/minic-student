# 教师发布指南：逐个阶段解锁模式

## 🎯 发布策略：独立仓库 + 逐个解锁

### 仓库架构设计
```
zhnt/minic-s0  # 阶段0：加法计算器
zhnt/minic-s1  # 阶段1：词法分析观察
zhnt/minic-s2  # 阶段2：减法实现
...
zhnt/minic-s12 # 阶段12：完整编译器
```

## 📋 阶段发布流程

### 1. 创建阶段仓库模板

#### 阶段0发布（当前）
```bash
# 创建阶段0仓库
cd /Users/zhnt/workspace/compile/minic-s0
git init
git add .
git commit -m "Minic阶段0：加法计算器"
git remote add origin https://github.com/zhnt/minic-s0.git
git push -u origin main
```

#### 阶段1准备模板
```bash
# 复制阶段0作为模板
cp -r /Users/zhnt/workspace/compile/minic-s0 /Users/zhnt/workspace/compile/minic-s1

# 修改阶段1内容
cd /Users/zhnt/workspace/compile/minic-s1
# 修改README.md、tasks.md等
# 添加阶段1特有的代码修改标记
```

### 2. 阶段发布时间表

| 阶段 | 发布时间 | 发布内容 | 学生通知 |
|------|----------|----------|----------|
| s0   | 第1节课前 | 加法计算器 | "体验编译器魔力" |
| s1   | 第2节课前 | 词法分析观察 | "解锁编译器第一步" |
| s2   | 第3节课前 | 减法实现 | "扩展你的编译器" |
| ...  | ...       | ...        | ... |
| s12  | 课程结束 | 完整项目 | "编译大师认证" |

### 3. 学生通知模板

#### 阶段0通知（课前发布）
```markdown
## 🎯 第1课：体验编译器魔力

### 📥 获取阶段0
```bash
git clone https://github.com/zhnt/minic-s0.git
cd minic-s0
make
echo "3 + 5" | ./build/minic
```

### 🎯 学习目标（15分钟）
- 体验编译器的神奇之处
- 理解基础加法运算
- 建立学习信心

### ⏰ 完成时间
课内15分钟体验，课后可继续探索

### 🔒 解锁条件
完成本阶段后，老师会发布阶段1代码！
```

#### 阶段1通知（完成s0后发布）
```markdown
## 🎉 恭喜完成阶段0！

### 🔓 阶段1已解锁！
```bash
git clone https://github.com/zhnt/minic-s1.git
cd minic-s1
make
echo "10 + 20" | ./build/minic -vt
```

### 🎯 新挑战：词法分析观察
- 学习什么是token
- 观察编译器如何"看懂"代码
- 掌握调试工具使用

### ⚡ 快速开始
15分钟掌握编译器第一步！
```

### 4. 自动化发布脚本

#### 创建阶段发布器
```bash
#!/bin/bash
# publish-stage.sh STAGE_NUMBER

STAGE_NUM=$1
STAGE_DIR="/Users/zhnt/workspace/compile/minic-s$STAGE_NUM"
REPO_NAME="minic-s$STAGE_NUM"

cd "$STAGE_DIR"

# 更新README
cat > README.md << EOF
# Minic阶段$STAGE_NUM：$(get_stage_name $STAGE_NUM)

## 🎯 学习目标
$(get_stage_goal $STAGE_NUM)

## 🚀 快速开始
```bash
git clone https://github.com/zhnt/minic-s$STAGE_NUM.git
cd minic-s$STAGE_NUM
make
$(get_stage_demo $STAGE_NUM)
```

## 📋 解锁信息
- **阶段**：$STAGE_NUM/12
- **前一阶段**：$(prev_stage_url $STAGE_NUM)
- **下一解锁**：$(next_stage_info $STAGE_NUM)
EOF

# 发布到GitHub
git init
git add .
git commit -m "Minic阶段$STAGE_NUM：$(get_stage_name $STAGE_NUM)"
git remote add origin https://github.com/zhnt/minic-s$STAGE_NUM.git
git push -u origin main
```

### 5. 进度追踪系统

#### 创建学生进度表
```markdown
## 📊 班级进度追踪

| 学生 | s0完成 | s1完成 | s2完成 | 当前阶段 |
|------|--------|--------|--------|----------|
| 张三 | ✅ | ✅ | ⏳ | s2 |
| 李四 | ✅ | ⏳ | ❌ | s1 |
| 王五 | ✅ | ✅ | ✅ | s3 |

### 🎯 阶段解锁状态
- ✅ **s0**：已发布（全员可用）
- ✅ **s1**：张三、王五已解锁
- ⏳ **s2**：张三进行中，李四待解锁
- 🔒 **s3-s12**：后续阶段
```

### 6. 教师控制台

#### 一键发布所有阶段
```bash
#!/bin/bash
# teacher-console.sh

echo "🎓 Minic教学控制台"
echo "1. 发布阶段0"
echo "2. 发布阶段1" 
echo "3. 发布阶段2"
echo "4. 查看学生进度"
echo "5. 发送阶段解锁通知"

read -p "选择操作：" choice
case $choice in
    1) ./publish-stage.sh 0 ;;
    2) ./publish-stage.sh 1 ;;
    3) ./publish-stage.sh 2 ;;
    4) ./view-progress.sh ;;
    5) ./send-unlock-notification.sh ;;
esac
```

## 🎯 教学优势

### ✅ 渐进式解锁
- **心理激励**：完成才有下一阶段
- **学习节奏**：控制学生进度
- **成就感**：每阶段都有收获

### ✅ 技术简单
- **统一入口**：git clone即可
- **零配置**：每个阶段独立完整
- **跨平台**：支持所有系统

### ✅ 教师可控
- **进度管理**：完全掌控发布节奏
- **灵活调整**：可随时修改阶段内容
- **反馈收集**：GitHub Issues收集问题

### ✅ 学生友好
- **清晰路径**：12个里程碑
- **即时反馈**：每个阶段15分钟见效
- **成就系统**：完成即解锁

## 📱 课堂使用示例

### 第1节课
```bash
# 教师发布
./publish-stage.sh 0

# 学生获取
git clone https://github.com/zhnt/minic-s0.git
```

### 第2节课
```bash
# 教师检查进度后发布
git clone https://github.com/zhnt/minic-s0.git --depth 1
# 统计学生完成情况

# 发布阶段1
./publish-stage.sh 1
```

## 🎓 完整发布计划

| 周次 | 发布阶段 | 发布内容 | 学生通知 |
|------|----------|----------|----------|
| 第1周 | s0 | 加法计算器 | "体验编译器魔力" |
| 第2周 | s1 | 词法分析观察 | "读懂编译器眼睛" |
| 第3周 | s2 | 减法实现 | "扩展你的编译器" |
| 第4周 | s3 | 乘法实现 | "掌握运算符扩展" |
| 第5周 | s4 | 括号支持 | "理解语法优先级" |
| ...  | ... | ... | ... |
| 第12周 | s12 | 完整项目 | "编译大师认证" |

---

**记住：每个阶段都是独立的GitHub仓库，学生git clone即可开始新的学习旅程！**