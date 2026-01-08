.SUFFIXES:

CC = gcc
CXX = g++
CFLAGS = -Wall -g
CXXFLAGS = -Wall -g

BUILD_DIR = build

.DEFAULT_GOAL := all

help:
	@echo "Usage: make f=file.c       (for C files)"
	@echo "       make f=file.cpp     (for C++ files)"
	@echo ""
	@echo "Example:"
	@echo "  make f=Lecture1/memory_bug.c"
	@echo "  make f=main.cpp"

# 编译并运行
all:
	@if [ -z "$(f)" ]; then \
		echo "Error: Please specify a file with f=<filename>"; \
		echo "Example: make f=Lecture1/test.c"; \
		exit 1; \
	fi
	@mkdir -p $(BUILD_DIR)
	@EXT=$${f##*.}; \
	if [ "$$EXT" = "c" ]; then \
		BASENAME=$$(basename "$(f)" .c); \
		echo "Compiling $(f) to $(BUILD_DIR)/$$BASENAME..."; \
		$(CC) $(CFLAGS) "$(f)" -o "$(BUILD_DIR)/$$BASENAME" && \
		echo "Running $(BUILD_DIR)/$$BASENAME..." && \
		"$(BUILD_DIR)/$$BASENAME"; \
	elif [ "$$EXT" = "cpp" ]; then \
		BASENAME=$$(basename "$(f)" .cpp); \
		echo "Compiling $(f) to $(BUILD_DIR)/$$BASENAME..."; \
		$(CXX) $(CXXFLAGS) "$(f)" -o "$(BUILD_DIR)/$$BASENAME" && \
		echo "Running $(BUILD_DIR)/$$BASENAME..." && \
		"$(BUILD_DIR)/$$BASENAME"; \
	else \
		echo "Error: Unsupported file extension: $$EXT"; \
		echo "Only .c and .cpp files are supported"; \
		exit 1; \
	fi

.PHONY: help all