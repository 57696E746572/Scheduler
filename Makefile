CC := gcc
CFLAGS := -Wall -Wextra -Iinclude -O2


SRC_DIR := src
BUILD_DIR := build
INCLUDE_DIR := include


SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))
TARGET := scheduler


.PHONY: all clean dirs

all: dirs $(TARGET)

dirs:
	@mkdir -p $(BUILD_DIR)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ -lncurses -ltinfo


$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -rf $(BUILD_DIR) $(TARGET)
