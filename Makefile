# Compiler settings - Can be customized.
CXX = g++
CXXFLAGS = -Wall -g

# For wxWidgets
WX_CONFIG := wx-config
 
WX_CXXFLAGS := $(shell $(WX_CONFIG) --cxxflags)
WX_LIBS := $(shell $(WX_CONFIG) --libs)

# Directories
SRCDIR = src
OBJDIR = obj
BINDIR = bin

SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
TARGET = $(BINDIR)/eye_saver

# Default target
all: $(TARGET)

# Rule for linking final executable
$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(WX_LIBS)

# Rule for compiling source files to object files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGS) $(WX_CXXFLAGS)

# Clean up build files
clean:
	rm $(OBJDIR)/* $(TARGET)

# Non-file targets
.PHONY: all clean

