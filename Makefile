all: main clean

main: main.o imagens.o
	gcc -o main main.o imagens.o

imagens.o: modulo_imagens_ppm.c modulo_imagens_ppm.h
	gcc -o imagens.o -c modulo_imagens_ppm.c

main.o: main.c modulo_imagens_ppm.h
	gcc -o main.o -c main.c

clean:
	rm *.o


