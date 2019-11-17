# compiler
CC = g++

# compiler flags
CFLAGS = -std=c++11 -g -Wall

OBJECTS = CityRoute.o Matrix.o Tour.o heap.o BruteForceAlgorithm.o GeneticAlgorithm.o 
HEADERS := $(shell find ./  -name "*.hpp")

$(OBJECTS) : $(HEADERS)
	$(CC) $(CFLAGS) CityRoute.cpp -c -o CityRoute.o
	$(CC) $(CFLAGS) Matrix.cpp -c -o Matrix.o
	$(CC) $(CFLAGS) Tour.cpp -c -o Tour.o
	$(CC) $(CFLAGS) heap.cpp -c -o heap.o
	$(CC) $(CFLAGS) BruteForceAlgorithm.cpp -c -o BruteForceAlgorithm.o
	$(CC) $(CFLAGS) GeneticAlgorithm.cpp -c -o GeneticAlgorithm.o

main.o :
	$(CC) $(CFLAGS) main.cpp -c -o main.o
main: $(OBJECTS) main.o
	$(CC) $(CFLAGS) -o $@ $^

clean: 
	$(RM) *.o *.gch core main 
