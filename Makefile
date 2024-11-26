# Compiler settings
CXX = g++
CXXFLAGS = -Wall -g -Iinclude -Iinc -I/usr/include/freetype2 -I/usr/include/glm

# For GLFW and GLAD
LIBS = -lglfw -lm -ldl -lfreetype

SRCDIR = src
OBJDIR = obj
BINDIR = bin
LIBDIR = lib

SOURCES = $(wildcard $(SRCDIR)/*.cpp) $(LIBDIR)/glad.c
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
OBJECTS := $(OBJECTS:$(LIBDIR)/%.c=$(OBJDIR)/%.o)
TARGET = $(BINDIR)/eye_saver

# Default target
all: $(TARGET)

# Rule for linking final executable
$(TARGET): $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

# Rule for compiling source files to object files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

# Rule for compiling glad.c to object file
$(OBJDIR)/glad.o: $(LIBDIR)/glad.c
	@mkdir -p $(OBJDIR)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

# Clean up build files
clean:
	rm -rf $(OBJDIR) $(BINDIR)

# Non-file targets
.PHONY: all clean
