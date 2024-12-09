# Compiler
CC = g++

# Retrieve all source files, including those in subdirectories
SRC = $(wildcard *.cpp *.c *.hpp *.h) $(wildcard */*.cpp */*.c */*.hpp */*.h)

# Extract directories from source files
DIRS = $(dir $(SRC))

# Add -I before each directory
INC = $(patsubst %, -I %, $(DIRS))

# Détection du système d'exploitation
UNAME := $(shell uname)
OS_RELEASE := $(shell grep -o Microsoft /proc/version 2>/dev/null)

# Bibliothèques à utiliser
ifeq ($(OS),Windows_NT)  # Cas pour Windows natif
    LIBS = -lcomdlg32 -lole32 -lsfml-graphics -lsfml-window -lsfml-system -ltbb
else ifneq ($(OS_RELEASE),)  # Cas pour WSL
    LIBS = -lsfml-graphics -lsfml-window -lsfml-system -ltbb -W 2>/dev/null
else ifeq ($(UNAME), Linux)  # Cas pour Linux natif
    LIBS = -lsfml-graphics -lsfml-window -lsfml-system -ltbb -W 2>/dev/null
endif

# Name of the executable
TARGET = GoL

# Default rule: compile the executable
all:
	$(CC) $(SRC) $(LIBS) $(INC) -o $(TARGET)

# Clean: delete generated files
clean:
	rm -f $(TARGET)