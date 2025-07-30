# Minic阶段6：比较运算

## 🎯 学习目标
- 添加比较运算符（> < == !=）
- 理解布尔值和条件判断
- 掌握条件表达式

## 🚀 快速开始

### 获取阶段6代码
```bash
git clone https://github.com/zhnt/minic-s6.git
cd minic-s6
make
```

### 测试比较功能
```bash
echo "5 > 3" | ./build/minic  # 1.00 (true)
echo "10 == 10" | ./build/minic  # 1.00 (true)
echo "5 < 3" | ./build/minic  # 0.00 (false)
```

## 📚 20分钟学习指南

### 第1步：理解比较运算（5分钟）
比较运算符：
- `>` 大于
- `<` 小于  
- `>=` 大于等于
- `<=` 小于等于
- `==` 等于
- `!=` 不等于

### 第2步：实现比较功能（10分钟）
需要添加：
- 新的比较token
- 比较表达式的解析规则
- 布尔值的表示（1.0为true，0.0为false）

### 第3步：条件表达式测试（5分钟）
```bash
# 基础比较
echo "10 > 5" | ./build/minic  # 1.00

# 变量比较
result=$(echo "x = 10; y = 20; x < y" | ./build/minic)  # 1.00
echo $result
```

## 🔍 实现要点

### 1. 比较token定义
```c
TOKEN_GREATER,    // >
TOKEN_GREATER_EQUAL,  // >=
TOKEN_LESS,       // <
TOKEN_LESS_EQUAL, // <=
TOKEN_EQUAL_EQUAL, // ==
TOKEN_BANG_EQUAL,  // !=
```

### 2. 布尔值表示
```c
// true = 1.0, false = 0.0
double bool_to_double(bool value) {
    return value ? 1.0 : 0.0;
}
```

### 3. 比较字节码
```c
// OP_GREATER, OP_LESS, OP_EQUAL, OP_NOT_EQUAL
```

## 🎯 完成标准
- [ ] 实现所有比较运算符
- [ ] 正确处理布尔值
- [ ] 支持变量间的比较
- [ ] 通过所有测试用例

## 📋 测试用例
```bash
# 基础比较
echo "10 > 5" | ./build/minic  # 1.00
echo "7 < 3" | ./build/minic  # 0.00
echo "5 == 5" | ./build/minic  # 1.00
echo "4 != 4" | ./build/minic  # 0.00

# 变量比较
echo "score = 85; score >= 60" | ./build/minic  # 1.00
```

## 📋 解锁下一阶段
完成本阶段后，老师会发布阶段7的代码。

## 📊 当前阶段信息
- **阶段**：6/12
- **功能**：比较运算
- **时间**：20分钟学习
- **状态**：已解锁

---
**记住：比较运算是条件判断的基础，让程序有了决策能力！**