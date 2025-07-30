# Minic阶段8：for循环

## 🎯 学习目标
- 实现for循环语句
- 理解计数循环模式
- 掌握初始化-条件-更新循环结构

## 🚀 快速开始

### 获取阶段8代码
```bash
git clone https://github.com/zhnt/minic-s8.git
cd minic-s8
make
```

### 测试for循环功能
```bash
echo "sum = 0; for (i = 1; i <= 5; i = i + 1) sum = sum + i; sum" | ./build/minic  # 15.00
echo "for (n = 10; n > 0; n = n - 1) print(n)" | ./build/minic  # 输出10到1
```

## 📚 20分钟学习指南

### 第1步：理解for循环结构（5分钟）
for循环语法：
```
for (初始化; 条件; 更新) {
    循环体
}
```

### 第2步：实现for语句（10分钟）
需要添加：
- for关键字token
- 三部分表达式解析
- 代码生成优化

### 第3步：计数循环测试（5分钟）
```bash
# 基础计数循环
echo "total = 0; for (i = 1; i <= 3; i = i + 1) total = total + i; total" | ./build/minic  # 6.00
```

## 🔍 实现要点

### 1. 新增token
```c
TOKEN_FOR,  // for关键字
```

### 2. for循环结构
```c
// 初始化 -> 条件判断 -> 循环体 -> 更新 -> 条件判断...
```

### 3. 代码优化
```c
// 可以优化为while循环的语法糖
// 但保持for循环的清晰结构
```

## 🎯 完成标准
- [ ] 实现for循环语法
- [ ] 支持初始化表达式
- [ ] 支持条件判断
- [ ] 支持更新表达式
- [ ] 通过所有测试用例

## 📋 测试用例
```bash
# 基础for循环
echo "sum = 0; for (i = 1; i <= 5; i = i + 1) sum = sum + i; sum" | ./build/minic  # 15.00

# 递减循环
echo "result = 1; for (n = 5; n > 0; n = n - 1) result = result * n; result" | ./build/minic  # 120.00

# 与while的等价性
echo "i = 0; while (i < 3) { i = i + 1; } i" | ./build/minic  # 3.00
```

## 📋 解锁下一阶段
完成本阶段后，老师会发布阶段9的代码。

## 📊 当前阶段信息
- **阶段**：8/12
- **功能**：for循环
- **时间**：20分钟学习
- **状态**：已解锁

---
**记住：for循环是计数循环的优雅表达，让代码更清晰！**