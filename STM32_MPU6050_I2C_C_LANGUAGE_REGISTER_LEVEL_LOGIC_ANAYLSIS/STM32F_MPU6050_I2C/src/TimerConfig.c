/*
 * TimerConfig.c
 *
 *  Created on: 12 Ara 2022
 *      Author: mehme
 */


#include "TimerConfig.h"

void Timer7Config(void){


	RCC->APB1ENR |=(1<<5);       //TIMER7 clock bus enable

	TIM7->PSC =41;               //42MHZ/41+1 = 1us -->> errorrr
	TIM7->ARR=0XFFFF;            //MAX ARR VALUE
	TIM7->CR1 |=(1<<0);          //TIMER7 ENABLE
	while(!(TIM7->SR &(1<<0)));	 //TO CHECK TIMER7 EVENT FLAG

}

void Delay_us(uint16_t us){

	TIM7->CNT=0x0000;
	while(TIM7->CNT<us);
}
void Delay_ms(uint16_t ms){


	for(int i=0;i<=ms;i++){

		Delay_us(1000);

	}
}

