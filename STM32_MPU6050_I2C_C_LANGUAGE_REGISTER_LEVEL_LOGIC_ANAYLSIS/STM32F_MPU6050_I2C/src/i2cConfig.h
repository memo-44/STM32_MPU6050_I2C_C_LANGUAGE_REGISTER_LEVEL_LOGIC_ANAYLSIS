/*
 * i2cConfig.h
 *
 *  Created on: 8 Ara 2022
 *      Author: mehme
 */

#ifndef I2CCONFIG_H_
#define I2CCONFIG_H_

#include "stm32f4xx.h"
#include "stm32f4_discovery.h"


void i2cConfig();
void i2cStart();
void i2cStop();
void i2cDeviceAdrTrans(uint8_t Adr);
void i2cRegAdrTrans(uint8_t Reg);
void i2cDataTrans(uint8_t *Data,uint8_t Size);
void i2cDataReceive(uint8_t Address,uint8_t *Buffer,uint8_t Size);

#endif /* I2CCONFIG_H_ */
