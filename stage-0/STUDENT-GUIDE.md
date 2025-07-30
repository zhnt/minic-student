# 🎯 Minic加法编译器 - 学生学习指南

## 📖 前言：为什么从加法开始？

加法是最基础的数学运算，但也是理解编译器工作原理的最佳入口。通过实现一个简单的加法编译器，你将：
- **15分钟内**获得编译器工作的直观体验
- **无需恐惧**复杂的编译器理论
- **建立信心**继续后续阶段学习

## 🚀 立即体验（30秒上手）

### 第1步：获取代码
```bash
git clone https://github.com/zhnt/minic-student.git
cd minic-student
git checkout stage-0
cd stage-0
```

### 第2步：构建运行
```bash
make                    # 构建编译器
echo "3 + 5" | ./build/minic        # 输出：8.00
```

### 第3步：验证成功
```bash
echo "100 + 200" | ./build/minic    # 输出：300.00
echo "x = 10 + 5; x" | ./build/minic  # 输出：15.00
```

## 🔍 编译器内部探秘

### 1. 三层架构理解
我们的加法编译器采用经典的三层架构：

```
源代码 → 词法分析 → 语法分析 → 代码生成 → 虚拟机执行
   ↑        ↑           ↑          ↑           ↑
"3+5" → [3,+,5] → (+ 3 5) → 字节码 → 8.00
```

### 2. 关键文件解读

#### 📁 核心文件结构
```
stage-0/
├── src/           # 源代码
│   ├── lexer.c    # 词法分析器：把字符变成token
│   ├── parser.c   # 语法分析器：把token变成AST
│   ├── compiler.c # 代码生成器：把AST变成字节码
│   └── vm.c       # 虚拟机：执行字节码
├── include/       # 头文件定义
├── tests/         # 测试用例
└── Makefile       # 构建脚本
```

#### 🔍 关键函数速查
| 文件 | 关键函数 | 作用 |
|------|----------|------|
| lexer.c | scan_token() | 读取字符生成token |
| parser.c | parse_expression() | 解析表达式生成AST |
| compiler.c | compile_ast() | 编译AST生成字节码 |
| vm.c | interpret() | 执行字节码得到结果 |

## 🎯 15分钟深度学习路径

### 第1阶段：直观体验（5分钟）

#### 观察token化过程
```bash
./build/minic -vt   # 输入：42 + 58
# 输出：NUMBER(42) PLUS NUMBER(58)
```

#### 观察AST结构
```bash
./build/minic -va   # 输入：42 + 58
# 输出：(+ 42 58)
```

#### 观察完整流程
```bash
./build/minic -v    # 输入：42 + 58
# 输出：
# 源代码：42 + 58
# Token：[NUMBER(42), PLUS, NUMBER(58)]
# AST：(+ 42 58)
# 字节码：PUSH 42, PUSH 58, ADD
# 结果：100.00
```

### 第2阶段：代码阅读（5分钟）

#### 1. 词法分析（lexer.c）
```c
// 关键代码片段
switch (c) {
    case '+': return TOKEN_PLUS;    // 识别加号
    case '0'...'9': return scan_number();  // 识别数字
    default: error("未知字符");
}
```

#### 2. 语法分析（parser.c）
```c
// 加法表达式解析
Expr *parse_expression() {
    Expr *left = parse_primary();    // 解析左操作数
    if (match(TOKEN_PLUS)) {         // 遇到加号
        Expr *right = parse_expression();  // 解析右操作数
        return make_binary(left, right);   // 创建二元表达式
    }
    return left;
}
```

#### 3. 代码生成（compiler.c）
```c
// 加法编译
void compile_binary(BinaryExpr *expr) {
    compile_ast(expr->left);   // 编译左操作数
    compile_ast(expr->right);  // 编译右操作数
    emit(OP_ADD);              // 生成加法指令
}
```

#### 4. 虚拟机执行（vm.c）
```c
// 加法指令执行
case OP_ADD: {
    double b = pop();          // 弹出右操作数
    double a = pop();          // 弹出左操作数
    push(a + b);               // 计算并压入结果
    break;
}
```

### 第3阶段：动手实践（5分钟）

#### 创建测试文件
```bash
# 测试加法运算
echo "total = 100 + 200 + 300; total" > myfirst.mc
./build/minic myfirst.mc  # 600.00
```

#### 交互式探索
```bash
./build/minic
minic> 1 + 2 + 3 + 4 + 5
15.00
minic> x = 100 + 200; y = x + 50; y
350.00
minic> exit
```

## 📊 学习检查清单

### 基础理解（必须完成）
- [ ] 能够解释：什么是编译器？
- [ ] 能够运行：至少5个不同的加法运算
- [ ] 能够观察：token、AST、字节码三个层次

### 进阶理解（选做）
- [ ] 能够阅读：lexer.c中的token识别逻辑
- [ ] 能够理解：parser.c中AST的构建过程
- [ ] 能够描述：从源代码到结果的完整流程

### 创新实践（挑战）
- [ ] 修改代码：添加新的运算符（如减号）
- [ ] 扩展功能：支持更多数字格式
- [ ] 调试技巧：使用-v, -vt, -va选项分析问题

## 🎓 学习建议

### 1. 先体验，后理解
不要急于理解所有代码，先通过15分钟体验建立直观感受。

### 2. 分层学习
- 第1层：会用即可（5分钟）
- 第2层：理解结构（10分钟）
- 第3层：阅读关键代码（15分钟）
- 第4层：尝试修改（额外时间）

### 3. 动手实践
每学一个概念，立即用实际例子验证。

### 4. 错误是学习机会
如果遇到编译错误，这是理解编译器如何处理错误的绝佳机会。

## 🔮 下一步预告
完成加法编译器后，你将进入阶段1：
- **词法分析观察**：深入理解编译器如何"看懂"代码
- **token概念**：学习编译器如何识别不同类型的语法元素
- **调试工具**：掌握-vt选项观察token化过程

## 📞 获取帮助

### 常见问题
1. **make失败**：确认已安装gcc和make
2. **运行无输出**：检查输入格式，确保使用echo管道
3. **理解困难**：先完成体验部分，理论可以慢慢理解

### 学习资源
- 代码注释：每个关键函数都有详细注释
- 测试文件：tests/目录下有示例用法
- 在线支持：GitHub Issues提问

---

**🎯 记住：你已经迈出了编译器学习的第一步！加法虽小，五脏俱全。从这里开始，你将逐步构建出完整的编译器。**

**现在就开始你的15分钟编译器之旅吧！**