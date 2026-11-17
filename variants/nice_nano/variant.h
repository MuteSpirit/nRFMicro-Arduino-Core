#ifndef _NICE_NANO_V2_H_
#define _NICE_NANO_V2_H_

#define TARGET_NICE_NANO_V2

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
    PINS_COUNT = 23,
    NUM_DIGITAL_PINS = 23,
    NUM_ANALOG_INPUTS = 3,
    NUM_ANALOG_OUTPUTS = 0,
};
// NOTE:
//
// BATTERY VOLTAGE IS READ VIA VDDH/5 BY CALLING
//
// analogReadVDDHDIV5() // returns uint32_t

enum
{
    // 3V3 Regulator Disable
    PIN_EXT_VCC = 21, // EXT_VCC is P0.13 (set low to disable 3v3)
    EXT_VCC = PIN_EXT_VCC,

    // LEDs
    PIN_LED = 22, // USR LED is P0.15
    LED_PWR = PINS_COUNT, // no LED_PWR
    PIN_NEOPIXEL = PINS_COUNT, // no neopixel
    NEOPIXEL_NUM = 0,
    LED_BLUE     = PIN_LED, // required by bluefruit library

    LED_BUILTIN  = PIN_LED,

    LED_STATE_ON = 1,         // State when LED is on
};

/*
 * Buttons
 */
#define PIN_BUTTON1          (PINS_COUNT) // no button

// Digital PINs
// NOTE: THIS IS A RENUMBERING OF THE PINS
// AND DOES NOT CORRESPOND TO THE NICENANO DIAGRAM

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
  D3  = 3,  // P0.20 (MISO)
  D4  = 4,  // P0.22 (MOSI)
  D5  = 5,  // P0.24 (CS)
  D6  = 6,  // P1.00 (SDA)
  D7  = 7,  // P0.11 (SCL)
  D8  = 8,  // P1.04
  D9  = 9,  // P1.06
};

// right side (bottom to top)
enum
{
  D10 = 10, // P0.09 (NFC1)
  D11 = 11, // P0.10 (NFC2)
  D12 = 12, // P1.11
  D13 = 13, // P1.13 (SDA1)
  D14 = 14, // P1.15 (SCL1)
  D15 = 15, // P0.02/AIN0 (A0)
  D16 = 16, // P0.29/AIN6 (A1)
  D17 = 17, // P0.31/AIN7 (A2)
};

// extra center pins (left to right)
enum
{
  D18 = 18, // P1.01 (SCK1)
  D19 = 19, // P1.02 (MISO1)
  D20 = 20, // P1.07 (MOSI1)
};

/*
 * Enum for nRF pin numbers for compatibility
 */
enum
{
    P0_06 = D0,
    P0_08 = D1,
    P0_17 = D2,
    P0_20 = D3,
    P0_22 = D4,
    P0_24 = D5,
    P1_00 = D6,
    P0_11 = D7,
    P1_04 = D8,
    P1_06 = D9,
    P0_09 = D10,
    P0_10 = D11,
    P1_11 = D12,
    P1_13 = D13,
    P1_15 = D14,
    P0_02 = D15,
    P0_29 = D16,
    P0_31 = D17,
    P1_01 = D18,
    P1_02 = D19,
    P1_07 = D20,
    P0_13 = EXT_VCC,
    P0_15 = PIN_LED,
};

/*
 * Analog pins
 */
enum
{
    PIN_A0 = 15, // P0.02 (D15)
    PIN_A1 = 16, // P0.29 (D16)
    PIN_A2 = 17, // P0.31 (D17)
};

enum
{
    A0  = PIN_A0,
    A1  = PIN_A1,
    A2  = PIN_A2,
};

#define ADC_RESOLUTION    12

/*
 * Other pins
 */
enum
{
    PIN_NFC1 = 10, // P0.09 - also D10
    PIN_NFC2 = 11, // P0.10 - also D11
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
    PIN_SPI_SCK = 2,     // P0.17 - D2
    PIN_SPI_MISO = 3,    // P0.20 - D3
    PIN_SPI_MOSI = 4,    // P0.22 - D4
    SS   = 5,            // P0.24 - D5

    MOSI = PIN_SPI_MOSI,
    MISO = PIN_SPI_MISO,
    SCK  = PIN_SPI_SCK,

    PIN_SPI1_SCK = 18,   // P1.01 - D18
    PIN_SPI1_MISO = 19,  // P1.02 - D19
    PIN_SPI1_MOSI = 20,  // P1.07 - D20
};

/*
 * Wire Interfaces
 */
#define WIRE_INTERFACES_COUNT 2

enum
{
    PIN_WIRE_SDA = 6, // P1.00 - D6
    PIN_WIRE_SCL = 7, // P0.11 - D7

    SDA = PIN_WIRE_SDA,
    SCL = PIN_WIRE_SCL,

    PIN_WIRE1_SDA = 13, // P1.13 - D13
    PIN_WIRE1_SCL = 14, // P1.15 - D14
};

#ifdef __cplusplus
}
#endif

/*----------------------------------------------------------------------------
 *        Arduino objects - C++ only
 *----------------------------------------------------------------------------*/

#endif
