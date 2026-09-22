##
# Cprojects
#
# @file
# @version 0.1

CC := gcc
SOURCES := main.c stateMachine.c fileHelper.c cJSON/cJSON.c
CFLAGS := -std=c17 -Wall -Wextra -Wpedantic

ifeq ($(OS),Windows_NT)
TARGET := main.exe
RAYLIB_FLAGS := -IC:/raylib/raylib/src -LC:/raylib/raylib/src \
                -lraylib -lopengl32 -lgdi32 -lwinmm
else
TARGET := main
RAYLIB_FLAGS := $(shell pkg-config --cflags --libs raylib)
endif

.PHONY: run

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) $(RAYLIB_FLAGS) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

# end
