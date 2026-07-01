# Makefile for SparseVector and SparseMatrix

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall

# Source files
SRCS = SparseVector.cpp SparseMatrix.cpp main.cpp
# Add all source files here

# Object files
OBJS = $(SRCS:.cpp=.o)

# Executable name
TARGET = sparse_app

# Default rule
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

# Rule to build object files
%.o: %.cpp SparseVector.h SparseMatrix.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule
clean:
	rm -f $(OBJS) $(TARGET)

# Build and run rule
run: $(TARGET)
	./$(TARGET)