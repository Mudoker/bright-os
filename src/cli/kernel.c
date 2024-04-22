#include "../uart/uart.h"
#include "../global/global.h"

#define MAX_CMD_SIZE 100

void cli()
{
	static char cli_buffer[MAX_CMD_SIZE];
	static int index = 0;

	// read and send back each char
	char c = uart_getc();
	uart_sendc(c);

	// put into a buffer until got new line character
	if (c != '\n')
	{
		cli_buffer[index] = c; // Store into the buffer
		index++;
	}
	else if (c == '\n')
	{
		cli_buffer[index] = '\0';

		uart_puts("\nGot commands: ");
		uart_puts(cli_buffer);
		uart_puts("\n");

		/* Compare with supported commands and execute
		 * ........................................... */

		// Return to command line
		index = 0;
	}
}

int main()
{
	// set up serial console
	uart_init();

	// run CLI
	char *cli_buffer = "Hello World!\n";
	uart_puts(cli_buffer);

	while (1)
	{
		cli();
	}
	return 0;
}