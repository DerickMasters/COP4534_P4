# compiler
CC = g++

# compiler flags
CFLAGS = -std=c++11 -g -Wall

OBJECTS = RngGen.o GenBatchDataSet.o GenBacteriaDataSet.o BatchMonteCarlo.o BacteriaMonteCarlo.o 
HEADERS := $(shell find ./  -name "*.hpp")

$(OBJECTS) : $(HEADERS)
	$(CC) $(CFLAGS) RngGen.cpp -c -o RngGen.o
	$(CC) $(CFLAGS) GenBatchDataSet.cpp -c -o GenBatchDataSet.o
	$(CC) $(CFLAGS) GenBacteriaDataSet.cpp -c -o GenBacteriaDataSet.o
	$(CC) $(CFLAGS) BatchMonteCarlo.cpp -c -o BatchMonteCarlo.o
	$(CC) $(CFLAGS) BacteriaMonteCarlo.cpp -c -o BacteriaMonteCarlo.o

main.o :
	$(CC) $(CFLAGS) main.cpp -c -o main.o
main: $(OBJECTS) main.o
	$(CC) $(CFLAGS) -o $@ $^

clean: 
	$(RM) *.o *.gch ds*.txt core main 
