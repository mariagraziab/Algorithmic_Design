CXX = gcc 
CXXFLAGS = -Wall

all: bin_heap_array

bin_heap_array: 
	$(CXX) $(CXXFLAGS) -o main.x main.c heap.c orders.c utility.c
	
clean: 
	@rm *.x *.txt

.PHONY: all clean
