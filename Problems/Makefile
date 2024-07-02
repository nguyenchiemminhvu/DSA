# Find all directories containing main.cpp files
SRC_DIRS := $(shell find . -type f -name main.cpp -exec dirname {} \;)
TARGETS := $(foreach dir,$(SRC_DIRS),$(dir)/main)

all: $(TARGETS)

$(TARGETS): %/main: %/main.cpp
	@echo "Compiling $<"
	g++ -std=c++11 $< -o $@ -lDSA

clean:
	@echo "Cleaning up..."
	@find . -type f -name main -exec rm -f {} \;

.PHONY: all clean
