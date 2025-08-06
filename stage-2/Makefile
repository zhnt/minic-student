# Minic Compiler - Stage 2
# 扁平化源码结构，优化编译配置

# 编译器配置
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g -O2
LDFLAGS = -lm

# 目录配置
SRC_DIR = src
BUILD_DIR = build

# 源文件
SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
HEADERS = $(wildcard $(SRC_DIR)/*.h)

# 目标文件
TARGET = minic
NEW_TARGET = minic-new

# 默认目标
.PHONY: all clean help new

all: $(TARGET)

# 新的分层版本
new: $(NEW_TARGET)

$(NEW_TARGET):
	$(CC) $(CFLAGS) -o $(NEW_TARGET) $(wildcard newsrc/*.c) $(LDFLAGS)
	@echo "✅ 编译完成: $(NEW_TARGET)"  

# 创建构建目录
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

# 编译可执行文件到当前目录
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)
	@echo "✅ 编译完成: $(TARGET)"

# 编译对象文件到build目录
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "🔧 编译: $< → $@"

# 清理构建文件
 clean:
	@rm -rf $(BUILD_DIR) $(TARGET)
	rm minic
	rm minic-clean
	@echo "🧹 清理完成"

# 完整清理（包括所有临时文件）
clean-all: clean
	@find . -name "*.dSYM" -type d -exec rm -rf {} + 2>/dev/null || true
	@echo "🧹 深度清理完成"

# 运行测试
 test: $(TARGET)
	@echo "🧪 运行测试..."
	@cd tests && ./test.sh

# 帮助信息
 help:
	@echo "Minic编译器 - Stage 2"
	@echo ""
	@echo "使用方法:"
	@echo "  make         - 编译项目"
	@echo "  make clean   - 清理构建文件"
	@echo "  make test    - 运行测试"
	@echo "  make help    - 显示此帮助"
	@echo ""
	@echo "文件结构:"
	@echo "  src/         - 所有.c和.h文件"
	@echo "  build/       - 临时.o文件"
	@echo "  minic        - 生成的可执行文件"
	@echo ""
	@echo "快速开始:"
	@echo "  make && ./minic -v"
