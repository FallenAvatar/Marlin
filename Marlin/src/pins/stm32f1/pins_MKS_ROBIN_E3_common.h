/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2020 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */
#pragma once

/**
 * MKS Robin E3 & E3D (STM32F103RCT6) common board pin assignments
 */

#include "env_validate.h"

#define BOARD_NO_NATIVE_USB

#define BOARD_WEBSITE_URL "github.com/makerbase-mks"

//#define DISABLE_DEBUG
#define DISABLE_JTAG

//
// EEPROM
//
#if EITHER(NO_EEPROM_SELECTED, FLASH_EEPROM_EMULATION)
  #define FLASH_EEPROM_EMULATION
  #define EEPROM_PAGE_SIZE     (0x800U)           // 2KB
  #define EEPROM_START_ADDRESS (0x8000000UL + (STM32_FLASH_SIZE) * 1024UL - (EEPROM_PAGE_SIZE) * 2UL)
  #define MARLIN_EEPROM_SIZE    EEPROM_PAGE_SIZE  // 2KB
#endif

//
// Servos
//
#define SERVO0_PIN                          PA3

//
// Limit Switches
//
#define X_STOP_PIN                          PA12
#define Y_STOP_PIN                          PA11
#define Z_MIN_PIN                           PC6
#define Z_MAX_PIN                           PB1

//
// Steppers
//
#define X_STEP_PIN                          PC0
#define X_DIR_PIN                           PB2
#define X_ENABLE_PIN                        PC13

#define Y_STEP_PIN                          PC2
#define Y_DIR_PIN                           PB9
#define Y_ENABLE_PIN                        PB12

#ifndef Z_STEP_PIN
  #define Z_STEP_PIN                        PB7
#endif
#ifndef Z_DIR_PIN
  #define Z_DIR_PIN                         PB6
#endif
#define Z_ENABLE_PIN                        PB8

#define E0_STEP_PIN                         PB4
#define E0_DIR_PIN                          PB3
#define E0_ENABLE_PIN                       PB5

#if HAS_TMC_UART
  /**
   * TMC2208/TMC2209 stepper drivers
   *
   * Hardware serial communication ports.
   * If undefined software serial is used according to the pins below
   */
  //#define X_HARDWARE_SERIAL  MSerial1
  //#define Y_HARDWARE_SERIAL  MSerial1
  //#define Z_HARDWARE_SERIAL  MSerial1
  //#define E0_HARDWARE_SERIAL MSerial1

  #define X_SERIAL_TX_PIN                   PC7
  #define X_SERIAL_RX_PIN                   PC7

  #define Y_SERIAL_TX_PIN                   PD2
  #define Y_SERIAL_RX_PIN                   PD2

  #define Z_SERIAL_TX_PIN                   PC12
  #define Z_SERIAL_RX_PIN                   PC12

  #define E0_SERIAL_TX_PIN                  PC11
  #define E0_SERIAL_RX_PIN                  PC11

  // Reduce baud rate to improve software serial reliability
  #define TMC_BAUD_RATE                    19200
#endif

//
// Heaters 0,1 / Fans / Bed
//
#define HEATER_0_PIN                        PC9
#define FAN_PIN                             PA8
#define HEATER_BED_PIN                      PC8

//
// Temperature Sensors
//
#define TEMP_BED_PIN                        PA1   // TB
#define TEMP_0_PIN                          PA0   // TH1

#define FIL_RUNOUT_PIN                      PB10  // MT_DET

//
// Power Supply Control
//
#if ENABLED(MKS_PWC)
  #define PS_ON_PIN                         PA14  // PW_OFF
  #define KILL_PIN                          PB10  // PW_DET
  #define KILL_PIN_STATE                    HIGH
#endif

/**
 *                _____                                      _____                                     _____
 *  (BEEPER) PC1 | 1 2 | PC3 (BTN_ENC)          (MISO) PB14 | 1 2 | PB13 (SD_SCK)                  5V | 1 2 | GND
 *  (LCD_EN) PA4 | 3 4 | PA5 (LCD_RS)        (BTN_EN1) PB11 | 3 4 | PA15 (SD_SS)         (LCD_EN) PA4 | 3 4 | PA5  (LCD_RS)
 *  (LCD_D4) PA6 | 5 6   PA7 (LCD_D5)        (BTN_EN2)  PB0 | 5 6   PB15 (SD_MOSI)       (LCD_D4) PA6 | 5 6   PB0  (BTN_EN2)
 *  (LCD_D6) PC4 | 7 8 | PC5 (LCD_D7)      (SD_DETECT) PC10 | 7 8 | RESET                       RESET | 7 8 | PB11 (BTN_EN1)
 *           GND | 9 10| 5V                             GND | 9 10| NC                  (BTN_ENC) PC3 | 9 10| PC1  (BEEPER)
 *                -----                                      -----                                     -----
 *                EXP1                                       EXP2                                      EXP3
 */
#if HAS_WIRED_LCD

  #define BEEPER_PIN                        PC1
  #define BTN_ENC                           PC3
  #define LCD_PINS_ENABLE                   PA4
  #define LCD_PINS_RS                       PA5
  #define BTN_EN1                           PB11
  #define BTN_EN2                           PB0

  // MKS MINI12864 and MKS LCD12864B; If using MKS LCD12864A (Need to remove RPK2 resistor)
  #if ENABLED(MKS_MINI_12864)

    #define LCD_BACKLIGHT_PIN               -1
    #define LCD_RESET_PIN                   -1
    #define DOGLCD_A0                       PC4
    #define DOGLCD_CS                       PA7
    #define DOGLCD_SCK                      PB13
    #define DOGLCD_MOSI                     PB15

  #elif ENABLED(MKS_MINI_12864_V3)
    #define DOGLCD_CS                       PA4
    #define DOGLCD_A0                       PA5
    #define LCD_PINS_DC                DOGLCD_A0
    #define LCD_BACKLIGHT_PIN               -1
    #define LCD_RESET_PIN                   PA6
    #define NEOPIXEL_PIN                    PA7
    #define DOGLCD_MOSI                     PB15
    #define DOGLCD_SCK                      PB13
    #define FORCE_SOFT_SPI
    #define SOFTWARE_SPI
	//#define LCD_SCREEN_ROT_180

  #else

    #define LCD_PINS_D4                     PA6
    #if IS_ULTIPANEL
      #define LCD_PINS_D5                   PA7
      #define LCD_PINS_D6                   PC4
      #define LCD_PINS_D7                   PC5

      #if !defined(BTN_ENC_EN) && ENABLED(REPRAP_DISCOUNT_FULL_GRAPHIC_SMART_CONTROLLER)
        #define BTN_ENC_EN           LCD_PINS_D7  // Detect the presence of the encoder
      #endif

    #endif

  #endif // !MKS_MINI_12864

#endif // HAS_WIRED_LCD

//
// SD Card
//
#define SPI_DEVICE                             2
#define ONBOARD_SPI_DEVICE                     2
#define SDSS                           SD_SS_PIN
#define SDCARD_CONNECTION                ONBOARD
#define SD_DETECT_PIN                       PC10
#define ONBOARD_SD_CS_PIN              SD_SS_PIN
#define NO_SD_HOST_DRIVE

// TODO: This is the only way to set SPI for SD on STM32 (for now)
#define ENABLE_SPI2
#define SD_SCK_PIN                          PB13
#define SD_MISO_PIN                         PB14
#define SD_MOSI_PIN                         PB15
#define SD_SS_PIN                           PA15

#ifndef BOARD_ST7920_DELAY_1
  #define BOARD_ST7920_DELAY_1     DELAY_NS(125)
#endif
#ifndef BOARD_ST7920_DELAY_2
  #define BOARD_ST7920_DELAY_2     DELAY_NS(125)
#endif
#ifndef BOARD_ST7920_DELAY_3
  #define BOARD_ST7920_DELAY_3     DELAY_NS(125)
#endif
