# Minic阶段7：while循环

## 🎯 学习目标
- 实现while循环语句
- 理解循环控制流程
- 掌握跳转指令

## 🚀 快速开始

### 获取阶段7代码
```bash
git clone https://github.com/zhnt/minic-s7.git
cd minic-s7
make
```

### 测试循环功能
```bash
echo "i = 0; while (i < 5) i = i + 1; i" | ./build/minic  # 5.00
echo "sum = 0; i = 1; while (i <= 10) { sum = sum + i; i = i + 1; } sum" | ./build/minic  # 55.00
```

## 📚 25分钟学习指南

### 第1步：理解循环概念（5分钟）
while循环语法：
```
while (条件) {
    循环体
}
```

### 第2步：实现循环语句（15分钟）
需要添加：
- while关键字token
- 循环条件解析
- 跳转指令（循环开始、结束）
- 代码块处理

### 第3步：循环测试（5分钟）
```bash
# 简单计数器
echo "count = 0; while (count < 3) count = count + 1; count" | ./build/minic  # 3.00
```

## 🔍 实现要点

### 1. 新增token
```c
TOKEN_WHILE,    // while关键字
TOKEN_LEFT_BRACE,   // {
TOKEN_RIGHT_BRACE,  // }
```

### 2. 跳转指令
```c
OP_JUMP,        // 无条件跳转
OP_JUMP_IF_FALSE, // 条件为假时跳转
OP_LOOP,        // 循环跳转
```

### 3. 代码生成策略
```c
// 循环开始 -> 条件判断 -> 循环体 -> 跳转回开始
```

## 🎯 完成标准
- [ ] 实现while循环语法
- [ ] 支持循环条件判断
- [ ] 支持代码块（花括号）
- [ ] 支持无限循环和正常退出
- [ ] 通过所有测试用例

## 📋 测试用例
```bash
# 基础循环
echo "i = 0; while (i < 3) i = i + 1; i" | ./build/minic  # 3.00

# 计算1到10的和
echo "sum = 0; i = 1; while (i <= 10) { sum = sum + i; i = i + 1; } sum" | ./build/minic  # 55.00

# 阶乘计算
echo "n = 5; result = 1; while (n > 0) { result = result * n; n = n - 1; } result" | ./build/minic  # 120.00
```

## 📋 解锁下一阶段
完成本阶段后，老师会发布阶段8的代码。

## 📊 当前阶段信息
- **阶段**：7/12
- **功能**：while循环
- **时间**：25分钟学习
- **状态**：已解锁

---
**记住：循环让程序有了重复执行的能力，是自动化计算的关键！**