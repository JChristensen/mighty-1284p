/*
  Copyright (C) 2016 Wayne Chu

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef Pins_Arduino_h
#define Pins_Arduino_h

#include <avr/pgmspace.h>

// Turn on this define when setting jumpers
// to use A4 and A5 for i2c vs analog pins
// See FootNote below for details
//#define _SB_BOARD_A4A5_I2C

// note: this define can be automatically be turned on through a menu entry
// in the boards.txt file by using the build extra_flags capability.
// i.e. using build.extra_flags=-D_SB_BOARD_A4A5_I2C

// ATMEL ATMEGA1284P on Sleeping Beauty board
//
//                            +---\/---+
//                (D 4) PB0 1 |        | 40 PA0 (D 21) AI 0
//                (D 5) PB1 2 |        | 39 PA1 (D 20) AI 1
//           INT2 (D 6) PB2 3 |        | 38 PA2 (D 19) AI 2
//       PWM/OC0A (D 7) PB3 4 |        | 37 PA3 (D 18) AI 3
//   PWM/OC0B/SS (D 10) PB4 5 |        | 36 PA4 (D 17) AI 4  *
//          MOSI (D 11) PB5 6 |        | 35 PA5 (D 16) AI 5  *
// PWM/OC3A/MISO (D 12) PB6 7 |        | 34 PA6 (D 30) AI 6
//  PWM/OC3B/SCK (D 13) PB7 8 |        | 33 PA7 (D 31) AI 7
//                      RST 9 |        | 32 AREF
//                     VCC 10 |        | 31 GND 
//                     GND 11 |        | 30 AVCC
//                   XTAL2 12 |        | 29 PC7 (D 14) 
//                   XTAL1 13 |        | 28 PC6 (D 15) 
//           RX0 (D 0) PD0 14 |        | 27 PC5 (D 27) TDI
//           TX0 (D 1) PD1 15 |        | 26 PC4 (D 26) TDO
//      INT0 RX1 (D 2) PD2 16 |        | 25 PC3 (D 25) TMS
//      INT1 TX1 (D 3) PD3 17 |        | 24 PC2 (D 24) TCK
//     PWM/OC1B (D 22) PD4 18 |        | 23 PC1 (D 28) SDA  *
//      PWM/OC1A (D 9) PD5 19 |        | 22 PC0 (D 29) SCL  *
//      PWM/OC2B (D 8) PD6 20 |        | 21 PD7 (D 23) PWM/OC2A
//                            +--------+
//
// *NOTE:
// Some boards contain a pair of jumpers which control A4 and A5 labeled pins.
// The Sleeping Beauty uses J4 and the BareBones boards use H5.
// The jumpers control which 1284 pins are physically connected to
// the pins labeled A4 and A5 on the board.
// When in the "deault"/"analog" or up position, the A4 and A5 labeled pins are
// connected to 1284 pins 35 and 35 which allows them to be used as analog
// inputs or digital pins using the A4 and A5 symbols in this header file.
//
// If the jumpers are in the "i2c" or down position, the A4 and A4 labeled
// pins are connected to 1284 pins 22 and 23 which is SCL and SDA.
// This allows the pins to be used for i2c or digital i/o but not for analog
// read operations.
// When jumpers are in this position, the symbols for A4 and A4 will not
// be correct unless the define above is also turned on.
//
/*
 *===========================================================================
 *
 * One of the major simplifications implemented by the Arduino core
 * libraries is the ability to reference the IO pins by a BOARD-defined "Pin
 * number" rather than needing to deal with the various IO register
 * addresses and bit numbers or masks that microcontrollers normally use to
 * access the external world.
 *
 * Of course, at some point the functions that use the "pin number" need to
 * translate that abstraction into the actual IO address and bits need to
 * manipulate them.  This is accomplished by core code in wiring_*.c that is
 * essentially identical for each major chip architecture (ie "avr"), and
 * this pins_arduino.h file that contains the specifics on a per-board or
 * per-chip basis.
 *
 * Various algorithms are possible, and there can be significant differences
 * depending on the capabilities of the architecture and chip being
 * used. (for example, a PIC32 has separate Set and Clear IO registers for
 * bitwise access, and an ARM CM3 might use "bit-banding")
 *

 * variants/<boarddesc>/pins_arduino.h contains the macros and/or tables
 * used to convert from Arduino-style "pin numbers" (0-13 on Uno, for
 * example) to the internal information necessary to perform operations on
 * those pins.
 *
 *===========================================================================
*/


/*
 * Most AVR-based Arduinos use tables built into flash (program) memory to
 * do the bulk of work, so we'll need the avr-libc definitions for dealing
 * with this additional address space.
 */

 
/*
 * Total number of digital pins.  This includes any analog pins that could
 * also be used for digital IO.
 */

#define NUM_DIGITAL_PINS            32

/*
 * Total number of Analog Input pins
 */

#define NUM_ANALOG_INPUTS           8


/*
 * Mapping macros
 * Some of these have to change depending on the board jumpers
 */

#ifdef _SB_BOARD_A4A5_I2C
#define analogInputToDigitalPin(p) \
  (\
    (p) == 0 ? 21 : \
    (p) == 1 ? 20 : \
    (p) == 2 ? 19 : \
    (p) == 3 ? 18 : \
    (p) == 4 ? 28 : \
    (p) == 5 ? 29 : \
    (p) == 6 ? 30 : \
    (p) == 7 ? 31 : \
    -1 )
#else
#define analogInputToDigitalPin(p) \
  (\
    (p) == 0 ? 21 : \
    (p) == 1 ? 20 : \
    (p) == 2 ? 19 : \
    (p) == 3 ? 18 : \
    (p) == 4 ? 17 : \
    (p) == 5 ? 16 : \
    (p) == 6 ? 30 : \
    (p) == 7 ? 31 : \
    -1 )
#endif

// comment next line to solve SPI problem?
//extern const uint8_t digital_pin_to_timer_PGM[NUM_DIGITAL_PINS];  

#define ifpin(p,what,ifnot) \
  (((p) >= 0 && (p) < NUM_DIGITAL_PINS) ? (what) : (ifnot))

#define digitalPinHasPWM(p) \
  ifpin(p,pgm_read_byte(digital_pin_to_timer_PGM + (p)) != NOT_ON_TIMER,1==0)

#ifdef _SB_BOARD_A4A5_I2C
#define digitalPinToAnalogPin(p) \
  (\
    (p) == 21 ? 0 : \
    (p) == 20 ? 1 : \
    (p) == 19 ? 2 : \
    (p) == 18 ? 3 : \
    (p) == 28 ? 4 : \
    (p) == 29 ? 5 : \
    (p) == 30 ? 6 : \
    (p) == 31 ? 7 : \
    -1 )
#else
#define digitalPinToAnalogPin(p) \
  (\
    (p) == 21 ? 0 : \
    (p) == 20 ? 1 : \
    (p) == 19 ? 2 : \
    (p) == 18 ? 3 : \
    (p) == 17 ? 4 : \
    (p) == 16 ? 5 : \
    (p) == 30 ? 6 : \
    (p) == 31 ? 7 : \
    -1 )
#endif

/*
 * This macro supports being passed an anlog pin # or the matching digital pin #
 * Note that this macro cheats by directly returning digitalPinToAnalog()
 * since it is known that there is a one to on mapping between the
 * analog pin # and the analog channel
 */
#define analogPinToChannel(p) \
  ( (p) < NUM_ANALOG_INPUTS ? (p) : digitalPinToAnalogPin(p)) 

/*===========================================================================*/

/*
 * Names for Alternate pin functions.
 * Note that the mapping from pin number to alternate function
 * varies significantly from chip to chip.  An Uno and a MEGA are
 * not the same, for example.
 */

/*
 * SPI Peripheral pins
 */

static const uint8_t SS   = 10;
static const uint8_t MOSI = 11;
static const uint8_t MISO = 12;
static const uint8_t SCK  = 13;

/*
 * I2C (TWI) peripheral pins
 */

static const uint8_t SDA = 28;
static const uint8_t SCL = 29;

static const uint8_t LED_BUILTIN = 13;

/*
 * Alternate names for analog pins when accessed as digital IO
 */

static const uint8_t A0 = 21;
static const uint8_t A1 = 20;
static const uint8_t A2 = 19;
static const uint8_t A3 = 18;
#ifdef _SB_BOARD_A4A5_I2C
static const uint8_t A4 = 28;
static const uint8_t A5 = 29;
#else
static const uint8_t A4 = 17;
static const uint8_t A5 = 16;
#endif
static const uint8_t A6 = 30;
static const uint8_t A7 = 31;

// this macro will inline to the equilivant of 4 if statements if the argument
// is not a compile time constant

// return pointer to PCICR register for valid pins, otherwise 0
#define digitalPinToPCICR(p)    ifpin(p,&PCICR,(uint8_t *)0)

// return associated PCIEx bit for PCICR register for valid pins, otherwise 0
// (0 was a bad choice, since 0 is a valid bit)
// The >> 3, (divide by 8) takes the 0-31 PCINTxx number from the pcint[] table and
// converts it to be a 0-3 number to correspond to the bit numbers of
// the PCIE0, PCIE1, PCIE2, PCIE3 bits in the PCICR register.
// This works because the pcint[] table assigned the values based on the PCINTxx
// numbers used in  PCMSK0 to PCMSK7.

#define digitalPinToPCICRbit(p) \
  ifpin(p,digital_pin_to_pcint[p] >> 3,0)

// Internal macro for macro below
// It converts from a PCICR PCIEx bit number to the corresponding PCMSKx
// register address
// i.e. PCIE0 is bit 0 in the PCICR and associated with the PCMSK0 register
// i.e. PCIE3 is bit 3 in the PCICR and associated with bit PCMSK3 register
// x is a PCIEx bit number
#define PORT_NDX_TO_PCMSK(x)  \
	(\
	(x) == 0 ? &PCMSK0 : \
	(x) == 1 ? &PCMSK1 : \
	(x) == 2 ? &PCMSK2 : \
	(x) == 3 ? &PCMSK3 : \
	(uint8_t *)0)

// return pointer to associated PCMSKx register for valid pins, otherwise 0
#define digitalPinToPCMSK(p) \
	ifpin(p,PORT_NDX_TO_PCMSK(digital_pin_to_pcint[p] >> 3),(uint8_t *)0)

// return associated mask bit for associated PCMSKx register for valid pins,
// otherwise 0
// (0 was a bad choice, since 0 is a valid bit)
#define digitalPinToPCMSKbit(p) \
  ifpin(p,digital_pin_to_pcint[p] & 0x7,0)

// return associated INTx number for associated/valid pins,
// otherwise NOT_AN_INTERRUPT
// This useful for sketches that use attachInterrupt()

#define digitalPinToInterrupt(p) \
	(\
	(p) == 2 ? 0 : \
	(p) == 3 ? 1 : \
	(p) == 6 ? 2 : \
	NOT_AN_INTERRUPT)

// Port defines
// Do not change these values as there are tables below that assume these indexes
#define PA 1
#define PB 2
#define PC 3
#define PD 4

// specify port for each pin D0-D31
#define PORT_D0 PD
#define PORT_D1 PD
#define PORT_D2 PD
#define PORT_D3 PD
#define PORT_D4 PB
#define PORT_D5 PB
#define PORT_D6 PB
#define PORT_D7 PB
#define PORT_D8 PD
#define PORT_D9 PD
#define PORT_D10 PB
#define PORT_D11 PB
#define PORT_D12 PB
#define PORT_D13 PB
#define PORT_D14 PC
#define PORT_D15 PC
#define PORT_D16 PA
#define PORT_D17 PA
#define PORT_D18 PA
#define PORT_D19 PA
#define PORT_D20 PA
#define PORT_D21 PA
#define PORT_D22 PD
#define PORT_D23 PD
#define PORT_D24 PC
#define PORT_D25 PC
#define PORT_D26 PC
#define PORT_D27 PC
#define PORT_D28 PC
#define PORT_D29 PC
#define PORT_D30 PA
#define PORT_D31 PA

// specify port bit for each pin D0-D31
#define BIT_D0 0
#define BIT_D1 1
#define BIT_D2 2
#define BIT_D3 3
#define BIT_D4 0
#define BIT_D5 1
#define BIT_D6 2
#define BIT_D7 3
#define BIT_D8 6
#define BIT_D9 5
#define BIT_D10 4
#define BIT_D11 5
#define BIT_D12 6
#define BIT_D13 7
#define BIT_D14 7
#define BIT_D15 6
#define BIT_D16 5
#define BIT_D17 4
#define BIT_D18 3
#define BIT_D19 2
#define BIT_D20 1
#define BIT_D21 0
#define BIT_D22 4
#define BIT_D23 7
#define BIT_D24 2
#define BIT_D25 3
#define BIT_D26 4
#define BIT_D27 5
#define BIT_D28 1
#define BIT_D29 0
#define BIT_D30 6
#define BIT_D31 7


//*===========================================================================*/
/*
 * The data tables used to map the Arduino pins should only get defined ONCE
 * in an entire sketch, usually in wiring_digital.c where they are most
 * used.  Do this by making the definitions conditional on the ARDUINO_MAIN
 * symbol, which is only defined (with #define) in that one source file.
 *
 * Other files can include pins_arduino.h to get the other defitions above.
 */

// macro equivalents of PROGMEM arrays port_to_mode_PGM[] etc. below
#define PORT_TO_MODE(x) \
  (\
  (x) == PA ? &DDRA : \
  (x) == PB ? &DDRB : \
  (x) == PC ? &DDRC : \
  (x) == PD ? &DDRD : \
  NOT_A_PORT )

#define PORT_TO_OUTPUT(x) \
  (\
  (x) == PA ? &PORTA : \
  (x) == PB ? &PORTB : \
  (x) == PC ? &PORTC : \
  (x) == PD ? &PORTD : \
  NOT_A_PORT)

#define PORT_TO_INPUT(x) \
  (\
  (x) == PA ? &PINA : \
  (x) == PB ? &PINB : \
  (x) == PC ? &PINC : \
  (x) == PD ? &PIND : \
  NOT_A_PORT)

// Dxx to PCINTxx pcint[] table
// This table contains an array that contains PCMSKx PCINTxx values
// It allows converting from an Arduino digital pin number to a PCINTxx value
// by simply indexing into the table by the digital pin number.
// i.e. pcint[0] will contain the PCINTxx value for arduino digital pin 0
//
// Note: Since the AVR does not support const data in flash like other processors,
// this table eats up RAM space since "const" data on the AVR has to be moved
// to RAM because of the h/w design of using multiple address spaces.
// So this table eats up 32 bytes of RAM.
#ifndef ARDUINO_MAIN
extern const uint8_t digital_pin_to_pcint[NUM_DIGITAL_PINS];
#else
const uint8_t digital_pin_to_pcint[NUM_DIGITAL_PINS] =
{
  24, // D0 PD0
  25, // D1 PD1
  26, // D2 PD2
  27, // D3 PD3
  8,  // D4 PB0
  9,  // D5 PB1
  10, // D6 PB2
  11, // D7 PB3
  30, // D8 PD6
  29, // D9 PD5
  12, // D10 PB4
  13, // D11 PB5
  14, // D12 PB6
  15, // D13 PB7
  23, // D14 PC7
  22, // D15 PC6
  5,  // D16 PA5
  4,  // D17 PA4
  3,  // D18 PA3
  2,  // D19 PA2
  1,  // D20 PA1
  0,  // D21 PA0
  28, // D22 PD4
  31, // D23 PD7
  18, // D24 PC2
  19, // D25 PC3
  20, // D26 PC4
  21, // D27 PC5
  17, // D28 PC1
  16, // D29 PC0
  6,  // D30 PA6
  7,  // D31 PA7
};

/*===========================================================================*/
 
/*
 * Pins are mapped in a two-step process.  First the pin number is
 * translated into "port" (PA, PB, etc) which is just a small integer.
 * Then the "port" is translated into an IO address depending on function.
 * This allows different IO address for Read, Write, and Cofiguration.
 * Separately the pin number is also translated to a bit mask within the
 * IO address, which is assumed to be the same across all functions.
 * Note that there is no requirement, and no guarantee, that adjacent
 * pin numbers be on the same IO address, although this is somewhat true
 * on Uno and other ATmegaxx8-based Arduinos.  Pins can be scattered across
 * any number of ports in any order.
 */
 
// these arrays map port names (e.g. PA, PB, PC, PD) to the
// appropriate addresses for various functions (e.g. reading
// and writing)

// port to configuration register address
const uint16_t PROGMEM port_to_mode_PGM[] =
{
	NOT_A_PORT,
	(uint16_t) &DDRA,
	(uint16_t) &DDRB,
	(uint16_t) &DDRC,
	(uint16_t) &DDRD,
};

// port to output register address

const uint16_t PROGMEM port_to_output_PGM[] =
{
	NOT_A_PORT,
	(uint16_t) &PORTA,
	(uint16_t) &PORTB,
	(uint16_t) &PORTC,
	(uint16_t) &PORTD,
};

// port to input register address

const uint16_t PROGMEM port_to_input_PGM[] =
{
	NOT_A_PORT,
	(uint16_t) &PINA,
	(uint16_t) &PINB,
	(uint16_t) &PINC,
	(uint16_t) &PIND,
};



/*
 * Additionally, we have a table to tell us which timer is associated
 * with a pin for use with the analogWrite() PWM function.  This allows
 * the PWM to be turned off when digitalWrite() is used, and also is
 * used by analogWrite() to compute which timer registers to modify.
 * A pin that is not capable of doing PWM is mapped to NOT_ON_TIMER.
 */

const uint8_t PROGMEM digital_pin_to_timer_PGM[NUM_DIGITAL_PINS] =
{
  NOT_ON_TIMER, // D0 PD0
  NOT_ON_TIMER, // D1 PD1
  NOT_ON_TIMER, // D2 PD2
  NOT_ON_TIMER, // D3 PD3
  NOT_ON_TIMER, // D4 PB0
  NOT_ON_TIMER, // D5 PB1
  NOT_ON_TIMER, // D6 PB2
  TIMER0A,      // D7 PB3
  TIMER2B,      // D8 PD6
  TIMER1A,      // D9 PD5
  TIMER0B,      // D10 PB4
  NOT_ON_TIMER, // D11 PB5
  TIMER3A,      // D12 PB6
  TIMER3B,      // D13 PB7
  NOT_ON_TIMER, // D14 PC7
  NOT_ON_TIMER, // D15 PC6
  NOT_ON_TIMER, // D16 PA5
  NOT_ON_TIMER, // D17 PA4
  NOT_ON_TIMER, // D18 PA3
  NOT_ON_TIMER, // D19 PA2
  NOT_ON_TIMER, // D20 PA1
  NOT_ON_TIMER, // D21 PA0
  TIMER1B,      // D22 PD4
  TIMER2A,      // D23 PD7
  NOT_ON_TIMER, // D24 PC2
  NOT_ON_TIMER, // D25 PC3
  NOT_ON_TIMER, // D26 PC4
  NOT_ON_TIMER, // D27 PC5
  NOT_ON_TIMER, // D28 PC1
  NOT_ON_TIMER, // D29 PC0
  NOT_ON_TIMER, // D30 PA6
  NOT_ON_TIMER, // D31 PA7
};

/* ===========================================================================
 * Nothing below this line should need to be altered/customized for a board
 * Since it uses data from the PORT_Dxx and BIT_Dxx macros
 */ 

/*
 * Pin number to port mapping
 * This table contains PA, PB, PC, PD values (1 to 4) and is used as an index
 * into the other progmem port_to_xxx_PGM[] tables to get the port register address
 */

const uint8_t PROGMEM digital_pin_to_port_PGM[NUM_DIGITAL_PINS] =
{
  PORT_D0,
  PORT_D1,
  PORT_D2,
  PORT_D3,
  PORT_D4,
  PORT_D5,
  PORT_D6,
  PORT_D7,
  PORT_D8,
  PORT_D9,
  PORT_D10,
  PORT_D11,
  PORT_D12,
  PORT_D13,
  PORT_D14,
  PORT_D15,
  PORT_D16,
  PORT_D17,
  PORT_D18,
  PORT_D19,
  PORT_D20,
  PORT_D21,
  PORT_D22,
  PORT_D23,
  PORT_D24,
  PORT_D25,
  PORT_D26,
  PORT_D27,
  PORT_D28,
  PORT_D29,
  PORT_D30,
  PORT_D31
};

/*
 * Pin number to bitmask mapping.
 * Note that _BV(n) is a mask with bit n set.  (1 << n)
 */

const uint8_t PROGMEM digital_pin_to_bit_mask_PGM[NUM_DIGITAL_PINS] =
{
  _BV(BIT_D0),
  _BV(BIT_D1),
  _BV(BIT_D2),
  _BV(BIT_D3),
  _BV(BIT_D4),
  _BV(BIT_D5),
  _BV(BIT_D6),
  _BV(BIT_D7),
  _BV(BIT_D8),
  _BV(BIT_D9),
  _BV(BIT_D10),
  _BV(BIT_D11),
  _BV(BIT_D12),
  _BV(BIT_D13),
  _BV(BIT_D14),
  _BV(BIT_D15),
  _BV(BIT_D16),
  _BV(BIT_D17),
  _BV(BIT_D18),
  _BV(BIT_D19),
  _BV(BIT_D20),
  _BV(BIT_D21),
  _BV(BIT_D22),
  _BV(BIT_D23),
  _BV(BIT_D24),
  _BV(BIT_D25),
  _BV(BIT_D26),
  _BV(BIT_D27),
  _BV(BIT_D28),
  _BV(BIT_D29),
  _BV(BIT_D30),
  _BV(BIT_D31)
};

#endif // ARDUINO_MAIN

#endif // Pins_Arduino_h
