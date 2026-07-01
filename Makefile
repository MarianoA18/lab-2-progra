CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g -Iinclude
SRC_DIR = src
BUILD_DIR = build
TARGET = main

SRCS = main.c $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst %.c,$(BUILD_DIR)/%.o,$(notdir $(SRCS)))

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR) $(TARGET)
