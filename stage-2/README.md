# Minic阶段2：减法实现

## 🎯 学习目标
- 扩展编译器支持减法运算
- 理解运算符的添加过程
- 掌握代码修改技巧

## 🚀 快速开始

### 获取阶段2代码
```bash
# 获取完整学习系统（推荐）
git clone https://github.com/zhnt/minic-student.git
cd minic-student
git checkout stage-2
cd stage-2
make
```

### 测试减法功能
```bash
echo "10 - 3" | ./build/minic  # 7.00
echo "100 - 50 - 25" | ./build/minic  # 25.00
```

## 📚 15分钟扩展指南

### 第1步：理解现有代码（5分钟）
```c
// 在lexer.h中查找token定义
// 在parser.c中查找加法处理
// 在compiler.c中查找代码生成
```

### 第2步：添加减法支持（5分钟）
需要修改的文件：
- `src/lexer.c` - 添加MINUS token
- `src/parser.c` - 添加减法语法规则
- `src/compiler.c` - 生成减法字节码

### 第3步：测试验证（5分钟）
```bash
make clean && make
./build/minic -vt  # 输入：20 - 5 - 3
# 应该看到：MINUS token和正确的计算结果
```

## 🔍 代码修改提示

### 1. 添加MINUS token
```c
// 在lexer.h中添加
TOKEN_MINUS,
```

### 2. 识别减号字符
```c
// 在lexer.c的switch中添加
case '-': return TOKEN_MINUS;
```

### 3. 扩展语法规则
```c
// 在parser.c中添加减法表达式处理
// 参考加法表达式的处理方式
```

## 🎯 完成标准
完成以下任务即表示阶段2掌握：
- [ ] 成功实现减法运算功能
- [ ] 能通过所有测试用例
- [ ] 理解运算符添加的完整流程

## 📋 测试用例
```bash
# 基础减法
echo "10 - 3" | ./build/minic  # 7.00

# 连续减法
echo "100 - 20 - 30" | ./build/minic  # 50.00

# 混合运算
echo "50 + 30 - 20" | ./build/minic  # 60.00
```

## 📋 解锁下一阶段
完成本阶段后，老师会宣布解锁阶段3：
```bash
# 返回仓库根目录
cd ..
git checkout stage-3
```

## 📊 当前阶段信息
- **阶段**：2/12
- **功能**：减法实现
- **时间**：15分钟扩展
- **状态**：已解锁

---
**记住：每个运算符的添加都是一次小胜利！**