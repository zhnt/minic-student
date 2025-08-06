# 🎯 减法实现完整指南

## 📋 项目结构分析

基于对现有加法编译器的深入分析，减法实现需要修改以下5个核心模块：

### 🏗️ 当前架构
```
源代码 → 词法分析 → 语法分析 → 代码生成 → 虚拟机执行
  "3-5" → [3,-,5] → (- 3 5) → 字节码 → -2.00
```

### 📁 需要修改的文件
| 模块 | 文件路径 | 修改内容 |
|------|----------|----------|
| **词法分析** | `include/minic/lexer.h` | 添加减号token类型 |
| **词法分析** | `src/lexer.c` | 识别'-'字符 |
| **语法分析** | `src/parser.c` | 解析减法表达式 |
| **字节码** | `include/minic/bytecode.h` | 添加OP_SUB指令 |
| **代码生成** | `src/compiler.c` | 生成减法指令 |
| **虚拟机** | `src/vm.c` | 执行减法运算 |

---

## 🔧 详细实现步骤

### 步骤1：扩展词法分析器（2分钟）

#### 1.1 添加减号token类型
**文件：`include/minic/lexer.h` 第4-12行**
```c
typedef enum {
    TOKEN_NUMBER,
    TOKEN_IDENTIFIER,
    TOKEN_PLUS,
    TOKEN_MINUS,    // ✅ 新增：减号token
    TOKEN_ASSIGN,
    TOKEN_SEMICOLON,
    TOKEN_EOF,
    TOKEN_ERROR
} TokenType;
```

#### 1.2 识别减号字符
**文件：`src/lexer.c` 第61-66行**
```c
switch (c) {
    case '+': return (Token){TOKEN_PLUS, 0, "", lex->line, lex->column};
    case '-': return (Token){TOKEN_MINUS, 0, "", lex->line, lex->column}; // ✅ 新增
    case '=': return (Token){TOKEN_ASSIGN, 0, "", lex->line, lex->column};
    case ';': return (Token){TOKEN_SEMICOLON, 0, "", lex->line, lex->column};
    default: return (Token){TOKEN_ERROR, 0, "", lex->line, lex->column};
}
```

#### 1.3 更新token类型字符串
**文件：`src/lexer.c` 第69-79行**
```c
const char* token_type_string(TokenType type) {
    switch (type) {
        case TOKEN_NUMBER: return "NUMBER";
        case TOKEN_IDENTIFIER: return "IDENTIFIER";
        case TOKEN_PLUS: return "PLUS";
        case TOKEN_MINUS: return "MINUS";    // ✅ 新增
        case TOKEN_ASSIGN: return "ASSIGN";
        case TOKEN_SEMICOLON: return "SEMICOLON";
        case TOKEN_EOF: return "EOF";
        case TOKEN_ERROR: return "ERROR";
    }
}
```

### 步骤2：扩展语法分析器（2分钟）

#### 2.1 解析减法表达式
**文件：`src/parser.c` 第40-63行**
```c
static ASTNode* parse_expression(Parser* parser) {
    ASTNode* left = parse_primary(parser);
    
    while (1) {
        switch (parser->current.type) {
            case TOKEN_PLUS:
                parser_consume(parser, TOKEN_PLUS);
                left = ast_binary_op('+', left, parse_primary(parser));
                break;
            case TOKEN_MINUS:  // ✅ 新增：处理减号
                parser_consume(parser, TOKEN_MINUS);
                left = ast_binary_op('-', left, parse_primary(parser));
                break;
            case TOKEN_ERROR:
                printf("Parse error: Unrecognized operator or character\n");
                exit(1);
            default:
                return left;
        }
    }
    
    return left;
}
```

### 步骤3：扩展字节码指令集（1分钟）

#### 3.1 添加OP_SUB指令
**文件：`include/minic/bytecode.h` 第4-10行**
```c
typedef enum {
    OP_LOADK,      // 加载常量到寄存器: R[A] = K[B]
    OP_ADD,        // 加法: R[A] = R[B] + R[C]
    OP_SUB,        // ✅ 新增：减法 R[A] = R[B] - R[C]
    OP_SETGLOBAL,  // 设置全局变量: G[A] = R[B]
    OP_GETGLOBAL,  // 获取全局变量: R[A] = G[B]
    OP_RETURN      // 返回: return R[A]
} Opcode;
```

### 步骤4：扩展代码生成器（2分钟）

#### 4.1 生成减法指令
**文件：`src/compiler.c` 第27-36行**
```c
case AST_BINARY_OP: {
    int left_reg = compile_expression(comp, expr->data.binary_op.left);
    int right_reg = compile_expression(comp, expr->data.binary_op.right);
    
    // ✅ 修改：根据操作符类型选择指令
    if (expr->data.binary_op.op == '+') {
        bytecode_add_instruction(comp->bc, OP_ADD, reg, left_reg, right_reg);
    } else if (expr->data.binary_op.op == '-') {
        bytecode_add_instruction(comp->bc, OP_SUB, reg, left_reg, right_reg);
    }
    return reg;
}
```

### 步骤5：扩展虚拟机（1分钟）

#### 5.1 执行减法运算
**文件：`src/vm.c` 第20-50行**
```c
case OP_LOADK:
    vm->registers[instr->a] = bc->constants[instr->b];
    break;
    
case OP_ADD:
    vm->registers[instr->a] = vm->registers[instr->b] + vm->registers[instr->c];
    break;
    
case OP_SUB:  // ✅ 新增：执行减法
    vm->registers[instr->a] = vm->registers[instr->b] - vm->registers[instr->c];
    break;
    
case OP_SETGLOBAL:
    vm->globals[instr->a] = vm->registers[instr->b];
    break;
```

### 步骤6：扩展调试模块（2分钟）

#### 6.1 添加OP_SUB到指令名称映射
**文件：`src/debug.c` 第126-130行**
```c
printf("  %-5d %-12s %-8d %-8d %-8d", 
       i, 
       instr->op == OP_LOADK ? "LOADK" :
       instr->op == OP_ADD ? "ADD" :
       instr->op == OP_SUB ? "SUB" :    // ✅ 新增：SUB指令名称
       instr->op == OP_SETGLOBAL ? "SETGLOBAL" :
       instr->op == OP_GETGLOBAL ? "GETGLOBAL" :
       instr->op == OP_RETURN ? "RETURN" : "UNKNOWN",
       instr->a, instr->b, instr->c);
```

#### 6.2 添加OP_SUB执行跟踪
**文件：`src/debug.c` 第155-165行**
```c
case OP_ADD:
    printf("ADD R[%d] = R[%d] (%.2f) + R[%d] (%.2f)", 
           instr->a, instr->b, vm->registers[instr->b], 
           instr->c, vm->registers[instr->c]);
    vm->registers[instr->a] = vm->registers[instr->b] + vm->registers[instr->c];
    break;
    
case OP_SUB:  // ✅ 新增：SUB执行跟踪
    printf("SUB R[%d] = R[%d] (%.2f) - R[%d] (%.2f)", 
           instr->a, instr->b, vm->registers[instr->b], 
           instr->c, vm->registers[instr->c]);
    vm->registers[instr->a] = vm->registers[instr->b] - vm->registers[instr->c];
    break;
```

---

## 🧪 测试验证指南

### 测试1：基础减法
```bash
# 编译项目
make clean && make

# 测试简单减法
echo "5 - 3" | ./build/minic        # 期望输出：2.00
echo "10 - 20" | ./build/minic      # 期望输出：-10.00
echo "100 - 50 - 25" | ./build/minic # 期望输出：25.00
```

### 测试2：混合运算
```bash
# 测试加减混合
echo "10 + 5 - 3" | ./build/minic   # 期望输出：12.00
echo "100 - 50 + 25" | ./build/minic # 期望输出：75.00
```

### 测试3：观察内部过程
```bash
# 观察token化过程
./build/minic -vt  # 输入：10 - 5
# 期望输出：[NUMBER(10), MINUS, NUMBER(5)]

# 观察AST结构
./build/minic -va  # 输入：10 - 5
# 期望输出：(- 10 5)

# 观察完整编译流程
./build/minic -v   # 输入：10 - 5
# 期望输出：
# 源代码：10 - 5
# Token：[NUMBER(10), MINUS, NUMBER(5)]
# AST：(- 10 5)
# 字节码：PUSH 10, PUSH 5, SUB
# 结果：5.00
```

---

## 🎯 学习要点总结

### 🔍 理解编译器工作流程
1. **词法分析**：字符 → token（如'-' → TOKEN_MINUS）
2. **语法分析**：token → AST（如[10,-,5] → (- 10 5)）
3. **代码生成**：AST → 字节码（如(- 10 5) → PUSH 10, PUSH 5, SUB）
4. **虚拟机执行**：字节码 → 结果（如SUB → 10-5=5）

### 💡 关键概念
- **Token**：编译器识别的最小语法单元
- **AST**：抽象语法树，表达式的结构化表示
- **字节码**：虚拟机的中间指令格式
- **寄存器**：虚拟机中的临时存储位置

### 🚀 扩展思路
完成减法后，你可以继续添加：
- 乘法运算符（*）
- 除法运算符（/）
- 取模运算符（%）
- 括号优先级

---

## 🎓 完成检查清单

### ✅ 必须完成
- [ ] 所有7个文件修改完成（包括debug.c）
- [ ] 项目重新编译成功（make clean && make）
- [ ] 基础减法测试通过
- [ ] 混合运算测试通过
- [ ] 能够使用-vt观察token化过程
- [ ] 能够使用-va观察AST结构
- [ ] 能够使用-vb观察SUB指令
- [ ] 能够使用-ve观察SUB执行跟踪

### 🎯 进阶挑战
- [ ] 添加乘法支持
- [ ] 添加除法支持
- [ ] 处理负数输入（如"-5 + 3"）
- [ ] 添加括号支持

---

## 💬 常见问题解答

**Q: 修改后编译失败怎么办？**
A: 检查每个修改点的语法，确保分号和括号匹配。

**Q: 测试时输出不正确？**
A: 使用-v选项逐步检查：token → AST → 字节码 → 结果。

**Q: 如何调试？**
A: 在每个关键函数添加printf语句，观察数据流动。

---

**🎉 恭喜！完成减法实现后，你已经掌握了编译器扩展的基本方法！接下来可以尝试添加乘法、除法等更多运算符。**