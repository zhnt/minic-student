CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
SRCDIR = .
SOURCES = ast.c bytecode.c compiler.c debug.c lexer.c parser.c vm.c
HEADERS = ast.h bytecode.h compiler.h debug.h lexer.h parser.h vm.h
OBJECTS = $(SOURCES:.c=.o)
TARGET = minic

.PHONY: all clean test debug help

all: $(TARGET)

$(TARGET): minic.c $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) minic.c $(OBJECTS) -lm

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# 调试版本（带调试信息）
debug: CFLAGS += -DDEBUG -O0
debug: $(TARGET)

# 测试目标
test: $(TARGET)
	@echo "=== 测试基础功能 ==="
	@echo "5+3*2 =" `echo "5+3*2" | ./$(TARGET) | tail -1`
	@echo "-5+3 =" `echo "-5+3" | ./$(TARGET) | tail -1`
	@echo "1+2;3*4;5-1 =" `echo "1+2;3*4;5-1" | ./$(TARGET) | tail -1`
	@echo
	@echo "=== 测试变量功能（实现后） ==="
	@echo "x=5 =" `echo "x=5" | ./$(TARGET) | tail -1`
	@echo "x+3 =" `echo "x=5;x+3" | ./$(TARGET) | tail -1`

# 清理
clean:
	@echo "清理编译文件..."
	rm -f $(OBJECTS) $(TARGET)

# 帮助信息
help:
	@echo "编译器变量系统实现作业"
	@echo "======================="
	@echo "可用目标："
	@echo "  make       - 编译程序"
	@echo "  make test  - 运行测试"
	@echo "  make debug - 编译调试版本"
	@echo "  make clean - 清理文件"
	@echo "  make help  - 显示此帮助"
	@echo ""
	@echo "测试命令："
	@echo "  ./minic                  # 交互模式"
	@echo "  echo '5+3' | ./minic     # 批处理模式"
	@echo "  ./minic --help           # 查看所有选项"

# 学生专用目标
student-test: $(TARGET)
	@echo "🎯 学生作业测试开始..."
	@echo "基础计算测试："
	@echo "3+4*5 =" `echo "3+4*5" | ./$(TARGET) | tail -1`
	@echo "-3+5 =" `echo "-3+5" | ./$(TARGET) | tail -1`
	@echo "(1+2)*3 =" `echo "(1+2)*3" | ./$(TARGET) | tail -1`
	@echo ""
	@echo "变量功能测试（实现后）："
	@echo "x=10 =" `echo "x=10" | ./$(TARGET) | tail -1`
	@echo "x*2 =" `echo "x=10;x*2" | ./$(TARGET) | tail -1`
	@echo ""
	@echo "✅ 如上述测试通过，变量系统实现成功！"