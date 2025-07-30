# Minic阶段1：词法分析观察

## 🎯 学习目标
- 理解什么是token（记号）
- 观察编译器如何"看懂"代码
- 掌握调试工具使用

## 🚀 快速开始

### 获取阶段1代码
```bash
# 获取完整学习系统（推荐）
git clone https://github.com/zhnt/minic-student.git
cd minic-student
git checkout stage-1
cd stage-1
make
```

### 观察token化过程
```bash
# 查看token序列
./build/minic -vt   # 输入：10 + 20 * 30
# 输出：NUMBER(10) PLUS NUMBER(20) STAR NUMBER(30)

# 理解每个token的含义
# NUMBER: 数字
# PLUS: 加号 +
# STAR: 乘号 *
```

## 📚 15分钟学习指南

### 第1步：观察基础token（5分钟）
```bash
# 数字token
echo "42" | ./build/minic -vt    # NUMBER(42)

# 运算符token
echo "3 + 5" | ./build/minic -vt  # NUMBER(3) PLUS NUMBER(5)

# 变量token
echo "x = 10" | ./build/minic -vt  # IDENTIFIER(x) EQUAL NUMBER(10)
```

### 第2步：复杂表达式（5分钟）
```bash
# 混合运算
echo "a + b * c" | ./build/minic -vt
# IDENTIFIER(a) PLUS IDENTIFIER(b) STAR IDENTIFIER(c)

# 括号
echo "(1 + 2) * 3" | ./build/minic -vt
# LEFT_PAREN NUMBER(1) PLUS NUMBER(2) RIGHT_PAREN STAR NUMBER(3)
```

### 第3步：调试模式（5分钟）
```bash
# 完整调试信息
./build/minic -v    # 输入：var x = 100 + 200
# 将显示：
# 1. 源代码
# 2. Token序列
# 3. 抽象语法树
# 4. 字节码
# 5. 执行结果
```

## 🔍 Token类型速查表

| Token类型 | 示例 | 说明 |
|-----------|------|------|
| NUMBER | 42, 3.14 | 数字常量 |
| IDENTIFIER | x, total | 变量名 |
| PLUS | + | 加法运算 |
| STAR | * | 乘法运算 |
| EQUAL | = | 赋值符号 |
| SEMICOLON | ; | 语句结束 |
| LEFT_PAREN | ( | 左括号 |
| RIGHT_PAREN | ) | 右括号 |

## 🎯 完成标准
完成以下任意两项即表示阶段1掌握：
- [ ] 能解释什么是token
- [ ] 能识别5种以上的token类型
- [ ] 能使用-vt选项调试任意表达式

## 📋 解锁下一阶段
完成本阶段后，老师会宣布解锁阶段2：
```bash
# 返回仓库根目录
cd ..
git checkout stage-2
```

## 📊 当前阶段信息
- **阶段**：1/12
- **功能**：词法分析观察
- **时间**：15分钟学习
- **状态**：已解锁

---
**记住：理解token是编译器学习的第一步！**