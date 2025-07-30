# Minic阶段5：变量持久化

## 🎯 学习目标
- 实现变量存储和读取
- 理解内存管理机制
- 掌握符号表概念

## 🚀 快速开始

### 获取阶段5代码
```bash
git clone https://github.com/zhnt/minic-s5.git
cd minic-s5
make
```

### 测试变量功能
```bash
echo "x = 10; y = 20; x + y" | ./build/minic  # 30.00
echo "a = 5; a = a + 1; a" | ./build/minic  # 6.00
```

## 📚 20分钟学习指南

### 第1步：理解变量存储（5分钟）
变量需要：
- 存储变量名
- 存储变量值
- 支持读取和更新

### 第2步：实现符号表（10分钟）
需要添加：
- `src/table.c` - 哈希表实现
- `src/table.h` - 符号表接口
- 修改`src/vm.c` - 变量存储逻辑

### 第3步：变量操作测试（5分钟）
```bash
# 变量赋值
echo "price = 100; tax = 0.1; total = price * (1 + tax); total" | ./build/minic
# 110.00
```

## 🔍 实现要点

### 1. 变量存储结构
```c
typedef struct {
    char* name;
    double value;
} Variable;
```

### 2. 符号表操作
```c
// 设置变量
void set_variable(const char* name, double value);

// 获取变量
double get_variable(const char* name);
```

### 3. 作用域处理
```c
// 全局变量作用域
// 简单实现，暂不支持局部作用域
```

## 🎯 完成标准
- [ ] 支持变量定义和赋值
- [ ] 支持变量读取
- [ ] 支持变量值更新
- [ ] 通过所有测试用例

## 📋 测试用例
```bash
# 基础赋值
echo "x = 42; x" | ./build/minic  # 42.00

# 变量更新
echo "x = 10; x = x + 5; x" | ./build/minic  # 15.00

# 多变量
echo "a = 1; b = 2; c = 3; a + b + c" | ./build/minic  # 6.00
```

## 📋 解锁下一阶段
完成本阶段后，老师会发布阶段6的代码。

## 📊 当前阶段信息
- **阶段**：5/12
- **功能**：变量持久化
- **时间**：25分钟学习
- **状态**：已解锁

---
**记住：变量让程序有了记忆，这是计算的基础！**