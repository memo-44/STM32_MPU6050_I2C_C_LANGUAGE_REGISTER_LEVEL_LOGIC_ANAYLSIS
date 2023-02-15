#include "RccConfig.h"
#include "GpioConfig.h"
#include "i2cConfig.h"
#include "MPU6050.h"
#include "TimerConfig.h"


int main(void)
{
	RccConfig();
	GpioConfig();
	Timer7Config();
	i2cConfig();
	s_DEVICE Dev_Mpu6050={0};
	MPU6050_Id_and_ResetDevice(&Dev_Mpu6050);
	SelfTest(&Dev_Mpu6050);
	Calibration(&Dev_Mpu6050.Gyroscope_Bias[0],&Dev_Mpu6050.Accelerometer_Bias[0]);
	MPU6050_Config(&Dev_Mpu6050);
	AccelRead(&Dev_Mpu6050);
	GyroRead(&Dev_Mpu6050);
	TemperatureRead(&Dev_Mpu6050);


  while (1)
  {
	  //CHECK PROGRAM LOOP COMPLETED OR NOT
	  GPIOD->BSRRL |=(1<<12);
	  Delay_ms(1000);
	  GPIOD->BSRRH |=(1<<12);
	  Delay_ms(1000);
  }
}


