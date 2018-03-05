TARGET = geracpf
CFLAGS = -g -Wall
LIBS = -lm
EXEC = bin/geracpf
CC = gcc

SRC = src/main.c

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(SRC) $(CFLAGS) $(LIBS) -o $(EXEC)

clean: 
	-rm -f *.o
	-rm -f $(TARGET)
