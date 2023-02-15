/*
 * TimerConfig.h
 *
 *  Created on: 12 Ara 2022
 *      Author: mehme
 */

#ifndef TIMERCONFIG_H_
#define TIMERCONFIG_H_
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

void Timer7Config();
void Delay_ms(uint16_t ms);
void Delay_us(uint16_t us);

#endif /* TIMERCONFIG_H_ */
