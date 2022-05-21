#CC=/usr/local/arm/4.2.2-eabi/usr/bin/arm-linux-gcc
CC=gcc
test: prog.o code.o main.o
	$(CC) -o test prog.o code.o main.o
main.o: test.c
	$(CC) -o main.o -c test.c
prog.o: prog.c prog.h code.h
	$(CC) -c prog.c -o prog.o
code.o: code.c code.h
	$(CC) -c code.c -o code.o
clean:
	rm -f *.O
