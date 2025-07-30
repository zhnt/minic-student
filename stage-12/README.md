# Minic阶段12：完整编译器

## 🎯 学习目标
- 整合前面所有功能
- 实现完整的编程语言
- 完成编译器项目

## 🚀 快速开始

### 获取阶段12代码
```bash
git clone https://github.com/zhnt/minic-s12.git
cd minic-s12
make
```

### 测试完整功能
```bash
# 运行示例程序
./build/minic examples/fibonacci.mc
echo "func fib(n) { if (n <= 1) return n; return fib(n-1) + fib(n-2); } fib(10)" | ./build/minic  # 55.00
```

## 📚 综合项目指南

### 第1步：功能清单（5分钟）
✅ **已实现功能：**
- 基础运算：+ - * /
- 括号支持：()
- 变量系统：赋值与读取
- 比较运算：> < == != >= <=
- 控制结构：if, while, for
- 函数定义：func, return
- 数组字符串：[1,2,3], "hello"
- 标准库：sqrt, pow, sin, cos等

### 第2步：综合示例（10分钟）
```bash
# 示例程序：计算斐波那契数列
echo "
func fib(n) {
    if (n <= 1) return n;
    return fib(n-1) + fib(n-2);
}

for (i = 0; i <= 10; i = i + 1) {
    print(fib(i));
}
" | ./build/minic
```

### 第3步：项目挑战（15分钟）
**挑战项目：实现计算器程序**

创建文件 `calculator.mc`：
```javascript
// 简单计算器
func calculate(a, op, b) {
    if (op == "+") return a + b;
    if (op == "-") return a - b;
    if (op == "*") return a * b;
    if (op == "/") return a / b;
    return 0;
}

// 测试用例
result1 = calculate(10, "+", 5);    // 15
result2 = calculate(20, "*", 3);    // 60
result3 = calculate(100, "/", 4);   // 25

print("Calculator Results:");
print("10 + 5 = " + result1);
print("20 * 3 = " + result2);
print("100 / 4 = " + result3);
```

## 🔍 完整功能测试

### 1. 数学运算
```bash
echo "(10 + 5) * 2 - 8 / 4" | ./build/minic  # 28.00
```

### 2. 变量和控制结构
```bash
echo "
total = 0;
for (i = 1; i <= 100; i = i + 1) {
    total = total + i;
}
total" | ./build/minic  # 5050.00
```

### 3. 函数和数组
```bash
echo "
func sum(arr, len) {
    result = 0;
    for (i = 0; i < len; i = i + 1) {
        result = result + arr[i];
    }
    return result;
}

numbers = [1, 2, 3, 4, 5];
sum(numbers, 5)" | ./build/minic  # 15.00
```

## 🎯 完成标准

### 基础要求（必做）
- [ ] 运行所有示例程序
- [ ] 理解完整编译器结构
- [ ] 创建一个综合程序

### 进阶挑战（选做）
- [ ] 实现猜数字游戏
- [ ] 实现简单绘图程序
- [ ] 添加自定义函数

### 项目展示
```bash
# 运行你的最终项目
./build/minic my_final_project.mc
```

## 📋 示例程序库

### 1. 猜数字游戏
```javascript
// 猜数字游戏
secret = 42;
guesses = 0;

print("Guess a number between 1 and 100:");

while (true) {
    guess = 50;  // 简化版本
    guesses = guesses + 1;
    
    if (guess == secret) {
        print("Correct! You took " + guesses + " guesses.");
        break;
    }
    
    if (guess < secret) {
        print("Too low!");
    } else {
        print("Too high!");
    }
}
```

### 2. 数据统计程序
```javascript
// 计算平均值和标准差
func mean(data, len) {
    sum = 0;
    for (i = 0; i < len; i = i + 1) {
        sum = sum + data[i];
    }
    return sum / len;
}

func stddev(data, len) {
    avg = mean(data, len);
    sum_sq = 0;
    for (i = 0; i < len; i = i + 1) {
        diff = data[i] - avg;
        sum_sq = sum_sq + diff * diff;
    }
    return sqrt(sum_sq / len);
}

// 测试数据
scores = [85, 90, 78, 92, 88, 95, 83, 89];
print("Mean: " + mean(scores, 8));
print("Std Dev: " + stddev(scores, 8));
```

## 🏆 学习成果

### 你现在已经掌握了：
1. **编译器核心**：词法分析、语法分析、代码生成
2. **语言特性**：变量、控制结构、函数、数组、字符串
3. **标准库**：数学函数、实用工具
4. **项目实践**：从简单计算器到完整编程语言

### 下一步学习建议
- 研究更复杂的编译器（如LLVM）
- 探索JIT编译技术
- 学习垃圾回收机制
- 尝试实现面向对象特性

## 📋 解锁最终认证

完成本阶段后，你将获得：
- 🎓 **编译器大师认证**
- 📜 **项目完成证书**
- 🚀 **继续深入学习的路线图**

## 📊 最终阶段信息
- **阶段**：12/12 ✅
- **功能**：完整编译器
- **时间**：自由发挥
- **状态**：终极挑战

---

**🎉 恭喜你！你已经完成了从加法计算器到完整编译器的12阶段学习之旅！**

**现在你可以自豪地说："我亲手实现了一个完整的编程语言！"**

---

*下一步：探索更高级的编译器技术，如优化、垃圾回收、类型系统等...*