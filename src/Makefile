# Compiler
CC = gcc

# Compiler Flags
CFLAGS = -Wall -Wextra -pedantic -std=c99

# Target executable name
TARGET = csma

# Source files
SOURCES = csma.c

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm -f $(TARGET)


#COMPILERFLAGS = -g -Wall -Wextra -Wno-sign-compare 



