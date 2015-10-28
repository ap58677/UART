CFLAGS= -Wall -g

all: 
		mkdir -p bin
		gcc $(CFLAGS) -o bin/UART_I_O src/UART_I_O.c
		gcc $(CFLAGS) -o bin/main src/main.c
		gcc $(CFLAGS) -o bin/led_toggle src/led_toggle.c

clean:
		rm -rf bin
