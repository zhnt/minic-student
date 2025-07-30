# Minic阶段0：加法计算器

## 🎯 学习目标
- 15分钟内体验编译器的神奇之处
- 理解基础运算过程
- 建立学习信心

## 🚀 快速开始（仅需1分钟）

### 获取当前阶段
```bash
# 获取完整学习系统（推荐）
git clone https://github.com/zhnt/minic-student.git
cd minic-student
git checkout stage-0
cd stage-0
make
echo "3 + 5" | ./build/minic        # Result: 8.00
```

### 系统兼容性
- **Linux**：直接可用（gcc/make已预装）
- **macOS**：需要 `xcode-select --install`
- **Windows**：需要WSL（推荐）或MinGW

## 📚 15分钟体验指南

### 第1步：基础体验（2分钟）
```bash
# 基础加法
echo "3 + 5" | ./build/minic        # 8.00
echo "100 + 200" | ./build/minic    # 300.00

# 变量赋值
echo "x = 10 + 5; x" | ./build/minic  # 15.00
```

### 第2步：观察内部（5分钟）
```bash
# 观察token
./build/minic -vt   # 输入：10 + 20
# 输出：NUMBER(10) PLUS NUMBER(20)

# 观察AST
./build/minic -va   # 输入：10 + 20
# 输出：(+ 10 20)

# 完整调试
./build/minic -v    # 输入：10 + 20
# 显示完整编译流程
```

### 第3步：文件编译（3分钟）
```bash
echo "result = 15 + 25; result" > mycalc.mc
./build/minic mycalc.mc  # 40.00
```

### 第4步：交互探索（5分钟）
```bash
./build/minic
minic> 42 + 58
100.00
minic> x = 50 + 50; x
100.00
minic> exit
```

## 🔧 系统要求
- **编译器**：gcc/clang (支持C99)
- **构建工具**：make
- **依赖**：仅标准库（无需额外安装）

## 🎯 完成标准
完成以下任意一项即表示阶段0掌握：
- [ ] 成功运行5个不同的加法运算
- [ ] 观察到token和AST的输出
- [ ] 创建并运行了一个.m文件

## 📋 解锁下一阶段
完成本阶段后，老师会宣布解锁阶段1：
```bash
# 返回仓库根目录
cd ..
git checkout stage-1
```

## 🎓 教学特色
- ✅ **阶段解锁**：完成当前阶段才能获取下一阶段
- ✅ **零配置**：git clone即可使用
- ✅ **即时反馈**：15秒见效
- ✅ **渐进学习**：小步快跑，步步为营

## 📊 当前阶段信息
- **阶段**：0/12
- **功能**：加法计算器
- **时间**：15分钟体验
- **状态**：已发布

---
**记住：完成本阶段后，老师会宣布解锁下一阶段！**