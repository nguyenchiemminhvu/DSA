# Find all directories containing main.cpp files
SRC_DIRS := $(shell find . -type f -name main.cpp -exec dirname {} \;)
TARGETS := $(foreach dir,$(SRC_DIRS),$(dir)/main)

all: DSA_LIB $(TARGETS)

DSA_LIB:
	cd $(realpath $(PWD)/../) && autoreconf -i
	cd $(realpath $(PWD)/../) && ./configure
	cd $(realpath $(PWD)/../) && make
	cd $(realpath $(PWD)/../) && sudo make install-strip
	cd $(realpath $(PWD)/../) && git clean -df

$(TARGETS): %/main: %/main.cpp
	@echo "Compiling $<"
	g++ -std=c++11 -fpermissive $< -o $@ -lDSA

clean:
	@echo "Cleaning up..."
	@find . -type f -name main -exec rm -f {} \;

.PHONY: all clean
