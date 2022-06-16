/*
 * aplicacion.h
 *
 *  Created on: 16 jun. 2022
 *      Author: Win10
 */

#ifndef INC_APLICACION_H_
#define INC_APLICACION_H_

#include "PCF8574.h"

#include <stdio.h>
#include <stdlib.h>

void myPCF8574_Iniciar();
void myPCF8574_SaludoInicial();
void myPCF8574_BackLight();
void myPCF8574_Cursor();
void myPCF8574_CorrimientoIzquierda();
void myPCF8574_CorrimientoDerecha();
void myPCF8574_ImprimeNumero();


#endif /* INC_APLICACION_H_ */
