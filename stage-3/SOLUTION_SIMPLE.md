# 🔧 变量系统实现 - 超简版指南

## 🎯 目标
从src30到src34，仅需4个文件修改，实现完整变量系统。

## 📂 需要修改的文件
1. `compiler.h` - 添加变量存储
2. `compiler.c` - 实现变量功能
3. `parser.c` - 启用赋值语法

## 🚀 3步完成

### 第1步：添加变量存储 (compiler.h)
在`Compiler`结构体最后添加：
```c
#define MAX_VARIABLES 256
typedef struct {
    char names[MAX_VARIABLES][32];
    double values[MAX_VARIABLES];
    int count;
} VariableTable;

// 添加到Compiler结构体
VariableTable vars;
```

### 第2步：初始化变量 (compiler.c)
修改`compiler_init`函数：
```c
void compiler_init(Compiler* comp, Bytecode* bc) {
    comp->bc = bc;
    comp->next_register = 0;
    comp->vars.count = 0;  // 添加这行
}
```

### 第3步：查找变量 (compiler.c)
在`compile_expression`函数中，替换`case AST_IDENTIFIER:`：
```c
case AST_IDENTIFIER: {
    for (int i = 0; i < comp->vars.count; i++) {
        if (strcmp(comp->vars.names[i], expr->data.identifier) == 0) {
            bytecode_add_instruction(comp->bc, OP_GETVAR, reg, i, 0);
            return reg;
        }
    }
    printf("Error: Variable '%s' not defined\n", expr->data.identifier);
    return -1;
}
```

### 第4步：赋值功能 (compiler.c)
在`compile_ast`函数中，替换`case AST_ASSIGNMENT:`：
```c
case AST_ASSIGNMENT: {
    int value_reg = compile_expression(comp, ast->data.assignment.value);
    
    int var_idx = -1;
    for (int i = 0; i < comp->vars.count; i++) {
        if (strcmp(comp->vars.names[i], ast->data.assignment.name) == 0) {
            var_idx = i;
            break;
        }
    }
    
    if (var_idx == -1) {
        var_idx = comp->vars.count;
        strncpy(comp->vars.names[var_idx], ast->data.assignment.name, 31);
        comp->vars.count++;
    }
    
    bytecode_add_instruction(comp->bc, OP_SETVAR, var_idx, value_reg, 0);
    bytecode_add_instruction(comp->bc, OP_RETURN, value_reg, 0, 0);
    break;
}
```

### 第5步：语法支持 (parser.c)
在`parse_expression`函数中，替换整个函数：
```c
static ASTNode* parse_expression(Parser* parser) {
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

## ✅ 测试
```bash
make clean && make
echo "x = 5" | ./minic        # 应该成功
echo "x + 3" | ./minic        # 应该输出 8
echo "x = 10; x * 2" | ./minic  # 应该输出 20
```

**完成！现在你的编译器支持变量系统了。** 🎉