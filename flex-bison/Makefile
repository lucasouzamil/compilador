CC = gcc
CFLAGS = -g -Wall
TARGET = leds_parser
LIBS = -lfl -lm

# Adicione os novos arquivos .c
C_SOURCES = leds.tab.c leds.lex.c interpreter.c simulator.c
# Adicione os novos arquivos .h como dependências
H_SOURCES = leds.tab.h ast.h interpreter.h simulator.h

# Gera os .o a partir dos .c
OBJECTS = $(C_SOURCES:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS) $(LIBS)

# Regra genérica para compilar .c para .o
%.o: %.c $(H_SOURCES)
	$(CC) $(CFLAGS) -c $< -o $@

leds.tab.c leds.tab.h: leds.y ast.h
	bison -d leds.y

leds.lex.c: leds.l leds.tab.h
	flex -o leds.lex.c leds.l

clean:
	rm -f $(TARGET) $(OBJECTS) leds.tab.c leds.lex.c leds.tab.h lex.yy.c