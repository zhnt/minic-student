# 🎯 阶段3：变量系统作业 Makefile

# 基础配置
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
LDFLAGS = -lm

# 学生作业支持
.PHONY: all help clean init test validate

# 默认帮助
all: help

# 学生作业初始化
init:
	@echo "🚀 初始化学生作业环境..."
	@cp -r src30 src 2>/dev/null || echo "⚠️ 目录已存在"
	@echo ""
	@echo "📋 下一步操作："
	@echo "  cd src"
	@echo "  make help"

# 功能对比测试
test:
	@echo "📊 阶段功能对比测试"
	@echo "===================="
	@echo ""
	@echo "📋 基础功能测试："
	@cd src30 && make clean && make > /dev/null 2>&1
	@echo "src30 5+3*2 = " `cd src30 && echo "5+3*2" | ./minic | tail -1`
	@echo "src30 -5+3 = " `cd src30 && echo "-5+3" | ./minic | tail -1`
	@echo ""
	@echo "🎯 完整功能测试："
	@cd src34 && make clean && make > /dev/null 2>&1
	@echo "src34 变量赋值：" `cd src34 && echo "x=5" | ./minic | tail -1`
	@echo "src34 变量使用：" `cd src34 && echo "x=5;x+3" | ./minic | tail -1`

# 验证学生作业
validate: init
	@echo "🔍 验证学生作业实现..."
	@echo ""
	@echo "🧪 基础功能验证："
	@cd src && make clean && make > /dev/null 2>&1
	@cd src && echo "5+3*2" | ./minic | grep -q "11.00" && echo "✅ 基础表达式正常" || echo "❌ 基础表达式异常"
	@cd src && echo "-5+3" | ./minic | grep -q "-2.00" && echo "✅ 一元运算正常" || echo "❌ 一元运算异常"
	@echo ""
	@echo "🎯 变量功能验证："
	@cd src && (echo "x=5" | ./minic | tail -1 | grep -q "5.00" && echo "✅ 变量赋值正常" || echo "❌ 变量赋值异常")
	@cd src && (echo "x=5;x+3" | ./minic | tail -1 | grep -q "8.00" && echo "✅ 变量使用正常" || echo "❌ 变量使用异常")

# 全面清理
clean:
	@echo "🧹 清理所有构建文件..."
	@cd src30 && make clean 2>/dev/null || true
	@cd src34 && make clean 2>/dev/null || true
	@cd src && make clean 2>/dev/null || true
	@echo "✅ 清理完成"

# 帮助信息
help:
	@echo "🎯 阶段3：变量系统作业指南"
	@echo "================================"
	@echo ""
	@echo "🚀 快速开始："
	@echo "  make init         - 初始化学生作业环境"
	@echo "  make test         - 功能对比测试"
	@echo "  make validate     - 验证学生作业"
	@echo "  make clean        - 清理所有构建文件"
	@echo ""
	@echo "📂 目录说明："
	@echo "  src30/      - 学生起点（无变量功能）"
	@echo "  src34/      - 完整实现（参考答案）"
	@echo "  src/ - 学生作业目录"
	@echo ""
	@echo "📚 学习资源："
	@echo "  README.md         - 作业指南"
	@echo "  VARIABLE_GUIDE.md - 详细实现步骤"
	@echo "  SOLUTION_SIMPLE.md - 超简版指南"
	@echo ""
	@echo "🎯 作业流程："
	@echo "  1. make init     # 初始化作业环境"
	@echo "  2. cd src"
	@echo "  3. 开始实现变量系统"
	@echo "  4. make validate # 验证实现结果"
