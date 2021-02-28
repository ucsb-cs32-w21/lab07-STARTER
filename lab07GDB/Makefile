CC = g++
CFLAGS = -Wall -g -pedantic
MAIN = example
OBJS = example.o
all : $(MAIN)

$(MAIN) : $(OBJS)
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS)

example.o : example.cpp
	$(CC) $(CFLAGS) -c example.cpp

clean :
	rm *.o $(MAIN)
