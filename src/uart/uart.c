#include "./uart.h"
#include "../helper/styler/styler.h"

/**
 * Set baud rate and characteristics (115200 8N1) and map to GPIO
 */
void uart_init() {
  unsigned int r;

  /* Turn off UART0 */
  UART0_CR = 0x0;

  // Set Handshaking RTS/CTS
  if (HANDSHAKE_CONFIG == 1) {
    // Configure GPIO 16 as CTS and GPIO 17 as RTS
    r = GPFSEL1;
    r &= ~((7 << 18) | (7 << 21)); // clear bits 21-18 (FSEL17, FSEL16)
    r |= (7 << 18) | (7 << 21);    // Set value 0b100 (select ALT3)

    // Turn off GPIO 14 and 15
    r &= ~((7 << 12) | (7 << 15)); // clear bits 17-12 (FSEL15, FSEL14)

    GPFSEL1 = r;

    // Enable pull-up on GPIO 16, 17
    GPPUD = 0; // No pull up/down control
    r = 150;
    while (r--) {
      __asm volatile("nop");
    } // waiting 150 cycles

    GPPUDCLK0 = (1 << 16) | (1 << 17); // enable clock for GPIO 16, 17
    r = 150;
    while (r--) {
      __asm volatile("nop");
    } // waiting 150 cycles

    GPPUDCLK0 = 0; // flush GPIO setup

    // Enable RTS/CTS
    UART0_CR |= UART0_CR_CTSEN | UART0_CR_RTSEN;
  } else {
    // Configure GPIO 14 as TXD and GPIO 15 as RXD
    r = GPFSEL1;
    r &= ~((7 << 12) | (7 << 15)); // clear bits 17-12 (FSEL15, FSEL14)
    r |= (0b100 << 12) |
         (0b100 << 15); // Set value 0b100 (select ALT0: TXD0/RXD0)

    // Turn off GPIO 16 and 17
    r &= ~((7 << 18) | (7 << 21)); // clear bits 21-18 (FSEL17, FSEL16)

    GPFSEL1 = r;

    // Enable pull-up on GPIO 14, 15
    GPPUD = 0; // No pull up/down control
    r = 150;
    while (r--) {
      __asm volatile("nop");
    } // waiting 150 cycles

    GPPUDCLK0 = (1 << 14) | (1 << 15); // enable clock for GPIO 14, 15
    r = 150;
    while (r--) {
      __asm volatile("nop");
    } // waiting 150 cycles

    GPPUDCLK0 = 0; // flush GPIO setup

    // Disable RTS/CTS
    UART0_CR &= ~UART0_CR_CTSEN;
    UART0_CR &= ~UART0_CR_RTSEN;
  }

  /* Mask all interrupts */
  UART0_IMSC = 0;

  /* Clear pending interrupts */
  UART0_ICR = 0x7FF;

  /* Set integer & fractional part of Baud rate */
  UART0_IBRD = BAUD_RATE_CONFIG.ibrd;
  UART0_FBRD = BAUD_RATE_CONFIG.fbrd;

  /* Set up the Line Control Register */

  // Set data bits
  if (DATA_BITS_CONFIG == 5) {
    UART0_LCRH = UART0_LCRH_FEN | UART0_LCRH_WLEN_5BIT;
  } else if (DATA_BITS_CONFIG == 6) {
    UART0_LCRH = UART0_LCRH_FEN | UART0_LCRH_WLEN_6BIT;
  } else if (DATA_BITS_CONFIG == 7) {
    UART0_LCRH = UART0_LCRH_FEN | UART0_LCRH_WLEN_7BIT;
  } else if (DATA_BITS_CONFIG == 8) {
    UART0_LCRH = UART0_LCRH_FEN | UART0_LCRH_WLEN_8BIT;
  }

  // Set stop bits
  if (STOP_BIT_CONFIG == 1) {
    UART0_LCRH &= ~UART0_LCRH_STP2;
  } else if (STOP_BIT_CONFIG == 2) {
    UART0_LCRH |= UART0_LCRH_STP2;
  }

  // Set parity
  if (PARITY_CONFIG == 0) {
    UART0_LCRH &= ~UART0_LCRH_PEN;
  } else if (PARITY_CONFIG == 1) {
    UART0_LCRH |= UART0_LCRH_PEN;
    UART0_LCRH &= ~UART0_LCRH_EPS;
  } else if (PARITY_CONFIG == 2) {
    UART0_LCRH |= UART0_LCRH_PEN;
    UART0_LCRH |= UART0_LCRH_EPS;
  }

  /* Enable UART0, receive, and transmit */
  if (HANDSHAKE_CONFIG == 1) {
    UART0_CR = 0xC301; // enable Tx, Rx, FIFO
  } else {
    UART0_CR = 0x301; // enable Tx, Rx, FIFO
  }
}

/**
 * Send a character
 */
void uart_sendc(char c) {
  /* Check Flags Register */
  /* And wait until transmitter is not full */
  do {
    __asm volatile("nop");
  } while (UART0_FR & UART0_FR_TXFF);

  /* Write our data byte out to the data register */
  UART0_DR = c;
}

/**
 * Receive a character
 */
char uart_getc() {
  char c = 0;

  /* Check Flags Register */
  do {
    __asm volatile("nop");
  } while ((UART0_FR & UART0_FR_RXFE));

  /* read it and return */
  c = (unsigned char)(UART0_DR);

  /* convert carriage return to newline */
  return (c == '\r' ? '\n' : c);
}

/**
 * Display a string
 */
void uart_puts(char *s) {
  while (*s) {
    /* convert newline to carriage return + newline */
    if (*s == '\n')
      uart_sendc('\r');
    uart_sendc(*s++);
  }
}

// Calculate baud rate
BaudRateConfig get_baud_rate(int baud_rate) {
  int valid_baud[] = {300,   600,   1200,  2400,   4800,   9600,   14400,
                      19200, 38400, 57600, 921600, 230400, 460800, 115200};

  BaudRateConfig config;

  for (int i = 0; i <= 13; i++) {
    if (baud_rate == valid_baud[i]) {
      uart_puts("\n\nBaud rate set to ");
      uart_dec(baud_rate);
      uart_puts("\n");
      break;
    }

    if (i == 13) {
      // Return default baud rate
      str_format("\n\nInvalid baud rate \n", OS_CONFIG.ERROR,
                 OS_CONFIG.BACKGROUND_COLOR);

      str_format("Supported values: 300, 1200, 2400, 4800, 9600, "
                 "19200, 38400, 57600, 115200, 230400, 460800, 921600\n\n",
                 OS_CONFIG.SECONDARY_COLOR, OS_CONFIG.BACKGROUND_COLOR);

      str_format("Reverting... \n", OS_CONFIG.ERROR,
                 OS_CONFIG.BACKGROUND_COLOR);
      config = BAUD_RATE_CONFIG;
      return config;
    }
  }

  // Calculate Divider
  float divider = (float)UART_CLK / (16.0f * baud_rate);

  // Calculate integer and fractional parts of Divider
  int integerPart = (int)divider;
  float fractionalPart = divider - integerPart;

  // Calculate the integer part of the baud rate divisor
  config.ibrd = integerPart;

  // Calculate the fractional part of the baud rate divisor
  config.fbrd = (int)(fractionalPart * 64 + 0.5);

  return config;
}

/**
 * Display a value in hexadecimal format
 */
void uart_hex(unsigned int num) {
  uart_puts("0x");
  for (int pos = 28; pos >= 0; pos = pos - 4) {
    // Get highest 4-bit nibble
    char digit = (num >> pos) & 0xF;
    /* Convert to ASCII code */
    // 0-9 => '0'-'9', 10-15 => 'A'-'F'
    digit += (digit > 9) ? (-10 + 'A') : '0';
    uart_sendc(digit);
  }
}

/**
 * Display a value in decimal format
 */
void uart_dec(int num) {
  // A string to store the digit characters
  char str[33] = "";
  // Calculate the number of digits
  int len = 1;
  int temp = num;
  while (temp >= 10) {
    len++;
    temp = temp / 10;
  }
  // Store into the string and print out
  for (int i = 0; i < len; i++) {
    int digit = num % 10; // get last digit
    num = num / 10;       // remove last digit from the number
    str[len - (i + 1)] = digit + '0';
  }
  str[len] = '\0';
  uart_puts(str);
}
