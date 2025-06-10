TARGET = lumi
SRC_EXT = lumi

CC = gcc
CFLAGS = -g -Wall -Isrc -I$(BUILD_DIR)
LIBS = -lfl -lm

SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin

C_SOURCES = $(wildcard $(SRC_DIR)/*.c)
YACC_SOURCE = $(wildcard $(SRC_DIR)/*.y)
LEX_SOURCE = $(wildcard $(SRC_DIR)/*.l)

YACC_C = $(BUILD_DIR)/$(notdir $(YACC_SOURCE:.y=.tab.c))
YACC_H = $(BUILD_dir)/$(notdir $(YACC_SOURCE:.y=.tab.h))
LEX_C = $(BUILD_DIR)/$(notdir $(LEX_SOURCE:.l=.lex.c))

OBJECTS = $(addprefix $(BUILD_DIR)/, $(notdir $(C_SOURCES:.c=.o)))
OBJECTS += $(addprefix $(BUILD_DIR)/, $(notdir $(YACC_SOURCE:.y=.tab.o)))
OBJECTS += $(addprefix $(BUILD_DIR)/, $(notdir $(LEX_SOURCE:.l=.lex.o)))


all: $(BIN_DIR)/$(TARGET)

$(BIN_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS) $(LIBS)
	@echo "Compilação concluída! Executável criado em: $(BIN_DIR)/$(TARGET)"


$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.tab.o: $(BUILD_DIR)/%.tab.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.tab.c $(BUILD_DIR)/%.tab.h: $(YACC_SOURCE)
	@mkdir -p $(BUILD_DIR)
	bison -d -o $(BUILD_DIR)/$(notdir $(YACC_SOURCE:.y=.tab.c)) $(YACC_SOURCE)

$(BUILD_DIR)/%.lex.o: $(BUILD_DIR)/%.lex.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.lex.c: $(LEX_SOURCE) $(BUILD_DIR)/%.tab.h
	@mkdir -p $(BUILD_DIR)
	flex -o $(BUILD_DIR)/$(notdir $(LEX_SOURCE:.l=.lex.c)) $(LEX_SOURCE)


clean:
	@rm -rf $(BUILD_DIR) $(BIN_DIR)
	@echo "Diretórios de compilação limpos."

.PHONY: all clean

$(BUILD_DIR)/interpreter.o: $(BUILD_DIR)/lumi.tab.h
$(BUILD_DIR)/lumi.lex.o: $(BUILD_DIR)/lumi.tab.h
$(BUILD_DIR)/lumi.tab.o: $(BUILD_DIR)/lumi.tab.h
$(BUILD_DIR)/main.o: $(BUILD_DIR)/lumi.tab.h