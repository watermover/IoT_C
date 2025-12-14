all: prog

prog: main.o temp_api.o
	clang -o prog main.o temp_api.o

main.o: main.c temp_api.h
	clang -c -o main.o main.c

temp_api.o: temp_api.c temp_api.h
	clang -c -o temp_api.o temp_api.c

clean:
	rm -rf *.o prog
