/*
 * PCF8574.c
 *
 *  Created on: 15 jun. 2022
 *      Author: Win10
 */

#include "PCF8574.h"

//extern I2C_HandleTypeDef hi2c1;

uint8_t dpFunction;
uint8_t dpControl;
uint8_t dpMode;
uint8_t dpRows;
uint8_t dpBacklight;

static void _PCF8574_SendCommand(uint8_t);
static void _PCF8574_SendChar(uint8_t);
static void _PCF8574_Send(uint8_t, uint8_t);
static void _PCF8574_Write4Bits(uint8_t);
static void _PCF8574_PulseEnable(uint8_t);

uint8_t special1[8] = {
        0b00000,
        0b11001,
        0b11011,
        0b00110,
        0b01100,
        0b11011,
        0b10011,
        0b00000
};

uint8_t special2[8] = {
        0b11000,
        0b11000,
        0b00110,
        0b01001,
        0b01000,
        0b01001,
        0b00110,
        0b00000
};



void PCF8574_Clear()
{
  _PCF8574_SendCommand(LCD_CLEARDISPLAY);
  PCF8574_Delay_us(2000);
}

void PCF8474_Home()
{
  _PCF8574_SendCommand(LCD_RETURNHOME);
  PCF8574_Delay_us(2000);
}

void PCF8574_SetCursor(uint8_t col, uint8_t row)
{
  int row_offsets[] = { 0x00, 0x40, 0x14, 0x54 };
  if (row >= dpRows)
  {
    row = dpRows-1;
  }
  _PCF8574_SendCommand(LCD_SETDDRAMADDR | (col + row_offsets[row]));
}

void PCF8474_NoDisplay()
{
  dpControl &= ~LCD_DISPLAYON;
  _PCF8574_SendCommand(LCD_DISPLAYCONTROL | dpControl);
}

void PCF8474_Display()
{
  dpControl |= LCD_DISPLAYON;
  _PCF8574_SendCommand(LCD_DISPLAYCONTROL | dpControl);
}

void PCF8474_NoCursor()
{
  dpControl &= ~LCD_CURSORON;
  _PCF8574_SendCommand(LCD_DISPLAYCONTROL | dpControl);
}

void PCF8574_Cursor()
{
  dpControl |= LCD_CURSORON;
  _PCF8574_SendCommand(LCD_DISPLAYCONTROL | dpControl);
}

void PCF8574_NoBlink()
{
  dpControl &= ~LCD_BLINKON;
  _PCF8574_SendCommand(LCD_DISPLAYCONTROL | dpControl);
}

void PCF8574_Blink()
{
  dpControl |= LCD_BLINKON;
  _PCF8574_SendCommand(LCD_DISPLAYCONTROL | dpControl);
}

void PCF8474_ScrollDisplayLeft(void)
{
  _PCF8574_SendCommand(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT);
}

void PCF8574_ScrollDisplayRight(void)
{
  _PCF8574_SendCommand(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT);
}

void PCF8474_LeftToRight(void)
{
  dpMode |= LCD_ENTRYLEFT;
  _PCF8574_SendCommand(LCD_ENTRYMODESET | dpMode);
}

void PCF8474_RightToLeft(void)
{
  dpMode &= ~LCD_ENTRYLEFT;
  _PCF8574_SendCommand(LCD_ENTRYMODESET | dpMode);
}

void PCF8474_AutoScroll(void)
{
  dpMode |= LCD_ENTRYSHIFTINCREMENT;
  _PCF8574_SendCommand(LCD_ENTRYMODESET | dpMode);
}

void PCF8474_NoAutoScroll(void)
{
  dpMode &= ~LCD_ENTRYSHIFTINCREMENT;
  _PCF8574_SendCommand(LCD_ENTRYMODESET | dpMode);
}

void PCF8474_CreateSpecialChar(uint8_t location, uint8_t charmap[])
{
  location &= 0x7;
  _PCF8574_SendCommand(LCD_SETCGRAMADDR | (location << 3));
  for (int i=0; i<8; i++)
  {
    _PCF8574_SendChar(charmap[i]);
  }
}

void PCF8474_PrintSpecialChar(uint8_t index)
{
  _PCF8574_SendChar(index);
}

void PCF8474_LoadCustomCharacter(uint8_t char_num, uint8_t *rows)
{
	PCF8474_CreateSpecialChar(char_num, rows);
}

void PCF8574_PrintStr(const char c[])
{
  while(*c) _PCF8574_SendChar(*c++);
}

void PCF8474_SetBacklight(uint8_t new_val)
{
  if(new_val) 	PCF8574_Backlight();
  else 			PCF8574_NoBacklight();
}

void PCF8574_NoBacklight(void)
{
  dpBacklight=LCD_NOBACKLIGHT;
  PCF8574_ExpanderWrite(0, dpBacklight);
}

void PCF8574_Backlight(void)
{
  dpBacklight=LCD_BACKLIGHT;
  PCF8574_ExpanderWrite(0, dpBacklight);
}

void PCF8574_Init(uint8_t rows)
{
  dpRows = rows;

  dpBacklight = LCD_BACKLIGHT;

  dpFunction = LCD_4BITMODE | LCD_1LINE | LCD_5x8DOTS;

  if (dpRows > 1)
  {
    dpFunction |= LCD_2LINE;
  }
  else
  {
    dpFunction |= LCD_5x10DOTS;
  }

  /* Wait for initialization */
  PCF8574_Delay_Init();			// hardware
  PCF8574_Delay_ms(50);			// hardware

  PCF8574_ExpanderWrite(dpBacklight, dpBacklight);
  PCF8574_Delay_ms(1000);		// hardware

  /* 4bit Mode */
  _PCF8574_Write4Bits(0x03 << 4);
  PCF8574_Delay_us(4500);		// hardware

  _PCF8574_Write4Bits(0x03 << 4);
  PCF8574_Delay_us(4500);

  _PCF8574_Write4Bits(0x03 << 4);
  PCF8574_Delay_us(4500);

  _PCF8574_Write4Bits(0x02 << 4);
  PCF8574_Delay_us(100);

  /* Display Control */
  _PCF8574_SendCommand(LCD_FUNCTIONSET | dpFunction);

  dpControl = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
  PCF8474_Display();
  PCF8574_Clear();

  /* Display Mode */
  dpMode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
  _PCF8574_SendCommand(LCD_ENTRYMODESET | dpMode);
  PCF8574_Delay_us(4500);

  PCF8474_CreateSpecialChar(0, special1);
  PCF8474_CreateSpecialChar(1, special2);

  PCF8474_Home();
}


//----------Funciones Static-------------//
static void _PCF8574_SendCommand(uint8_t cmd)
{
  _PCF8574_Send(cmd, 0);
}

static void _PCF8574_SendChar(uint8_t ch)
{
  _PCF8574_Send(ch, RS);
}

static void _PCF8574_Send(uint8_t value, uint8_t mode)
{
  uint8_t highnib = value & 0xF0;
  uint8_t lownib = (value<<4) & 0xF0;
  _PCF8574_Write4Bits((highnib)|mode);
  _PCF8574_Write4Bits((lownib)|mode);
}

static void _PCF8574_PulseEnable(uint8_t _data)
{
  PCF8574_ExpanderWrite(_data | ENABLE, dpBacklight);
  PCF8574_Delay_us(20);

  PCF8574_ExpanderWrite(_data & ~ENABLE, dpBacklight);
  PCF8574_Delay_us(20);
}

void _PCF8574_Write4Bits(uint8_t value)
{
	PCF8574_ExpanderWrite(value, dpBacklight);	//Hardware
	_PCF8574_PulseEnable(value);
}





