# Compiler settings
CXX = g++
CXXFLAGS = -Wall -g

# For wxWidgets
WX_CONFIG := wx-config
WX_CXXFLAGS := $(shell $(WX_CONFIG) --cxxflags)
WX_LIBS := $(shell $(WX_CONFIG) --libs)

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
	@mkdir -p $(BINDIR)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(WX_LIBS)

# Rule for compiling source files to object files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) -c -o $@ $< $(CXXFLAGS) $(WX_CXXFLAGS)

# Clean up build files
clean:
	rm -rf $(OBJDIR) $(BINDIR)

# Non-file targets
.PHONY: all clean
