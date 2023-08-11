# Compiler and compiler flags
CXX := g++
CXXFLAGS := -Wall -Wextra -g

# Source files
SRCDIR := src
SRCS := $(wildcard $(SRCDIR)/*.cpp)

# Object files directory
OBJDIR := obj
OBJS := $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.cpp=.o)))

# Binary files direcotry
BINDIR := bin
EXE := $(BINDIR)/main

# Phony targets
.PHONY: all clean

# Default target
all: $(EXE)

# Rule to build the executable
$(EXE): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rule to build object files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Valgrind target
valgrind: $(EXE)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(EXE)

# Run target
run: $(EXE)
	./$(EXE)

# Rebuild target
rebuild: clean all

# Rebuild and run target
rerun: rebuild run

# Clean the generated files
clean:
	$(RM) -r $(OBJDIR) $(EXE)