# Compiler
CC = g++

# Retrieve all source files, including those in subdirectories
SRC = $(wildcard *.cpp *.c *.hpp *.h) $(wildcard */*.cpp */*.c */*.hpp */*.h)

# Extract directories from source files
DIRS = $(dir $(SRC))

# Add -I before each directory
INC = $(patsubst %, -I %, $(DIRS))

# Library directories
LIBS = -lcomdlg32 -lole32

# Name of the executable
TARGET = GoL

# Default rule: compile the executable
all:
	$(CC) $(SRC) $(LIBS) $(INC) -o $(TARGET)

# Clean: delete generated files
clean:
	rm -f $(TARGET)