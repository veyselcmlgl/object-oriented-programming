# Makefile

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -Wall -Wextra -Werror

# Source files
SRC = main.cpp catalog.cpp

# Header files
HEADERS = catalog.h

# Output executable
TARGET = catalog_app

# Build the executable
all: $(TARGET)

# Link the object files to create the final executable
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

# Clean up build files
clean:
	rm -f $(TARGET) *.o

# Phony targets
.PHONY: all clean
