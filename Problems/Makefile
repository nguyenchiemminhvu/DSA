# Find all directories containing solve.cpp files
SRC_DIRS := $(shell find . -type f -name solve.cpp -exec dirname {} \;)
TARGETS := $(foreach dir,$(SRC_DIRS),$(dir)/solve)

all: $(TARGETS)

$(TARGETS): %/solve: %/solve.cpp
	@echo "Compiling $<"
	g++ -std=c++17 -fpermissive $< -o $@

clean:
	@echo "Cleaning up..."
	@find . -type f -name solve -exec rm -f {} \;

.PHONY: all clean
