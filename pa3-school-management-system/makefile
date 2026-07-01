# Compiler settings - Can change according to your system
CXX = g++
CXXFLAGS = -Wall -std=c++11

# Linker settings
LDFLAGS = 

# Add header files here
HEADERS = Student.h Course.h SchoolManagerSystem.h

# Add source files here
SOURCES = Student.cpp Course.cpp SchoolManagerSystem.cpp main.cpp

# Object files are based on the source file names
OBJECTS = $(SOURCES:.cpp=.o)

# The final executable
EXEC = SchoolSystem

# Default target
all: $(EXEC)

# Link the executable
$(EXEC): $(OBJECTS)
	$(CXX) $(LDFLAGS) -o $@ $^

# Rule for object files, depends on source files
# This makes use of automatic variables:
# - $<: the name of the prerequisite of the rule (a .cpp file)
# - $@: the name of the target of the rule (a .o file)
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Target to compile and run the program
run: $(EXEC)
	./$(EXEC)

# Clean up build files
clean:
	rm -f $(OBJECTS) $(EXEC)

# Phony targets for commands that don't create files
.PHONY: all clean
