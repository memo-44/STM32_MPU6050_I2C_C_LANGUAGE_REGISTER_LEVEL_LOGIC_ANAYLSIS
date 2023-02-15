/*
 * MPU6050.h
 *
 *  Created on: 29 Kas 2022
 *      Author: mehme
 */

#ifndef MPU6050_H_
#define MPU6050_H_

#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "stdbool.h"


//*******DEFINE DEVICE ID**********//
#define MPU6050_Id ((uint8_t)0x68)
//*******DEFINE DEVICE ID**********//
#define MPU6050_Device_Adr ((uint8_t)0xD0)
//*******DEFINE DEVICE ID FOR READING and WRITING**********//
#define MPU6050_Device_Adr_R ((uint8_t)0xD1)
#define MPU6050_Device_Adr_W ((uint8_t)0xD0)
//*******DEFINE REGISTER ADDRESS and NAME**********//
#define XA_OFFSET_H        ((uint8_t)0x06)
#define XA_OFFSET_L_TC     ((uint8_t)0x07)
#define YA_OFFSET_H        ((uint8_t)0x08)
#define YA_OFFSET_L_TC     ((uint8_t)0x09)
#define ZA_OFFSET_H        ((uint8_t)0x0A)
#define ZA_OFFSET_L_TC     ((uint8_t)0x0B)
#define SELF_TEST_X        ((uint8_t)0x0D)
#define SELF_TEST_Y        ((uint8_t)0x0E)
#define SELF_TEST_Z        ((uint8_t)0x0F)
#define SELF_TEST_A        ((uint8_t)0x10)
#define XG_OFFSET_H        ((uint8_t)0x13)
#define XG_OFFSET_L        ((uint8_t)0x14)
#define YG_OFFSET_H        ((uint8_t)0x15)
#define YG_OFFSET_L        ((uint8_t)0x16)
#define ZG_OFFSET_H        ((uint8_t)0x17)
#define ZG_OFFSET_L        ((uint8_t)0x18)
#define SMPLRT_DIV         ((uint8_t)0x19)
#define CONFIG 		       ((uint8_t)0x1A)
#define GYRO_CONFIG        ((uint8_t)0x1B)
#define ACCEL_CONFIG       ((uint8_t)0x1C)
#define FIFO_EN		       ((uint8_t)0x23)
#define I2C_MST_CTRL       ((uint8_t)0x24)
#define I2C_SLV0_ADDR      ((uint8_t)0x25)
#define I2C_SLV0_REG       ((uint8_t)0x26)
#define I2C_SLV0_CTRL      ((uint8_t)0x27)
#define I2C_SLV1_ADDR      ((uint8_t)0x28)
#define I2C_SLV1_REG       ((uint8_t)0x29)
#define I2C_SLV1_CTRL      ((uint8_t)0x2A)
#define I2C_SLV2_ADDR      ((uint8_t)0x2B)
#define I2C_SLV2_REG       ((uint8_t)0x2C)
#define I2C_SLV2_CTRL      ((uint8_t)0x2D)
#define I2C_SLV3_ADDR      ((uint8_t)0x2E)
#define I2C_SLV3_REG       ((uint8_t)0x2F)
#define I2C_SLV3_CTRL      ((uint8_t)0x30)
#define I2C_SLV4_ADDR      ((uint8_t)0x31)
#define I2C_SLV4_REG       ((uint8_t)0x32)
#define I2C_SLV4_DO        ((uint8_t)0x33)
#define I2C_SLV4_CTRL      ((uint8_t)0x34)
#define I2C_SLV4_DI        ((uint8_t)0x35)
#define I2C_MST_STATUS     ((uint8_t)0x36)
#define INT_PIN_CFG	       ((uint8_t)0x37)
#define INT_ENABLE	       ((uint8_t)0x38)
#define INT_STATUS	       ((uint8_t)0x3A)
#define ACCEL_XOUT_H       ((uint8_t)0x3B)
#define ACCEL_XOUT_L       ((uint8_t)0x3C)
#define ACCEL_YOUT_H       ((uint8_t)0x3D)
#define ACCEL_YOUT_L       ((uint8_t)0x3E)
#define ACCEL_ZOUT_H       ((uint8_t)0x3F)
#define ACCEL_ZOUT_L       ((uint8_t)0x40)
#define TEMP_OUT_H	       ((uint8_t)0x41)
#define TEMP_OUT_L	       ((uint8_t)0x42)
#define GYRO_XOUT_H	       ((uint8_t)0x43)
#define GYRO_XOUT_L	       ((uint8_t)0x44)
#define GYRO_YOUT_H	       ((uint8_t)0x45)
#define GYRO_YOUT_L	       ((uint8_t)0x46)
#define GYRO_ZOUT_H	       ((uint8_t)0x47)
#define GYRO_ZOUT_L	       ((uint8_t)0x48)
#define EXT_SENS_DATA_00   ((uint8_t)0x49)
#define EXT_SENS_DATA_01   ((uint8_t)0x4A)
#define EXT_SENS_DATA_02   ((uint8_t)0x4B)
#define EXT_SENS_DATA_03   ((uint8_t)0x4C)
#define EXT_SENS_DATA_04   ((uint8_t)0x4D)
#define EXT_SENS_DATA_05   ((uint8_t)0x4E)
#define EXT_SENS_DATA_06   ((uint8_t)0x4F)
#define EXT_SENS_DATA_07   ((uint8_t)0x50)
#define EXT_SENS_DATA_08   ((uint8_t)0x51)
#define EXT_SENS_DATA_09   ((uint8_t)0x52)
#define EXT_SENS_DATA_10   ((uint8_t)0x53)
#define EXT_SENS_DATA_11   ((uint8_t)0x54)
#define EXT_SENS_DATA_12   ((uint8_t)0x55)
#define EXT_SENS_DATA_13   ((uint8_t)0x56)
#define EXT_SENS_DATA_14   ((uint8_t)0x57)
#define EXT_SENS_DATA_15   ((uint8_t)0x58)
#define EXT_SENS_DATA_16   ((uint8_t)0x59)
#define EXT_SENS_DATA_17   ((uint8_t)0x5A)
#define EXT_SENS_DATA_18   ((uint8_t)0x5B)
#define EXT_SENS_DATA_19   ((uint8_t)0x5C)
#define EXT_SENS_DATA_20   ((uint8_t)0x5D)
#define EXT_SENS_DATA_21   ((uint8_t)0x5E)
#define EXT_SENS_DATA_22   ((uint8_t)0x5F)
#define EXT_SENS_DATA_23   ((uint8_t)0x60)
#define I2C_SLV0_DO		   ((uint8_t)0x63)
#define I2C_SLV0_D1		   ((uint8_t)0x64)
#define I2C_SLV0_D2		   ((uint8_t)0x65)
#define I2C_SLV0_D3		   ((uint8_t)0x66)
#define I2C_MST_DELAY_CTRL ((uint8_t)0x67)
#define SIGNAL_PATH_RESET  ((uint8_t)0x68)
#define USER_CTRL          ((uint8_t)0x6A)
#define PWR_MGMT_1	       ((uint8_t)0x6B)
#define PWR_MGMT_2		   ((uint8_t)0x6C)
#define FIFO_COUNTH		   ((uint8_t)0x72)
#define FIFO_COUNTL		   ((uint8_t)0x73)
#define FIFO_R_W		   ((uint8_t)0x74)
#define WHO_AM_I		   ((uint8_t)0x75)


//*******DEFINE GYROSCOPE FULL SCALE RANGES**********//
/*
 |-------------|------------------|
 |    FS_SEL   | Full Scale Range |
 |-------------|------------------|
 |  	0      |       250        |
 |-------------|------------------|
 |		1	   |       500        |
 |-------------|------------------|
 |		2	   |      1000        |
 |-------------|------------------|
 |		3	   |      2000        |
 |-------------|------------------|

 */

#define FS_SEL_250  ((uint8_t)0x00)
#define FS_SEL_500  ((uint8_t)0x01)
#define FS_SEL_1000 ((uint8_t)0x02)
#define FS_SEL_2000 ((uint8_t)0x03)

//*******DEFINE ACCELEROMETER FULL SCALE RANGES**********//
/*
 *
 |-------------|------------------|
 |   AFS_SEL   | Full Scale Range |
 |-------------|------------------|
 |  	0      |       2g         |
 |-------------|------------------|
 |		1	   |       4g         |
 |-------------|------------------|
 |		2	   |       8g         |
 |-------------|------------------|
 |		3	   |      16g         |
 |-------------|------------------|
 *
 */

#define AFS_SEL_2_g  ((uint8_t)0x00)
#define AFS_SEL_4_g  ((uint8_t)0x01)
#define AFS_SEL_8_g  ((uint8_t)0x02)
#define AFS_SEL_16_g ((uint8_t)0x03)


//*******DEFINE EXERNAL FRAME SYNCHRONIZATION**********//
/*
 |-------------|------------------|
 |EXT_SYNC_SET |FSYNC Bit Location|
 |-------------|------------------|
 |  	0      |  Input disabled  |
 |-------------|------------------|
 |		1	   |  TEMP_OUT_L[0]   |
 |-------------|------------------|
 |		2	   |  GYRO_XOUT_L[0]  |
 |-------------|------------------|
 |		3	   |  GYRO_YOUT_L[0]  |
 |-------------|------------------|
 |		4	   |  GYRO_ZOUT_L[0]  |
 |-------------|------------------|
 |		5	   |  ACCEL_XOUT_L[0] |
 |-------------|------------------|
 |		6	   |  ACCEL_YOUT_L[0] |
 |-------------|------------------|
 |		7	   |  ACCEL_ZOUT_L[0] |
 |-------------|------------------|

 *CR->>CONFIG REGISTER
 */
#define CR_Input_disabled  ((uint8_t)0x00)
#define CR_TEMP_OUT_L	   ((uint8_t)0x01)
#define CR_GYRO_XOUT_L	   ((uint8_t)0x02)
#define CR_GYRO_YOUT_L	   ((uint8_t)0x03)
#define CR_GYRO_ZOUT_L	   ((uint8_t)0x04)
#define CR_ACCEL_XOUT_L	   ((uint8_t)0x05)
#define CR_ACCEL_YOUT_L	   ((uint8_t)0x06)
#define CR_ACCEL_ZOUT_L	   ((uint8_t)0x07)

//*******DEFINE DIGITAL LOW PASS FILTER (DLPF)**********//
/*
  |--------|-------------------------|------------------------------------|
  |DLPG_CFG|       Accelerometer     |             GYROSCOPE              |
  |	       |        (Fs=1kHz)	     |                                    |
  |	       |-------------------------|------------------------------------|
  |	       |BANDWITH(Hz) | DELAY(ms) | BANDWITH(Hz) | DELAY(ms) | Fs (kHz)|
  |--------|-------------|-----------|--------------|-----------|---------|
  |	  0    |    260      |     0     |     256      |   0.98    |    8    |
  |--------|-------------|-----------|--------------|-----------|---------|
  |	  1    |    184      |     2     |     188      |    1.9    |    1    |
  |--------|-------------|-----------|--------------|-----------|---------|
  |	  2    |     94      |     3     |      98      |    2.8    |    1    |
  |--------|-------------|-----------|--------------|-----------|---------|
  |	  3    |     44      |   4.9     |      42      |    4.8    |    1    |
  |--------|-------------|-----------|--------------|-----------|---------|
  |   4    |     21      |   8.5     |      20      |    8.3    |    1    |
  |--------|-------------|-----------|--------------|-----------|---------|
  |   5    |     10      |  13.8     |      10      |   13.4    |    1    |
  |--------|-------------|-----------|--------------|-----------|---------|
  |	  6    |      5      |    19     |       5      |   18.6    |    1    |
  |--------|-------------|-----------|--------------|-----------|---------|
  |   7    |         RESERVED        |          RESERVED        |    8    |
  |--------|-------------|-----------|--------------|-----------|---------|
 */

#define DLPG_CFG_0 ((uint8_t)0x00)
#define DLPG_CFG_1 ((uint8_t)0x01)
#define DLPG_CFG_2 ((uint8_t)0x02)
#define DLPG_CFG_3 ((uint8_t)0x03)
#define DLPG_CFG_4 ((uint8_t)0x04)
#define DLPG_CFG_5 ((uint8_t)0x05)
#define DLPG_CFG_6 ((uint8_t)0x06)

//*******DEFINE CLOCK SOURCE**********//
/*
 |-------------|----------------------------------------|
 |    CLKSEL   |CLOCK SOURCE                            |
 |-------------|----------------------------------------|
 |  	0      |  INTERNAL 8MHz OSCILLATOR              |
 |-------------|----------------------------------------|
 |		1	   |  PLL with X AXIS GYROSCOPE REFERENCE   |
 |-------------|----------------------------------------|
 |		2	   |  PLL with Y AXIS GYROSCOPE REFERENCE   |
 |-------------|----------------------------------------|
 |		3	   |  PLL with Z AXIS GYROSCOPE REFERENCE   |
 |-------------|----------------------------------------|
 |		4	   |  PLL with EXTERNAL 32.768kHz REFERENCE |
 |-------------|----------------------------------------|
 |		5	   |  PLL with EXTERNAL 19.2MHz REFERENCE   |
 |-------------|----------------------------------------|
 |		6	   |  RESERVED                              |
 |-------------|----------------------------------------|
 |		7	   |  STOP the CLOCK and keeps THE TIMING   |
 |             |  GENERATOR in RESET                    |
 |-------------|----------------------------------------|

*/

#define CLKSEL_0 ((uint8_t)0x00)
#define CLKSEL_1 ((uint8_t)0x01)
#define CLKSEL_2 ((uint8_t)0x02)
#define CLKSEL_3 ((uint8_t)0x03)
#define CLKSEL_4 ((uint8_t)0x04)
#define CLKSEL_5 ((uint8_t)0x05)
#define CLKSEL_6 ((uint8_t)0x06)
#define CLKSEL_7 ((uint8_t)0x07)


				//*******STRUCT OF MPU6050 REGISTERS**********//

//********STRUCT OF BITS and UNION BITS and VALUE
typedef struct{
	uint8_t bit0:1;
	uint8_t bit1:1;
	uint8_t bit2:1;
	uint8_t bit3:1;
	uint8_t bit4:1;
	uint8_t bit5:1;
	uint8_t bit6:1;
	uint8_t bit7:1;
}s_byte_t;

typedef union{
	s_byte_t bits;
	uint8_t value;
}u_byte_t;


//*******STRUCT OF SELF_TEST REGISTERS**********//

typedef struct{

	uint8_t XG_TEST:5;
	uint8_t XA_TEST:3;

}s_SELF_TEST_X;

typedef struct{

	uint8_t YG_TEST:5;
	uint8_t YA_TEST:3;

}s_SELF_TEST_Y;

typedef struct{

	uint8_t ZG_TEST:5;
	uint8_t ZA_TEST:3;

}s_SELF_TEST_Z;

typedef struct{

	uint8_t ZA_TEST:2;
	uint8_t YA_TEST:2;
	uint8_t XA_TEST:2;
	uint8_t _reserved:2;

}s_SELF_TEST_A;

//*******STRUCT OF SMPLRT_DIV REGISTER**********//

typedef struct{

	uint8_t SMPLRT_DIVI;

}s_SMPLRT_DIV;

//*******STRUCT OF CONFIG REGISTER**********//

typedef struct{

	uint8_t DLPF_CFG:3;
	uint8_t EXT_SYNC_SET:3;
	uint8_t _reserved:2;

}s_CONFIG;

//*******STRUCT OF GYRO_CONFIG REGISTER**********//

typedef struct{

	uint8_t _reserved:3;
	uint8_t FS_SEL:2;
	uint8_t ZG_ST:1;
	uint8_t YG_ST:1;
	uint8_t XG_ST:1;

}s_GYRO_CONFIG;

//*******STRUCT OF ACCEL_CONFIG REGISTER**********//

typedef struct{

	uint8_t _reserved:3;
	uint8_t AFS_SEL:2;
	uint8_t ZA_ST:1;
	uint8_t YA_ST:1;
	uint8_t XA_ST:1;

}s_ACCEL_CONFIG;

//*******STRUCT OF SIGNAL PATH RESET REGISTER**********//

typedef struct{

	uint8_t TEMP_RESET:1;
	uint8_t ACCEL_RESET:1;
	uint8_t GYRO_RESET:1;
	uint8_t _reserved:5;

}s_SIGNAL_PATH_RESET;

//*******STRUCT OF USER CONTROL REGISTER**********//

typedef struct{

	uint8_t SIG_COND_RESET:1;
	uint8_t I2C_MST_RESET:1;
	uint8_t FIFO_RESET:1;
	uint8_t _reserved:1;
	uint8_t I2C_IF_DIS:1;
	uint8_t I2C_MST_EN:1;
	uint8_t _FIFO_EN:1;

}s_USER_CONTROL;

//*******STRUCT OF POWER MANAGEMENT REGISTERS**********//

typedef struct{

	uint8_t CLKSEL:3;
	uint8_t TEMP_DIS:1;
	uint8_t _reserved:1;
	uint8_t CYCLE:1;
	uint8_t SLEEP:1;
	uint8_t DEVICE_RESET:1;

}s_PWR_MNG_1;


typedef struct{

	uint8_t STBY_ZG:1;
	uint8_t STBY_YG:1;
	uint8_t STBY_XG:1;
	uint8_t STBY_ZA:1;
	uint8_t STBY_YA:1;
	uint8_t STBY_XA:1;
	uint8_t LP_WAKE_CTRL:2;

}s_PWR_MNG_2;


//*******STRUCT OF ACCEL RAW VALUE REGISTERS**********//
typedef struct{

	uint8_t ACCEL_XOUT_RAW_H;
	uint8_t ACCEL_XOUT_RAW_L;
	uint8_t ACCEL_YOUT_RAW_H;
	uint8_t ACCEL_YOUT_RAW_L;
	uint8_t ACCEL_ZOUT_RAW_H;
	uint8_t ACCEL_ZOUT_RAW_L;
	float Accel_Xout;
	float Accel_Yout;
	float Accel_Zout;

}s_ACCEL_OUT;

//*******STRUCT OF TEMPERATURE RAW VALUE REGISTERS**********//

typedef struct{

	uint8_t TEMP_XOUT_RAW_H;
	uint8_t TEMP_XOUT_RAW_L;
	float Temperature_Value;

}s_TEMP_OUT;

//*******STRUCT OF GYRO RAW VALUE REGISTERS**********//

typedef struct{

	uint8_t GYRO_XOUT_RAW_H;
	uint8_t GYRO_XOUT_RAW_L;
	uint8_t GYRO_YOUT_RAW_H;
	uint8_t GYRO_YOUT_RAW_L;
	uint8_t GYRO_ZOUT_RAW_H;
	uint8_t GYRO_ZOUT_RAW_L;
	float GYRO_XOUT;
	float GYRO_YOUT;
	float GYRO_ZOUT;

}s_GYRO_OUT;

typedef struct{

	float Change_FT_STR[6];
	int8_t AccelSelfValue[3];
	int8_t GyroSelfValue[3];
	uint8_t Self_Result;

}s_SELF_TEST_OUT;

typedef struct{

	//STRUCTS CONFIGURATION OF DEVICE
	uint8_t DeviceId;
	s_PWR_MNG_1 PWR_MNG_1_Reg;
	s_PWR_MNG_2 PWR_MNG_2_Reg;
	s_SIGNAL_PATH_RESET SIGNAL_PATH_RESET_Reg;
	s_USER_CONTROL USER_CONTROL_Reg;
	s_SMPLRT_DIV SMPLRT_DIV_Reg;
	s_CONFIG CONFIG_Reg;
	s_GYRO_CONFIG GYRO_CONFIG_Reg;
	s_ACCEL_CONFIG ACCEL_CONFIG_Reg;
	u_byte_t Reg_Bits_Value;

	//READ OF DEVICE DATA
	s_SELF_TEST_OUT Get_Self_Test;
	float Gyroscope_Bias[3],Accelerometer_Bias[3];
	s_ACCEL_OUT Accel_Out_Value;
	s_TEMP_OUT Temp_Out_Value;
	s_GYRO_OUT Gyro_Out_Value;
}s_DEVICE;


void MPU6050_Read(uint8_t Reg_Address,uint8_t *Buffer,uint8_t Size);
void MPU6050_Write(uint8_t Reg_Address,uint8_t Data,uint8_t Size);
void Whoami(uint8_t DeviceIdRegAdr,s_DEVICE *MPU6050);
void Set_Reg_Position_and_Value(s_DEVICE *MPU6050,uint8_t SetRegAdr);
void MPU6050_Id_and_ResetDevice(s_DEVICE *MPU6050);
void Calibration(float *Gyroscope_Bias,float *Accelerometer_Bias);
void MPU6050_Config(s_DEVICE *MPU6050);
void SelfTest(s_DEVICE *MPU6050);
void GyroRead(s_DEVICE *MPU6050);
void AccelRead(s_DEVICE *MPU6050);
void TemperatureRead(s_DEVICE *MPU6050);



#endif /* MPU6050_H_ */


