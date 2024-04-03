# Compiler settings - Can be customized.
CXX = g++
CXXFLAGS = -Iinclude -Wall -g

# Directories
SRCDIR = src
OBJDIR = obj
BINDIR = bin
INCDIR = inc

# Find all source files in the source directory, sorted by most recently modified
SOURCES = $(shell find $(SRCDIR) -name '*.cpp' | sort -k 1nr | cut -f2-)
# Substitute .cpp file extension with .o for object files
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
# Name of final executable
TARGET = $(BINDIR)/myapp

# Default target
all: $(TARGET)

# Rule for linking final executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Rule for compiling source files to object files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -rf $(OBJDIR)/* $(TARGET)

# Non-file targets
.PHONY: all clean

