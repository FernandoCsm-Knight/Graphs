# Compiler and compiler flags
CXX := g++
CXXFLAGS := -Wall -Wextra -g -std=c++23 

# Source files
SRCDIR := src
SRCS := $(wildcard $(SRCDIR)/*.cpp)

# Object files directory
OBJDIR := obj
OBJS := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))

# Binary files directory
BINDIR := bin
EXE := $(BINDIR)/Main

# Log directory
LOGDIR := logs

# Test files
TESTDIR := test
TEST_SRCS := $(wildcard $(TESTDIR)/*.cpp)
TEST_OBJS := $(patsubst $(TESTDIR)/%.cpp,$(OBJDIR)/%.o,$(TEST_SRCS))
TEST_EXE := $(BINDIR)/Test

# Data files
TMPDIR := tmp
DATADIR := data
IMGDIR := img

# Output directories
OUTPUT_DIRS := $(OBJDIR) $(BINDIR) $(DATADIR) $(TMPDIR) $(IMGDIR)
CLEAN_DIRS := $(OBJDIR) $(BINDIR) $(TMPDIR)

# Graphviz DOT file
DOTFILE := toPlot.dot
DOTPNGFILE := graph_from_dot.png

# Phony targets
.PHONY: all clean test dot create_dirs

# Default target
all: create_dirs $(EXE)

# Rule to build the executable
$(EXE): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rule to build object files from source directory
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to build object files from test directory
$(OBJDIR)/%.o: $(TESTDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Test target
test: $(TEST_EXE)
	@mkdir -p $(TESTDIR)/$(LOGDIR)
	./$(TEST_EXE)

# Rule to build the test executable
$(TEST_EXE): $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

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
	rm -r $(CLEAN_DIRS)

# Clean img directory
clean_img:
	rm -r $(IMGDIR)/*

# Clean data directory
clean_data:
	rm -r $(DATADIR)/*

# Generate Graphviz DOT file
dot: $(EXE)
	dot -Tpng $(TMPDIR)/$(DOTFILE) -o $(IMGDIR)/$(DOTPNGFILE)

# Create output directories
create_dirs:
	@mkdir -p $(OUTPUT_DIRS)
