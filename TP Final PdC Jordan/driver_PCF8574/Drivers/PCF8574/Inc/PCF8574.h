/*
 * PCF8574.h
 *
 *  Created on: 15 jun. 2022
 *      Author: Win10
 */

#ifndef PCF8574_INC_PCF8574_H_
#define PCF8574_INC_PCF8574_H_

#include "stm32f4xx_hal.h"

/* Command */
#define LCD_CLEARDISPLAY 		0x01
#define LCD_RETURNHOME 			0x02
#define LCD_ENTRYMODESET 		0x04
#define LCD_DISPLAYCONTROL 		0x08
#define LCD_CURSORSHIFT 		0x10
#define LCD_FUNCTIONSET 		0x20
#define LCD_SETCGRAMADDR 		0x40
#define LCD_SETDDRAMADDR 		0x80

/* Entry Mode */
#define LCD_ENTRYRIGHT 			0x00
#define LCD_ENTRYLEFT 			0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

/* Display On/Off */
#define LCD_DISPLAYON 			0x04
#define LCD_DISPLAYOFF 			0x00
#define LCD_CURSORON 			0x02
#define LCD_CURSOROFF 			0x00
#define LCD_BLINKON 			0x01
#define LCD_BLINKOFF 			0x00

/* Cursor Shift */
#define LCD_DISPLAYMOVE 		0x08
#define LCD_CURSORMOVE 			0x00
#define LCD_MOVERIGHT 			0x04
#define LCD_MOVELEFT 			0x00

/* Function Set */
#define LCD_8BITMODE 			0x10
#define LCD_4BITMODE 			0x00
#define LCD_2LINE 				0x08
#define LCD_1LINE 				0x00
#define LCD_5x10DOTS 			0x04
#define LCD_5x8DOTS 			0x00

/* Backlight */
#define LCD_BACKLIGHT 			0x08
#define LCD_NOBACKLIGHT 		0x00

/* Enable Bit */
#define ENABLE 					0x04

/* Read Write Bit */
#define RW 						0x0

/* Register Select Bit */
#define RS 						0x01

/* Device I2C Address */
//#define DEVICE_ADDR     		(0x27 << 1) //Comercial
#define DEVICE_ADDR     		(0x38 << 1) //Simen


#include <stdio.h>
#include <stdlib.h>

//Funciones con implementación de Hardware
void PCF8574_Delay_Init(void);
void PCF8574_Delay_us(uint32_t);
void PCF8574_Delay_ms(uint32_t Delay);
void PCF8574_ExpanderWrite(uint8_t _data, uint8_t dpBacklight);


void PCF8574_Init(uint8_t rows);
void PCF8574_Clear();
void PCF8474_Home();
void PCF8474_NoDisplay();
void PCF8474_Display();
void PCF8574_NoBlink();
void PCF8574_Blink();
void PCF8474_NoCursor();
void PCF8574_Cursor();
void PCF8474_ScrollDisplayLeft();
void PCF8574_ScrollDisplayRight();
void PCF8474_PrintLeft();
void PCF8474_PrintRight();
void PCF8474_LeftToRight();
void PCF8474_RightToLeft();
void PCF8474_ShiftIncrement();
void PCF8474_ShiftDecrement();
void PCF8574_NoBacklight();
void PCF8574_Backlight();
void PCF8474_AutoScroll();
void PCF8474_NoAutoScroll();
void PCF8474_CreateSpecialChar(uint8_t, uint8_t[]);
void PCF8474_PrintSpecialChar(uint8_t);
void PCF8574_SetCursor(uint8_t, uint8_t);
void PCF8474_SetBacklight(uint8_t new_val);
void PCF8474_LoadCustomCharacter(uint8_t char_num, uint8_t *rows);
void PCF8574_PrintStr(const char[]);

#endif /* PCF8574_INC_PCF8574_H_ */
