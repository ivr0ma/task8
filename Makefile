PROG = matr
CC=g++
CFLAGS = -c -Wall

all: $(PROG)

$(PROG): main.o ATD.o
	$(CC) main.o ATD.o -o $(PROG)

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp
ATD.o: ATD.cpp ATD.h
	$(CC) $(CFLAGS) $< -o $@
clean:
	rm -f *.o $(PROG)
run:
	./$(PROG)
runv:
	valgrind ./$(PROG)
