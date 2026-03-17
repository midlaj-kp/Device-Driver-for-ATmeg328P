# UART Device Driver – Bare Metal (ATmega328P)

## Overview

This branch contains a bare-metal UART driver implementation for the ATmega328P microcontroller (Arduino UNO).

### Objective

- Initialize UART at 9600 baud
- Configure 8-N-1 frame format
- Transmit string every 1000ms
- Do NOT use Arduino Serial library
- Use direct register-level programming only

---

## Hardware Details

- **Board:** Arduino UNO  
- **Microcontroller:** ATmega328P  
- **Clock Frequency:** 16 MHz  
- **Communication:** UART0  

---

## Baud Rate Calculation

Formula from datasheet:

```
UBRR = (F_CPU / (16 × Baud)) - 1
```

For:

- F_CPU = 16,000,000
- Baud = 9600

Result:

```
UBRR = 103
```

---

## Registers Used

- `UBRR0H`, `UBRR0L` → Baud rate setting
- `UCSR0A` → Status register
- `UCSR0B` → Control register B
- `UCSR0C` → Control register C
- `UDR0` → Data register

---

## Step 1: Set Baud Rate

```c
UBRR0H = (unsigned char)(UBRR_VALUE >> 8);
UBRR0L = (unsigned char)UBRR_VALUE;
```

Sets UART baud rate to 9600.

---

## Step 2: Enable Transmitter

```c
UCSR0B = (1 << TXEN0);
```

`TXEN0` enables UART transmission.

---

## Step 3: Configure Frame Format (8-N-1)

```c
UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
```

Configuration:

- 8 Data bits
- No Parity
- 1 Stop bit (default)

This creates standard 8-N-1 communication.

---

## Step 4: Transmit Data

```c
while (!(UCSR0A & (1 << UDRE0)));
UDR0 = data;
```

### Explanation

- Wait until transmit buffer is empty
- Load data into `UDR0`
- Hardware shifts data automatically

---

## Sending a String

```c
while (*str)
{
    UART_transmit(*str++);
}
```

Iterates through characters until null terminator.

---

## Program Flow

1. Initialize UART
2. Send `"Hello from UART\r\n"`
3. Wait 1000ms
4. Repeat continuously

---

## Expected Output

When Serial Monitor is opened at 9600 baud:

```
Hello from UART
Hello from UART
Hello from UART
```

Message appears every second.

---

## Why This Is Bare Metal

- No `Serial.begin()`
- No `Serial.print()`
- Manual baud rate calculation
- Bit-level configuration of control registers
- Datasheet-driven implementation

---

## Learning Outcomes

- Understanding UART hardware architecture
- Baud rate calculation
- Frame format configuration
- Transmit buffer handling
- Direct peripheral control via registers
