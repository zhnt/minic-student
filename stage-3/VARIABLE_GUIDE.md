# 🎯 阶段3：变量系统实现指南

## 🚀 作业概述
从src30开始，实现完整的变量系统，达到src34的功能水平。

## 📊 当前状态对比
- **src30**：支持表达式计算、一元操作、多语句、错误处理
- **src34**：在src30基础上增加完整变量系统

## 📝 实现步骤（详细版）

### 步骤1：数据结构准备 (5分钟)

**文件：`compiler.h`**

在`Compiler`结构体中添加变量存储：
```c
#define MAX_VARIABLES 256

typedef struct {
    char names[MAX_VARIABLES][32];    // 变量名
    double values[MAX_VARIABLES];     // 变量值
    int count;                        // 变量数量
} VariableTable;

// 添加到Compiler结构体中
typedef struct {
    Bytecode* bc;
    int next_register;
    VariableTable vars;  // 新增：变量表
} Compiler;
```

### 步骤2：编译器初始化 (2分钟)

**文件：`compiler.c` -> compiler_init函数**

```c
void compiler_init(Compiler* comp, Bytecode* bc) {
    comp->bc = bc;
    comp->next_register = 0;
    comp->vars.count = 0;  // 初始化变量计数器
}
```

### 步骤3：变量查找功能 (10分钟)

**文件：`compiler.c` -> compile_expression函数**

替换`AST_IDENTIFIER`分支：
```c
case AST_IDENTIFIER: {
    // 在变量表中查找
    int var_idx = -1;
    for (int i = 0; i < comp->vars.count; i++) {
        if (strcmp(comp->vars.names[i], expr->data.identifier) == 0) {
            var_idx = i;
            break;
        }
    }
    
    if (var_idx == -1) {
        printf("Error: Variable '%s' not defined\n", expr->data.identifier);
        return -1;
    }
    
    bytecode_add_instruction(comp->bc, OP_GETVAR, reg, var_idx, 0);
    return reg;
}
```

### 步骤4：变量赋值功能 (15分钟)

**文件：`compiler.c` -> compile_ast函数**

启用`AST_ASSIGNMENT`分支：
```c
case AST_ASSIGNMENT: {
    int value_reg = compile_expression(comp, ast->data.assignment.value);
    if (value_reg == -1) return;
    
    // 查找或创建变量
    int var_idx = -1;
    for (int i = 0; i < comp->vars.count; i++) {
        if (strcmp(comp->vars.names[i], ast->data.assignment.name) == 0) {
            var_idx = i;
            break;
        }
    }
    
    if (var_idx == -1) {
        if (comp->vars.count >= MAX_VARIABLES) {
            printf("Error: Too many variables\n");
            return;
        }
        var_idx = comp->vars.count;
        strncpy(comp->vars.names[var_idx], ast->data.assignment.name, 31);
        comp->vars.count++;
    }
    
    bytecode_add_instruction(comp->bc, OP_SETVAR, var_idx, value_reg, 0);
    bytecode_add_instruction(comp->bc, OP_RETURN, value_reg, 0, 0);
    break;
}
```

### 步骤5：语法分析器支持 (5分钟)

**文件：`parser.c` -> parse_expression函数**

启用赋值语法：
```c
static ASTNode* parse_expression(Parser* parser) {
    // 检查是否是赋值语句
    if (parser->current.type == TOKEN_IDENTIFIER) {
        Lexer temp_lexer = *parser->lexer;
        Token temp_token = lexer_next_token(&temp_lexer);
        
        if (temp_token.type == TOKEN_ASSIGN) {
            char name[32];
            strncpy(name, parser->current.identifier, 31);
            parser_consume(parser, TOKEN_IDENTIFIER);
            parser_consume(parser, TOKEN_ASSIGN);
            ASTNode* value = parse_expression(parser);
            return ast_assignment(name, value);
        }
    }
    
    return parse_term(parser);
}
```

### 步骤6：VM字节码支持 (已存在)

src30已包含所需的字节码操作：
- `OP_GETVAR`：获取变量值
- `OP_SETVAR`：设置变量值

### 步骤7：序列处理更新 (5分钟)

**文件：`compiler.c` -> compile_ast函数**

更新`AST_SEQUENCE`分支以支持赋值：
```c
case AST_SEQUENCE: {
    if (ast->data.sequence.count > 0) {
        // 处理所有语句
        for (int i = 0; i < ast->data.sequence.count - 1; i++) {
            ASTNode* stmt = ast->data.sequence.statements[i];
            if (stmt->type == AST_ASSIGNMENT) {
                int value_reg = compile_expression(comp, stmt->data.assignment.value);
                if (value_reg == -1) return;
                
                // 处理赋值逻辑（同上）
                int var_idx = -1;
                for (int j = 0; j < comp->vars.count; j++) {
                    if (strcmp(comp->vars.names[j], stmt->data.assignment.name) == 0) {
                        var_idx = j;
                        break;
                    }
                }
                
                if (var_idx == -1) {
                    var_idx = comp->vars.count;
                    strncpy(comp->vars.names[var_idx], stmt->data.assignment.name, 31);
                    comp->vars.count++;
                }
                
                bytecode_add_instruction(comp->bc, OP_SETVAR, var_idx, value_reg, 0);
            } else {
                compile_expression(comp, stmt);
            }
        }
        
        // 处理最后一个语句
        ASTNode* last = ast->data.sequence.statements[ast->data.sequence.count - 1];
        if (last->type == AST_ASSIGNMENT) {
            int value_reg = compile_expression(comp, last->data.assignment.value);
            if (value_reg == -1) return;
            
            int var_idx = -1;
            for (int j = 0; j < comp->vars.count; j++) {
                if (strcmp(comp->vars.names[j], last->data.assignment.name) == 0) {
                    var_idx = j;
                    break;
                }
            }
            
            if (var_idx == -1) {
                var_idx = comp->vars.count;
                strncpy(comp->vars.names[var_idx], last->data.assignment.name, 31);
                comp->vars.count++;
            }
            
            bytecode_add_instruction(comp->bc, OP_SETVAR, var_idx, value_reg, 0);
            bytecode_add_instruction(comp->bc, OP_RETURN, value_reg, 0, 0);
        } else {
            int result_reg = compile_expression(comp, last);
            if (result_reg == -1) return;
            bytecode_add_instruction(comp->bc, OP_RETURN, result_reg, 0, 0);
        }
    }
    break;
}
```

## 🧪 测试验证

### 编译测试
```bash
cd stage-3/src30
make clean && make
```

### 功能测试
```bash
# 基础测试
./minic
minic> 5 + 3 * 2
11.00

# 变量测试
minic> x = 5
minic> y = 3 + 2
minic> x + y
8.00

# 变量更新
minic> x = x + 1
minic> x
6.00

# 错误测试
minic> z
Error: Variable 'z' not defined
```

## 📋 检查清单

- [ ] 变量赋值 `x = 5` 正常工作
- [ ] 变量使用 `x + 1` 正常工作
- [ ] 多变量支持 `abc = 123` 正常工作
- [ ] 变量更新 `x = x + 1` 正常工作
- [ ] 错误提示友好
- [ ] 代码无内存泄漏
- [ ] 支持任意长度变量名（≤31字符）

## 🎯 进阶挑战（可选）

1. **作用域支持**：实现局部变量
2. **变量删除**：实现 `unset x` 功能
3. **内置函数**：添加 `sin(x)` 等数学函数
4. **变量类型**：支持字符串变量

## 📝 作业提交

完成后提交：
1. 修改后的源代码
2. 测试用例运行截图
3. 简要说明实现思路

**祝实现顺利！** 🚀