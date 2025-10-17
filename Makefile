# --- Configurações principais ---
TARGET = pacman
SRC_DIR = src
INC_DIR = include
OBJ_DIR = build

# --- Arquivos fonte e objeto ---
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

# --- Compilador e flags ---
CC = gcc
CFLAGS = -I$(INC_DIR) -Wall -Wextra -std=c99
LIBS = -lraylib -lm -lpthread -ldl -lGL -lX11

# --- Regra principal ---
all: $(TARGET)

# --- Garante que a pasta build existe ---
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# --- Como gerar cada .o ---
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# --- Regra para gerar o executável ---
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LIBS)
	@echo "✅ Compilado com sucesso!"

# --- Limpar ---
clean:
	rm -rf $(OBJ_DIR) $(TARGET)
	@echo "🧹 Limpeza concluída."

.PHONY: all clean
