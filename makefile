CFLAGS= -Wall -g

all: 
		mkdir -p bin
		gcc $(CFLAGS) -o bin/UART_I_O src/UART_I_O.c
		gcc $(CFLAGS) -o bin/main src/main.c

clean:
		rm -rf bin
