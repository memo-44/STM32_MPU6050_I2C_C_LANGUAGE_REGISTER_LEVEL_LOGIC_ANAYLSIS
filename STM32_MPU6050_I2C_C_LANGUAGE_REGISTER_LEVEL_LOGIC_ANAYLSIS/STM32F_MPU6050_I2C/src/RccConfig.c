/*
 * RccConfig.c
 *
 *  Created on: 8 Ara 2022
 *      Author: mehme
 */

#include "RccConfig.h"

void RccConfig(){


	RCC->CR |=(1<<16); //HSE ENABLE
	while(!(RCC->CR & (1<<17)));//CHECK HSE READY

	RCC->APB1ENR |=(1<<28);//INTERFACE POWER ENABLE
	PWR->CR |=(3<<14);     //SET SCALE 1 MODE for MAIN VOLTAGE REGULATOR OUTPUT VOLTAGE

	RCC->CFGR &=~(1<<4); //AHB1 CLOCK BUS LINE NOT DIVIDED
	RCC->CFGR |=(5<<10); //APB1 CLOCK BUS LINE DIVIDED BY FOUR
	RCC->CFGR |=(4<<13); //APB2 CLOCK BUS KINE DIVEDED BY TWO

	RCC->PLLCFGR =0; //RESET RCC_PLLCFGR REGISTER
	RCC->PLLCFGR |=(4<<0);    //SET PLL M VALUE
	RCC->PLLCFGR |=(168<<6);  //SET PLL N VALUE
	RCC->PLLCFGR &=~(1<<16);  //SET PLL P VALUE
	RCC->PLLCFGR |=(4<<24);   //SET PLL Q VALUE
	RCC->PLLCFGR |=(1<<22);	  //PLL CLOCK SOURCE SELECTED AS HSE

	RCC->CR |=(1<<24); //PLL ENABLE
	while(!(RCC->CR & (1<<25))); //CHECK PLL READY


	FLASH->ACR |=(1<<9);   //INSTRUCTION CACHE ENABLE
	FLASH->ACR |=(1<<10);  //DATA CACHE ENABLE
	FLASH->ACR |=(5<<0);   //These bits represent the ratio of the CPU clock period to the
						   //Flash memory access time.


	RCC->CFGR &=(uint32_t)((uint32_t)~(0x00000003));
	RCC->CFGR |=(2<<0);    //PLL SOURCE SWÝTCHED SYSTEM CLOCK
	while (!(RCC->CFGR & (2<<2)));

	SystemCoreClockUpdate();

	RCC->CIR |= 0x00800000;					// CSS Flag clear

}
