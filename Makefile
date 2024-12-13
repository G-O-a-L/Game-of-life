# Compiler
CC = g++

# Retrieve all source files, including those in subdirectories
SRC = $(wildcard *.cpp *.c) $(wildcard */*.cpp */*.c)

# Extract directories from source files
DIRS = $(dir $(SRC))

# Add -I before each directory
INC = $(patsubst %, -I %, $(DIRS))

# Détection du système d'exploitation
UNAME := $(shell uname)

# Bibliothèques à utiliser
ifeq ($(OS),Windows_NT)  # Cas pour Windows natif
    LIBS = -lcomdlg32 -lole32 -lsfml-graphics -lsfml-window -lsfml-system -ltbb
else ifeq ($(UNAME), Linux)  # Cas pour Linux natif
    LIBS = -lsfml-graphics -lsfml-window -lsfml-system -ltbb
endif

# Name of the executable
TARGET = GoL

# Default rule: compile the executable
all:
	$(CC) $(SRC) $(LIBS) $(INC) -o $(TARGET)

# Clean: delete generated files
clean:
	rm -f $(TARGET)