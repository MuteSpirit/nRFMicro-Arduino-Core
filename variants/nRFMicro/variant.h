#ifndef _NRFMICRO_H_
#define _NRFMICRO_H_

#define TARGET_NRFMICRO

// NOTE:
//
// PIN NUMBERS AND RELATED CONSTANTS ARE DECLARED AS ENUM CONSTANTS
// INSTEAD OF MACROS.
//
// Macros named Dn can clash with identifiers used by third-party
// libraries (e.g. the Embedded Template Library), since a macro
// expands textually inside the library's own code. Enum constants
// are real identifiers, so they don't clash, and unlike a variable
// they need no `static`, work in both C and C++ files, are true
// compile-time constants, and never cause linker redefinition errors.
//
// EXCEPTION: PIN_SERIAL1_TX/RX must remain macros (see below).

/** Master clock frequency */
enum
{
    VARIANT_MCK = 64000000ul,
};

// ASSUMES CRYSTAL OSCILLATOR IS USED
#define USE_LFXO      // Board uses 32khz crystal for LF
//#define USE_LFRC    // Board uses RC for LF

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "WVariant.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

enum
{
    PINS_COUNT = 28,
    NUM_DIGITAL_PINS = 28,
    NUM_ANALOG_INPUTS = 7,
    NUM_ANALOG_OUTPUTS = 0,
};

enum
{
    // 3V3 Regulator Disable
    PIN_EXT_VCC = 26, // EXT_VCC is P1.09 (set high to disable 3v3)
    EXT_VCC = PIN_EXT_VCC,
};

// LEDs
enum
{
    PIN_LED = 27, // USR LED is P1.10
    LED_PWR = PINS_COUNT, // no LED_PWR
    PIN_NEOPIXEL = PINS_COUNT, // no neopixel
    NEOPIXEL_NUM = 0,
    LED_BLUE = PIN_LED, // required by bluefruit library

    LED_BUILTIN = PIN_LED,

    LED_STATE_ON = 1,         // State when LED is on
};

enum
{
    PIN_VBAT = 25, // P0.04/AIN2 (VBAT) - reads battery voltage
};

/*
 * Buttons
 */
#define PIN_BUTTON1          (PINS_COUNT) // no button as of version 1.2

// Digital PINs
// NOTE: THIS IS A RENUMBERING OF THE PINS
// AND DOES NOT CORRESPOND TO THE NICENANO OR
// PROMICRO DIAGRAM

// NOTE:
//
// DIGITAL PIN NUMBERS ARE DECLARED AS ENUM CONSTANTS INSTEAD OF MACROS.
//
// Macros named Dn can clash with identifiers used by third-party
// libraries (e.g. the Embedded Template Library), since a macro
// expands textually inside the library's own code. Enum constants
// are real identifiers, so they don't clash, and unlike a variable
// they need no `static`, work in both C and C++ files, are true
// compile-time constants, and never cause linker redefinition errors.

// left side (top to bottom)
enum
{
  D0  = 0,  // P0.06 (TX)
  D1  = 1,  // P0.08 (RX)
  D2  = 2,  // P0.17 (SCK)
  D3  = 3,  // P0.17 (MISO)
  D4  = 4,  // P0.20 (MOSI)
  D5  = 5,  // P0.13 (SDA)
  D6  = 6,  // P0.24 (SCL)
  D7  = 7,  // P0.09 (NFC1)
  D8  = 8,  // P0.10 (NFC2)
  D9  = 9,  // P1.06 (CS)
};

// right side (bottom to top)
enum
{
  D10 = 10, // P1.11
  D11 = 11, // P0.28/AIN4 (A0)
  D12 = 12, // P0.03/AIN1 (A1)
  D13 = 13, // P1.13
  D14 = 14, // P0.02/AIN0 (A2)
  D15 = 15, // P0.29/AIN5 (A3)
  D16 = 16, // P0.31/AIN7 (A4)
  D17 = 17, // P0.30/AIN6 (A5)
};

// extra center pins (clockwise from bottom left, viewed from bottom side of board)
// only using through-hole pins
// P0.05 (AIN3) is a surface mount that isn't broken out

// four free pins on the left (bottom to top)
enum
{
  D18 = 18, // P1.04 (SCK1)
  D19 = 19, // P1.02 (MISO1)
  D20 = 20, // P1.00 (MOSI1)
  D21 = 21, // P0.22
};

// three free pins on top (left to right)
enum
{
  D22 = 22, // P0.07 (SDA1)
  D23 = 23, // P0.12 (SCL1)
  D24 = 24, // P0.26
};


/*
 * Enum for nRF pin numbers for compatibility
 */
enum
{
    P0_06 = D0,
    P0_08 = D1,
    P0_15 = D2,
    P0_17 = D3,
    P0_20 = D4,
    P0_13 = D5,
    P0_24 = D6,
    P0_09 = D7,
    P0_10 = D8,
    P1_06 = D9,
    P1_11 = D10,
    P0_28 = D11,
    P0_03 = D12,
    P0_02 = D13,
    P0_29 = D15,
    P0_31 = D16,
    P0_30 = D17,
    P1_04 = D18,
    P1_02 = D19,
    P1_00 = D20,
    P0_22 = D21,
    P0_07 = D22,
    P0_12 = D23,
    P0_26 = D24,
    P0_04 = PIN_VBAT,
    P1_09 = PIN_EXT_VCC,
    P1_10 = PIN_LED,
};

/*
 * Analog pins
 */
enum
{
    PIN_A0 = 11, // P0.28/AIN4
    PIN_A1 = 12, // P0.03/AIN1
    PIN_A2 = 14, // P0.02/AIN0
    PIN_A3 = 15, // P0.29/AIN5
    PIN_A4 = 16, // P0.31/AIN7
    PIN_A5 = 17, // P0.30/AIN6
};

enum
{
    A0  = PIN_A0,
    A1  = PIN_A1,
    A2  = PIN_A2,
    A3  = PIN_A3,
    A4  = PIN_A4,
    A5  = PIN_A5,
};
#define ADC_RESOLUTION    12

/*
 * Other pins
 */
enum
{
    PIN_NFC1 = 7, // P0.09 (D7)
    PIN_NFC2 = 8, // P0.10 (D8)
};

/*
 * Serial interfaces
 */
// NOTE: THESE MUST REMAIN MACROS. The core enables Serial1 support with
// `#if defined(PIN_SERIAL1_RX) && defined(PIN_SERIAL1_TX)`
// (cores/nRF5/Uart.cpp), and `defined()` only works on preprocessor macros.
#define PIN_SERIAL1_TX       (0) // P0.06 - also D0
#define PIN_SERIAL1_RX       (1) // P0.08 - also D1

/*
 * SPI Interfaces
 */
#define SPI_INTERFACES_COUNT 2

enum
{
    PIN_SPI_SCK = 2,     // P0.15 - D2
    PIN_SPI_MISO = 3,    // P0.17 - D3
    PIN_SPI_MOSI = 4,    // P0.20 - D4
    SS   = 9,            // P1.06 - D9

    MOSI = PIN_SPI_MOSI,
    MISO = PIN_SPI_MISO,
    SCK  = PIN_SPI_SCK,

    PIN_SPI1_SCK = 18,   // P1.04 - D18
    PIN_SPI1_MISO = 19,  // P1.02 - D19
    PIN_SPI1_MOSI = 20,  // P1.00 - D20
};

/*
 * Wire Interfaces
 */
#define WIRE_INTERFACES_COUNT 2

enum
{
    PIN_WIRE_SDA = 5, // P0.13 - D5
    PIN_WIRE_SCL = 6, // P0.24 - D6

    SDA = PIN_WIRE_SDA,
    SCL = PIN_WIRE_SCL,

    PIN_WIRE1_SDA = 22, // P0.07 - D22
    PIN_WIRE1_SCL = 23, // P0.12 - D23
};

#ifdef __cplusplus
}
#endif

/*----------------------------------------------------------------------------
 *        Arduino objects - C++ only
 *----------------------------------------------------------------------------*/

#endif
