# Define o compilador C
CC = gcc

# Flags de compilação
CFLAGS = -Wall -g

# Flags específicas para o Raylib
# Certifique-se de que o Raylib está instalado e as flags estão corretas para o seu sistema
# Para Linux, use as seguintes flags:
RAYLIB_FLAGS = -lraylib -lm -lpthread -ldl -lrt -lX11
# Para Windows, você usaria:
# RAYLIB_FLAGS = -lraylib -lopengl32 -lgdi32 -lwinmm -lws2_32

# Diretórios do projeto
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build
BIN_DIR = bin

# Nomes dos arquivos de origem (todos os arquivos .c dentro de src/)
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Nomes dos arquivos objeto (serão criados na pasta build)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

# Nome do executável
TARGET = $(BIN_DIR)/wander

.PHONY: all clean

all: $(TARGET)

# Cria os diretórios de build e bin se não existirem
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Regra para compilar cada arquivo .c em .o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Regra para linkar todos os arquivos .o e criar o executável
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CC) $(OBJS) -o $(TARGET) $(RAYLIB_FLAGS)

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)