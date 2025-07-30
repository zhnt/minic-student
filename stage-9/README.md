# Minic阶段9：函数定义

## 🎯 学习目标
- 实现函数定义和调用
- 理解参数传递机制
- 掌握作用域和返回机制

## 🚀 快速开始

### 获取阶段9代码
```bash
git clone https://github.com/zhnt/minic-s9.git
cd minic-s9
make
```

### 测试函数功能
```bash
echo "func add(a, b) { return a + b; } add(3, 4)" | ./build/minic  # 7.00
echo "func square(x) { return x * x; } square(5)" | ./build/minic  # 25.00
```

## 📚 30分钟学习指南

### 第1步：理解函数概念（5分钟）
函数组成：
- 函数名
- 参数列表
- 函数体
- 返回值

### 第2步：实现函数语法（15分钟）
需要添加：
- func关键字token
- 参数解析
- 函数调用机制
- 返回值处理
- 局部变量作用域

### 第3步：函数调用测试（10分钟）
```bash
# 基础函数
echo "func double(n) { return n * 2; } double(7)" | ./build/minic  # 14.00

# 递归函数
echo "func fact(n) { if (n <= 1) return 1; return n * fact(n - 1); } fact(5)" | ./build/minic  # 120.00
```

## 🔍 实现要点

### 1. 新增token
```c
TOKEN_FUNC,     // func关键字
TOKEN_RETURN,   // return关键字
TOKEN_COMMA,    // 参数分隔符
```

### 2. 函数调用机制
```c
// 调用栈管理
// 参数传递
// 返回值处理
```

### 3. 作用域管理
```c
// 局部变量
// 函数参数
// 全局变量
```

## 🎯 完成标准
- [ ] 实现函数定义语法
- [ ] 支持函数调用
- [ ] 支持参数传递
- [ ] 支持返回值
- [ ] 支持递归调用
- [ ] 通过所有测试用例

## 📋 测试用例
```bash
# 基础函数
echo "func add(a, b) { return a + b; } add(3, 4)" | ./build/minic  # 7.00

# 无参数函数
echo "func pi() { return 3.14159; } pi()" | ./build/minic  # 3.14159

# 多参数函数
echo "func max(a, b) { if (a > b) return a; return b; } max(10, 20)" | ./build/minic  # 20.00

# 递归函数
echo "func fib(n) { if (n <= 1) return n; return fib(n-1) + fib(n-2); } fib(6)" | ./build/minic  # 8.00
```

## 📋 解锁下一阶段
完成本阶段后，老师会发布阶段10的代码。

## 📊 当前阶段信息
- **阶段**：9/12
- **功能**：函数定义
- **时间**：30分钟学习
- **状态**：已解锁

---
**记住：函数是代码复用的基石，让程序结构化且易于维护！**