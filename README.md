# 🎯 Minic学生代码库 - 渐进式编译器学习系统

## 🚀 学生快速开始（30秒上手）

### 1. 获取代码（仅需一次克隆）
```bash
git clone https://github.com/zhnt/minic-student.git
cd minic-student
```

### 2. 体验当前阶段
```bash
# 查看所有可用阶段
git tag -l stage-*

# 老师宣布后切换到当前阶段
git fetch origin      # 获取最新标签
git checkout stage-0  # 阶段0：加法计算器

# 立即体验
cd stage-0
make
echo "3 + 5" | ./minic        # 8.00
echo "x = 10 + 5; x" | ./minic  # 15.00
```

## 📋 12阶段学习路径

| 阶段 | 功能 | 学习时间 | 难度 | 获取方式 |
|------|------|----------|------|----------|
| [stage-0](stage-0/README.md) | 加法计算器 | 15分钟 | ⭐ | `git checkout stage-0` |
| [stage-1](stage-1/README.md) | 词法分析观察 | 15分钟 | ⭐⭐ | `git checkout stage-1` |
| [stage-2](stage-2/README.md) | 减法实现 | 15分钟 | ⭐⭐ | `git checkout stage-2` |
| [stage-3](stage-3/README.md) | 乘法实现 | 20分钟 | ⭐⭐⭐ | `git checkout stage-3` |
| [stage-4](stage-4/README.md) | 括号支持 | 20分钟 | ⭐⭐⭐ | `git checkout stage-4` |
| [stage-5](stage-5/README.md) | 变量持久化 | 25分钟 | ⭐⭐⭐⭐ | `git checkout stage-5` |
| [stage-6](stage-6/README.md) | 比较运算 | 20分钟 | ⭐⭐⭐ | `git checkout stage-6` |
| [stage-7](stage-7/README.md) | while循环 | 25分钟 | ⭐⭐⭐⭐ | `git checkout stage-7` |
| [stage-8](stage-8/README.md) | for循环 | 20分钟 | ⭐⭐⭐ | `git checkout stage-8` |
| [stage-9](stage-9/README.md) | 函数定义 | 30分钟 | ⭐⭐⭐⭐⭐ | `git checkout stage-9` |
| [stage-10](stage-10/README.md) | 数组字符串 | 30分钟 | ⭐⭐⭐⭐ | `git checkout stage-10` |
| [stage-11](stage-11/README.md) | 标准库 | 30分钟 | ⭐⭐⭐⭐ | `git checkout stage-11` |
| [stage-12](stage-12/README.md) | 完整编译器 | 自由发挥 | ⭐⭐⭐⭐⭐ | `git checkout stage-12` |

## 🔓 阶段解锁流程

### 学生使用步骤：
1. **一次性克隆**：`git clone https://github.com/zhnt/minic-student.git`
2. **查看可用阶段**：`git tag -l stage-*`
3. **老师宣布解锁**："同学们，阶段N已解锁！"
4. **获取最新阶段**：`git fetch origin`
5. **切换阶段**：`git checkout stage-N`
6. **开始学习**：`cd stage-N && make && ./build/minic`

### 教师控制流程：
- **准备阶段**：完善阶段代码
- **发布阶段**：`./publish-stage.sh N "发布说明"`
- **通知学生**："阶段N已解锁！"
- **监控进度**：查看学生提交

## 📱 完整学习体验

### 第1天：阶段0体验
```bash
# 学生首次获取
git clone https://github.com/zhnt/minic-student.git
cd minic-student

# 老师宣布："阶段0已发布！"
git checkout stage-0
cd stage-0
make
echo "3 + 5" | ./build/minic        # 8.00 ✨
./build/minic -vt  # 观察token
```

### 第2天：阶段1解锁
```bash
# 老师宣布："阶段1已解锁！"
git fetch origin      # 获取新标签
git checkout stage-1
cd stage-1
make
echo "10 + 20" | ./build/minic -vt  # 观察token
```

## 🔧 系统要求

| 系统 | 要求 | 安装命令 |
|------|------|----------|
| **Linux** | gcc, make, git | 通常已预装 |
| **macOS** | Xcode命令行工具, git | `xcode-select --install` |
| **Windows** | WSL + gcc/make/git | 推荐使用WSL |

## 🎓 学习特色

### ✅ 渐进式解锁
- **心理激励**：完成才有下一阶段
- **学习节奏**：控制进度，避免信息过载
- **成就感**：每15-30分钟一个小胜利

### ✅ 零配置体验
- **单仓库**：只需`git clone`一次
- **标准工具**：仅需gcc/make
- **跨平台**：Linux/macOS/Windows(WSL)

### ✅ 即时反馈
- **15秒见效**：每个阶段都有立即的反馈
- **可视化调试**：`-vt`查看token，`-va`查看AST
- **错误提示**：清晰的编译错误信息

## 📞 获取帮助

### 遇到问题？
1. **查看帮助**：每个阶段都有详细的README.md
2. **检查系统**：确认gcc和make已安装
3. **联系老师**：通过GitHub Issues或课堂提问

### 学习资源
- [教师发布指南](TEACHER-GUIDE.md)
- [学生Agent工具](https://github.com/zhnt/minic-student-agent)

---

**🎯 现在学生体验：**
```bash
# 30秒内开始
1. git clone https://github.com/zhnt/minic-student.git
2. cd minic-student && git fetch origin && git checkout stage-0
3. cd stage-0 && make && echo "3 + 5" | ./build/minic
```

**记住：老师会逐个宣布解锁下一阶段！** 🚀