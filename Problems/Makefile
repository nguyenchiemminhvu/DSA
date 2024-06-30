SUBDIRS := \
	AdvancedTechniques \
	ArrayAndString \
	Backtracking \
	DynamicProgramming \
	GameTheories \
	Geometrics \
	Graphs \
	Greedy \
	Mathematics \
	RangeQueries \
	SlidingWindow \
	SortingAndSearching \
	Tree

TARGETS := $(patsubst %,%/ProblemA/main,$(SUBDIRS))

all: $(TARGETS)

$(TARGETS):
	@echo "Compiling $@"
	$(MAKE) -C $(dir $@) main

%/ProblemA/main: %/ProblemA/main.cpp
	g++ $< -o $@ -lDSA

clean:
	@for dir in $(SUBDIRS); do \
		echo "Cleaning $$dir/ProblemA"; \
		rm -f $$dir/ProblemA/main; \
	done

.PHONY: all clean $(SUBDIRS)
