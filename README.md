# Protocolos de Comunicación en Sistemas Embebidos
Repositorio de la materia Protocolos de Comunicación en Sistemas Embebidos
Carrera de Especialización en Sistemas Embebidos
FIUBA
Año 2022

Se implementa un Driver del tipo genérico, para manejo de Display alfanumérico 16x2. 
Se utiliza el protocolo I2C para comunicarse desde la placa Nucleo144 (con STM32F429ZI) 
con el integrado PCF8574, el cual actúa como conversor I2C/paralelo para controlar el Display.
Se implementará una estructura de capas, siendo la capa más alta la aplicación, la capa intermedia 
el Driver y la capa más baja el hardware.

Autor: Joan Emmanuel Jordán