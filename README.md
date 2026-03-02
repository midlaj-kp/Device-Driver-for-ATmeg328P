# GPIO Device Driver – Bare Metal (ATmega328P)

## Overview

This branch contains a bare-metal GPIO driver implementation for the ATmega328P microcontroller (Arduino UNO).

### Objective

- Configure Pin 13 (PB5) as output
- Toggle onboard LED every 500ms
- Do NOT use Arduino libraries
- Use direct register-level programming only

---

## Hardware Details

- **Board:** Arduino UNO  
- **Microcontroller:** ATmega328P  
- **Clock Frequency:** 16 MHz  
- **LED Pin:** Digital 13 (PB5)

---

## Register-Level Understanding

Pin 13 corresponds to:

- **Port:** PORTB  
- **Bit:** PB5  

Relevant registers:

- `DDRB`  → Data Direction Register B  
- `PORTB` → Output Register  

---

## Step 1: Configure Pin as Output

```c
DDRB |= (1 << DDB5);
```

### Explanation

- `DDB5` is bit 5 of `DDRB`
- Setting this bit to `1` configures PB5 as **OUTPUT**

If DDR bit = 0 → Input  
If DDR bit = 1 → Output  

---

## Step 2: Toggle the LED

```c
PORTB ^= (1 << PORTB5);
```

### Explanation

- XOR operation flips bit 5
- If LED is ON → becomes OFF
- If LED is OFF → becomes ON

This is hardware-level toggling using bitwise manipulation.

---

## Timing Control

Clock defined as:

```c
#define F_CPU 16000000UL
```

Delay used:

```c
_delay_ms(500);
```

This creates a 500ms toggle interval.

---

## Program Flow

1. Configure PB5 as output
2. Toggle PORTB bit 5
3. Wait 500ms
4. Repeat continuously

---

## Why This Is Bare Metal

- No `pinMode()`
- No `digitalWrite()`
- No `delay()`
- Direct manipulation of hardware registers
- Fully based on ATmega328P datasheet

---

## Expected Output

The onboard LED connected to Pin 13 blinks every 500ms continuously.

---

## Learning Outcomes

- Understanding DDRx and PORTx registers
- Bitwise operations in embedded C
- GPIO hardware architecture
- Direct hardware control without abstraction
