# Minic阶段11：标准库

## 🎯 学习目标
- 实现数学标准库函数
- 添加输入输出功能
- 掌握库函数的设计和实现

## 🚀 快速开始

### 获取阶段11代码
```bash
git clone https://github.com/zhnt/minic-s11.git
cd minic-s11
make
```

### 测试标准库功能
```bash
echo "sqrt(16)" | ./build/minic  # 4.00
echo "pow(2, 3)" | ./build/minic  # 8.00
echo "sin(0)" | ./build/minic  # 0.00
```

## 📚 30分钟学习指南

### 第1步：理解标准库概念（5分钟）
标准库包含：
- 数学函数：sqrt, pow, sin, cos, tan
- 实用函数：abs, max, min, random
- 输入输出：print, input

### 第2步：实现数学函数（15分钟）
需要添加：
- 数学函数token
- 函数注册机制
- 标准库模块
- 错误处理

### 第3步：标准库测试（10分钟）
```bash
# 数学函数测试
echo "max(10, 20) + min(5, 15)" | ./build/minic  # 25.00
echo "abs(-42)" | ./build/minic  # 42.00
```

## 🔍 实现要点

### 1. 标准库函数列表
```c
// 数学函数
sqrt(x)    // 平方根
pow(x, y)  // 幂运算
sin(x)     // 正弦
cos(x)     // 余弦
tan(x)     // 正切
abs(x)     // 绝对值
max(x, y)  // 最大值
min(x, y)  // 最小值
```

### 2. 函数注册机制
```c
typedef struct {
    const char* name;
    double (*function)(int, double*);
} NativeFunction;
```

### 3. 标准库模块
```c
// native.c - 标准库实现
// native.h - 函数声明
```

## 🎯 完成标准
- [ ] 实现基础数学函数
- [ ] 实现实用函数
- [ ] 支持函数注册
- [ ] 提供完整标准库
- [ ] 通过所有测试用例

## 📋 测试用例
```bash
# 数学计算
sqrt(25)  # 5.00
pow(2, 8)  # 256.00
abs(-100)  # 100.00

# 实用函数
max(1, 2)  # 2.00
min(10, 5)  # 5.00

# 综合应用
area = pi() * pow(5, 2)  # 78.54 (圆的面积)
```

## 📋 解锁下一阶段
完成本阶段后，老师会发布阶段12的代码。

## 📊 当前阶段信息
- **阶段**：11/12
- **功能**：标准库
- **时间**：30分钟学习
- **状态**：已解锁

---
**记住：标准库让语言变得实用，是完整编程语言的标志！**