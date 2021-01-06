CXX = gcc 
CXXFLAGS = -Wall

all: bin_heap

bin_heap:
	$(CXX) $(CXXFLAGS) -o main.x main.c graph.c binheap.c node.c total_orders.c utility.c

clean: 
	@rm *.x *.txt

.PHONY: all clean
