// #include "uart.h"
#include "../global/src/strings.c"

#define MAX_CMD_SIZE 100

// void cli()
// {
// 	static char cli_buffer[MAX_CMD_SIZE];
// 	static int index = 0;

// 	//read and send back each char
// 	char c = uart_getc();
// 	uart_sendc(c);

// 	//put into a buffer until got new line character
// 	if (c != '\n'){
// 		cli_buffer[index] = c; //Store into the buffer
// 		index++;
// 	} else if (c == '\n'){
// 		cli_buffer[index] = '\0';

// 		uart_puts("\nGot commands: ");
// 		uart_puts(cli_buffer); uart_puts("\n");

// 		/* Compare with supported commands and execute
// 		* ........................................... */

// 		//Return to command line
// 		index = 0;
// 	}
// }

int main()
{
	// set up serial console
	// uart_init();
	// uart_puts("Hello World!\n");

	// run CLI

	OS_Greet();

	// char *cli_buffer = "Hello World!";

	while (1)
	{
		// cli();
		// uart_puts(cli_buffer);
		break;
	}

	return 0;
}
