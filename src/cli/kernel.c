#include "../uart/uart.h"
#include "../global/global.h"
#include "../commands/os.h"
#include "../helper/utils/utils.h"

#define MAX_CMD_SIZE 100

void cli()
{
	static char cli_buffer[MAX_CMD_SIZE];
	static int index = 0;
	static int is_new_command = 1;

	if (is_new_command == 1)
	{
		uart_puts("\nBrightOS> ");
		is_new_command = 0;
	}

	char c = uart_getc();

	// Check for backspace
	if (c == '\b')
	{
		if (index > 0)
		{
			index--;
			cli_buffer[index] = '\0';
			uart_puts("\b \b");
		}
	}
	else
	{
		if (c != '\n')
		{
			if (index < MAX_CMD_SIZE - 1)
			{
				cli_buffer[index] = c;
				index++;
				uart_sendc(c);
			}
		}
		else
		{
			cli_buffer[index] = '\0';

			uart_puts("\nGot commands: ");
			uart_puts(cli_buffer);

			if (strcmp(cli_buffer, "os") == 0)
			{
				os_greet();
			}

			uart_puts("\n");

			index = 0;
			is_new_command = 1;
		}
	}
}

int main()
{
	// set up serial console
	uart_init();

	// Welcome message
	os_greet();

	while (1)
	{
		cli();
	}
	return 0;
}
