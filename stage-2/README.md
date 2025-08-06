# 🎯 Minic阶段2：运算符优先级与四则运算

## 🎉 实验目标：通过对比学习掌握优先级

本阶段采用**对比式学习**方法，让学生通过老版本和新版本的对比，深入理解运算符优先级的重要性。

## 📁 目录结构

```
stage-2/
├── src/           # 老版本：扁平解析器（只有+-）
├── newsrc/        # 新版本：分层解析器（预置架构，缺少*/()）
├── minic          # 老版本可执行文件
├── minic-new      # 新版本可执行文件（学生构建）
└── Grammar-Guide.md # 分层语法详解
```

## 🔍 实验流程：5步掌握优先级

### 第一步：在老版本中添加*法（体验问题）
在老版本（src/）中直接添加乘法，**不**修改优先级：

```bash
cd stage-2
make                # 构建老版本
./minic             # 测试：2 + 3 * 4
# 结果：20 ❌  （发现问题！）
```

**预期结果**：学生会发现在扁平解析器中添加乘法会导致`2 + 3 * 4 = 20`的错误结果。

### 第二步：发现问题，对比分析
学生会发现：
- 老版本：所有运算符同等优先级，从左到右
- 需要：数学正确的优先级（先乘除后加减）
- 需要：括号支持改变运算顺序

### 第三步：学习分层语法架构
阅读 `Grammar-Guide.md`，理解：
- **expr层**：处理加减法（最低优先级）
- **term层**：处理乘除法（中等优先级）
- **factor层**：处理基本元素和括号（最高优先级）

### 第四步：在新架构中添加功能
使用newsrc中的预置分层架构，学生需要：

#### 任务1：在term层添加乘除法
在 `newsrc/parser.c` 的 `parse_term()` 函数中添加：
```c
// TODO: 学生需要在这里添加乘法和除法支持
while (parser->current.type == TOKEN_STAR || parser->current.type == TOKEN_SLASH) {
    // 添加处理逻辑
}
```

#### 任务2：在factor层添加括号
在 `newsrc/parser.c` 的 `parse_factor()` 函数中添加：
```c
// TODO: 学生需要在这里添加括号支持
} else if (parser->current.type == TOKEN_LEFT_PAREN) {
    // 添加括号处理
}
```

#### 构建新版本：
```bash
make new            # 构建新版本
./minic-new         # 测试：2 + 3 * 4 = 14 ✅
```

### 第五步：对比分析，深入理解
对比两种实现：

| 特性 | 老版本（src/） | 新版本（newsrc/） |
|------|---------------|------------------|
| 架构 | 扁平解析器 | 分层解析器 |
| 优先级 | 无 | 数学正确 |
| 可扩展性 | 差 | 好 |
| 代码结构 | 简单 | 清晰 |

## 🎯 具体实施步骤

### 🔧 需要修改的文件

#### 老版本（src/）- 仅第一步使用
1. `lexer.h/c` - 添加 `TOKEN_STAR`, `TOKEN_SLASH`
2. `parser.c` - 直接添加乘除法（体验问题）
3. `bytecode.h` - 添加 `OP_MUL`, `OP_DIV`
4. `compiler.c` - 生成乘除法代码
5. `vm.c` - 实现乘除法运算
6. `debug.c` - 添加调试支持

#### 新版本（newsrc/）- 主要工作
1. `lexer.h/c` - 添加 `* / ( )` 标记
2. `parser.c` - 在TODO位置添加乘除法和括号支持
3. `bytecode.h` - 添加 `OP_MUL`, `OP_DIV`
4. `compiler.c` - 生成乘除法代码
5. `vm.c` - 实现乘除法运算
6. `debug.c` - 添加调试支持

## 🧪 测试验证

### 老版本测试（体验问题）
```bash
echo "2 + 3 * 4" | ./minic     # 应该得到20 ❌
echo "10 - 6 / 2" | ./minic    # 应该得到2 ❌
```

### 新版本测试（验证正确性）
```bash
# 构建新版本
make new

# 优先级测试
echo "2 + 3 * 4" | ./minic-new     # 应该得到14 ✅
echo "10 - 6 / 2" | ./minic-new    # 应该得到7 ✅

# 括号测试
echo "(2 + 3) * 4" | ./minic-new   # 应该得到20 ✅
echo "8 / (2 + 2)" | ./minic-new   # 应该得到2 ✅

# 混合测试
echo "1 + 2 * 3 - 4 / 2" | ./minic-new  # 应该得到5 ✅
```

## 🚀 快速开始

### 📋 实验检查清单

#### 步骤1：在老版本中体验问题
```bash
# 1. 构建老版本
make clean && make

# 2. 体验当前问题
echo "2 + 3 * 4" | ./minic
# 得到20，意识到需要优先级！
```

#### 步骤2：学习分层架构
```bash
# 阅读分层语法指南
cat Grammar-Guide.md
```

#### 步骤3：在新架构中实现功能
```bash
# 1. 编辑newsrc/parser.c，完成TODO部分
# 2. 添加lexer支持
# 3. 构建新版本
make new

# 4. 验证正确性
echo "2 + 3 * 4" | ./minic-new    # 应该得到14 ✅
echo "(2 + 3) * 4" | ./minic-new  # 应该得到20 ✅
```

#### 步骤4：对比两种实现
```bash
# 对比结果
./minic "2 + 3 * 4"         # 老版本：20 ❌
./minic-new "2 + 3 * 4"     # 新版本：14 ✅
```

#### 步骤5：深入理解
- 对比两种parser.c的实现
- 思考为什么分层架构更好
- 理解如何扩展到更多运算符

---

**🎓 完成实验后，你将真正理解：为什么需要分层解析器，以及如何优雅地处理运算符优先级！**

### 🎯 扩展任务：乘除法与括号支持

#### 📋 作业要求
在优先级基础上，添加完整的乘除法和括号支持：

#### 1. 实现乘法运算 `*`
- **示例**：`5 * 3` → `15.00`
- **优先级测试**：`2 + 3 * 4` → `14.00`

#### 2. 实现除法运算 `/`
- **示例**：`10 / 2` → `5.00`
- **优先级测试**：`10 - 6 / 2` → `7.00`

#### 3. 实现括号支持 `()`
- **示例**：`(2 + 3) * 4` → `20.00`
- **优先级测试**：`(10 - 6) / 2` → `2.00`
- **嵌套测试**：`((1 + 2) * 3) - 4` → `5.00`

#### 4. 完成调试支持
- 所有调试选项支持新运算符和括号

#### 📁 需要修改的文件（7个）
1. `lexer.h` - 添加 `TOKEN_STAR`, `TOKEN_SLASH`, `TOKEN_LEFT_PAREN`, `TOKEN_RIGHT_PAREN`
2. `lexer.c` - 识别 `* / ( )` 字符
3. `parser.c` - 实现分层解析器 + 乘除法表达式 + 括号支持
4. `bytecode.h` - 添加 `OP_MUL` 和 `OP_DIV` 指令
5. `compiler.c` - 生成乘法和除法代码
6. `vm.c` - 执行乘法和除法运算
7. `debug.c` - 添加MUL和DIV调试支持

#### 🎯 测试用例
完成作业后，确保以下测试全部通过：

#### 优先级测试
```bash
# 优先级验证
echo "2 + 3 * 4" | ./minic     # 14.00 (不是20)
echo "10 - 6 / 2" | ./minic    # 7.00  (不是2)
echo "8 / 2 + 3 * 2" | ./minic  # 10.00 (4+6)
echo "1 + 2 * 3 - 4 / 2" | ./minic  # 5.00
```

#### 乘除法测试
```bash
# 乘法测试
echo "5 * 3" | ./minic          # 15.00
echo "2 * 3 * 4" | ./minic      # 24.00

# 除法测试  
echo "10 / 2" | ./minic         # 5.00
echo "20 / 4 / 5" | ./minic     # 1.00
```

#### 括号测试
```bash
# 括号优先级验证
echo "(2 + 3) * 4" | ./minic     # 20.00 (括号优先)
echo "(10 - 6) / 2" | ./minic    # 2.00  (括号优先)
echo "8 / (2 + 2)" | ./minic     # 2.00  (括号优先)
echo "((1 + 2) * 3) - 4" | ./minic  # 5.00 (嵌套括号)
```

#### 混合运算
```bash
echo "10 + 5 * 2" | ./minic     # 20.00
echo "100 - 50 / 5" | ./minic   # 90.00
echo "(10 + 5) * 2" | ./minic  # 30.00 (括号改变优先级)
```

#### 调试测试
```bash
# 检查优先级实现
./minic -vt -va -vb -ve  # 输入：2 + 3 * 4
```

### 🏆 进阶挑战（选做）
1. **除零错误**：优雅处理除零错误
2. **取模运算**：添加 `%` 运算符
3. **一元运算**：支持 `-5` 这样的负数

### 🚀 开始作业

#### 第一步：理解当前问题
```bash
make clean && make
echo "2 + 3 * 4" | ./minic  # 现在得到20，错误！需要14
```

#### 第二步：重构运算符优先级（核心）
**关键：先重构parser架构，再添加新运算符**

1. **先重构parser** - 建立expr→term→factor三层架构
   - 这一步只处理加减法，验证架构正确性
   - 测试：`2 + 3 - 4` 应该正常工作

2. **再添加乘除法** - 在term层添加 `*` `/` 支持
   - 测试：`2 + 3 * 4` 应该得到14

3. **最后添加括号** - 在factor层添加 `()` 支持
   - 测试：`(2 + 3) * 4` 应该得到20

#### 第三步：渐进式验证
每完成一个小步骤，立即测试验证：

```bash
# 步骤1：验证优先级架构
echo "2 + 3 - 4" | ./minic  # 应该得到1

# 步骤2：验证乘除法
echo "2 + 3 * 4" | ./minic  # 应该得到14

# 步骤3：验证括号
echo "(2 + 3) * 4" | ./minic  # 应该得到20
```

#### 💡 实现提示
- **分层思考**：表达式 → 项 → 因子
- **优先级**：乘除法层高于加减法层
- **测试驱动**：每步修改后立即测试
- **调试工具**：使用-vt/-va观察AST结构

### 🎯 实际架构展示

newsrc/parser.c中已经预置了分层架构，学生只需要完成TODO部分：

#### 当前架构（已预置）
```c
// ✅ expr层：处理加减法（已完整）
static ASTNode* parse_expression(Parser* parser) {
    ASTNode* left = parse_term(parser);
    while (parser->current.type == TOKEN_PLUS || parser->current.type == TOKEN_MINUS) {
        TokenType op = parser->current.type;
        parser_consume(parser, op);
        ASTNode* right = parse_term(parser);
        char op_char = (op == TOKEN_PLUS) ? '+' : '-';
        left = ast_binary_op(op_char, left, right);
    }
    return left;
}

// 📝 term层：处理乘除法（学生需要添加*和/）
static ASTNode* parse_term(Parser* parser) {
    ASTNode* left = parse_factor(parser);
    
    // TODO: 学生需要在这里添加乘法和除法支持
    // 添加 while 循环处理 TOKEN_STAR 和 TOKEN_SLASH
    return left;
}

// ✅ factor层：处理基本元素和括号（已完整）
static ASTNode* parse_factor(Parser* parser) {
    if (parser->current.type == TOKEN_NUMBER) {
        return ast_number(...);
    } else if (parser->current.type == TOKEN_IDENTIFIER) {
        return ast_identifier(...);
    } else if (parser->current.type == TOKEN_LEFT_PAREN) {
        // 括号支持已完整实现
        parser_consume(parser, TOKEN_LEFT_PAREN);
        ASTNode* expr = parse_expression(parser);
        parser_consume(parser, TOKEN_RIGHT_PAREN);
        return expr;
    }
    return ...;
}
```

---

**🎉 完成后，你将拥有一个支持 + - * / 四则运算且具备正确优先级的完整编译器！**

**🚀 下一步预告**：阶段3将学习括号支持和更复杂的表达式处理。