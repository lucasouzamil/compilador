CC = gcc
CFLAGS = -g -Wall
TARGET = lights_parser
LIBS = -lfl -lm

# Adicione os novos arquivos .c
C_SOURCES = lights.tab.c lights.lex.c interpreter.c simulator.c
# Adicione os novos arquivos .h como dependências
H_SOURCES = lights.tab.h ast.h interpreter.h simulator.h

# Gera os .o a partir dos .c
OBJECTS = $(C_SOURCES:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS) $(LIBS)

# Regra genérica para compilar .c para .o
%.o: %.c $(H_SOURCES)
	$(CC) $(CFLAGS) -c $< -o $@

lights.tab.c lights.tab.h: lights.y ast.h
	bison -d lights.y

lights.lex.c: lights.l lights.tab.h
	flex -o lights.lex.c lights.l

clean:
	rm -f $(TARGET) $(OBJECTS) lights.tab.c lights.lex.c lights.tab.h