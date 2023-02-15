/*
 * GpioConfig.c
 *
 *  Created on: 8 Ara 2022
 *      Author: mehme
 */


#include "GpioConfig.h"

void GpioConfig(){

	RCC->AHB1ENR |= (1<<1);//ENABLE CLOCK BUS LINE OF GPIOB


	// Configure the I2C PINs for ALternate Functions
	GPIOB->MODER   |=(2<<16)|(2<<18);  //8.(SCL) and 9.(SDA) PINS OF GPIOB SET ALTERNATIVE FUNCTION MODE
	GPIOB->OTYPER  |=(1<<8)|(1<<9);    //8. and 9. PINS OF GPIOB SET OUTPUT OPEN DRAIN
	GPIOB->OSPEEDR |=(3<<16)|(3<<18);  //8. and 9. PINS OF GPIOB SET HIGH SPEED
	GPIOB->PUPDR |= (1<<16) | (1<<18); //8. and 9. PINS OF GPIOB SELECTED AS PULL UP
	GPIOB->AFR[1] |= (4<<0) | (4<<4);  //ALTERNATIVE FUNTION SELECTED AS I2C


	RCC->AHB1ENR |=(1<<3);//ENABLE CLOCK BUS LINE OF GPIOD
	GPIOD->MODER |=(1<<30)|(1<<28)|(1<<26)|(1<<24);//15,14.13 and 12 PINS OF GPIOD SET OUTPUT MODE

	GPIOD->OTYPER &=~(1<<12);//15.,14.,13. and 12. PINS OF GPIOD SET Output push-pull
	GPIOD->OTYPER &=~(1<<13);
	GPIOD->OTYPER &=~(1<<14);
	GPIOD->OTYPER &=~(1<<15);

	GPIOD->OSPEEDR |=(2<<30)|(2<<28)|(2<<26)|(2<<24);//15,14.13 and 12 PINS OF GPIOD SET HIGH SPEED

	GPIOD->PUPDR &=~(1<<30);//15.,14.,13. and 12. PINS OF GPIOD SELECTED AS NO PULL UP-PULL DOWN
	GPIOD->PUPDR &=~(1<<28);
	GPIOD->PUPDR &=~(1<<26);
	GPIOD->PUPDR &=~(1<<24);

}
