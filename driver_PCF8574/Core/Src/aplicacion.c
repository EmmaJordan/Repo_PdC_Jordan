/*
 * aplicacion.c
 *
 *  Created on: 16 jun. 2022
 *      Author: Win10
 */

#include "aplicacion.h"

static void _myPCF8574_PrintNumber (uint8_t col, uint8_t row, const char c[])
{
	PCF8574_Clear();
	PCF8574_SetCursor(col,row);
	PCF8574_PrintStr(c);
}

void myPCF8574_Iniciar()
{
	PCF8574_Init(2);
}

void myPCF8574_SaludoInicial()
{
	PCF8574_Clear();
	PCF8574_SetCursor(0,0);
	PCF8574_PrintStr(" Protocolos  de ");
	PCF8574_SetCursor(0,1);
	PCF8574_PrintStr("  Comunicacion  ");
	PCF8574_Delay_ms(1500);
	PCF8574_Clear();
	PCF8574_SetCursor(0,0);
	PCF8574_PrintStr("  en Sistemas   ");
	PCF8574_SetCursor(0,1);
	PCF8574_PrintStr("   Embebidos    ");
	PCF8574_Delay_ms(1500);
	PCF8574_Clear();
	PCF8574_SetCursor(0,0);
	PCF8574_PrintStr(" Driver PCF8574 ");
	PCF8574_SetCursor(0,1);
	PCF8574_PrintStr("    LCD-I2C     ");
	PCF8574_Delay_ms(1500);
}

void myPCF8574_BackLight()
{
	PCF8574_Clear();
	PCF8574_Delay_ms(300);
	PCF8574_SetCursor(0,0);
	PCF8574_PrintStr("Back Light ON");
	PCF8574_Delay_ms(1000);
	PCF8574_SetCursor(0,0);
	PCF8574_PrintStr("Back Light OFF");
	PCF8574_Delay_ms(500);
	PCF8574_NoBacklight();
	PCF8574_Clear();
	PCF8574_Delay_ms(1000);
	PCF8574_Backlight();
	PCF8574_Delay_ms(500);
}

void myPCF8574_Cursor()
{
	PCF8574_Clear();
	PCF8574_Delay_ms(300);
	PCF8574_SetCursor(0,0);
	PCF8574_PrintStr("Cursor Fijo");
	PCF8574_Cursor();
	PCF8574_NoBlink();
	PCF8574_Delay_ms(1300);
	PCF8574_SetCursor(0,0);
	PCF8574_PrintStr("Cursor Blink");
	for(uint8_t i=0; i<4; i++)
	{
		PCF8574_Blink();
		PCF8574_Delay_ms(700);
	}
	PCF8574_Clear();
	PCF8574_SetCursor(0,0);
	PCF8574_NoBlink();
	PCF8474_NoCursor();
	PCF8574_Clear();
	PCF8574_Delay_ms(300);
}

void myPCF8574_CorrimientoIzquierda()
{
	PCF8574_SetCursor(0,0);
	PCF8574_PrintStr("Corre Izquierda");
	PCF8574_Delay_ms(500);
	for(int x=0; x<15; x++)
	{
		PCF8474_ScrollDisplayLeft();
		PCF8574_Delay_ms(250);
	}
	PCF8574_Clear();
	PCF8574_Delay_ms(300);
}

void myPCF8574_CorrimientoDerecha()
{
	PCF8574_SetCursor(0,0);
	PCF8574_PrintStr("Corre Derecha");
	PCF8574_Delay_ms(500);
	for(int x=0; x<13; x++)
	{
		PCF8574_ScrollDisplayRight();
		PCF8574_Delay_ms(250);
	}
	PCF8574_Clear();
	PCF8574_Delay_ms(300);
}

void myPCF8574_ImprimeNumero()
{
	char snum[5];
	for(int16_t x=0; x<6; x++)
	{
		itoa(x, snum, 10);
		_myPCF8574_PrintNumber(5,0,snum);
		PCF8574_Delay_ms (500);
	}
	for(int16_t x=6; x<11; x++)
	{
		itoa(x, snum, 10);
		_myPCF8574_PrintNumber(5,1,snum);
		PCF8574_Delay_ms (500);
	}
	for(int16_t x=11; x<16; x++)
	{
		itoa(x, snum, 10);
		_myPCF8574_PrintNumber(10,0,snum);
		PCF8574_Delay_ms (500);
	}
	for(int16_t x=16; x<21; x++)
	{
		itoa(x, snum, 10);
		_myPCF8574_PrintNumber(10,1,snum);
		PCF8574_Delay_ms (500);
	}
}
