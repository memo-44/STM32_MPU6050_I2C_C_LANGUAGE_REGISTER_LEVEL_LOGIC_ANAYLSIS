

#include "MPU6050.h"
#include "i2cConfig.h"
#include "TimerConfig.h"
#include "stdlib.h"
#include "math.h"

void MPU6050_Write(uint8_t Reg_Address,uint8_t Data,uint8_t Size){

	i2cStart();
	i2cDeviceAdrTrans(MPU6050_Device_Adr_W);
	i2cRegAdrTrans(Reg_Address);
	i2cDataTrans(&Data,Size);
	i2cStop();
}

void MPU6050_Read(uint8_t Reg_Address,uint8_t *Buffer,uint8_t Size){

	i2cStart();
	i2cDeviceAdrTrans(MPU6050_Device_Adr);
	i2cRegAdrTrans(Reg_Address);
	i2cStart();
	i2cDataReceive(MPU6050_Device_Adr_R,Buffer,Size);

}

void Whoami(uint8_t DeviceIdRegAdr,s_DEVICE *MPU6050){

	uint8_t Buffer;
	MPU6050_Read(DeviceIdRegAdr,&Buffer,1);
	if(MPU6050_Id==Buffer){
		MPU6050->DeviceId=Buffer;
		/**********RESET DEVICE**************/
		MPU6050->PWR_MNG_1_Reg.DEVICE_RESET=1;
		Set_Reg_Position_and_Value(MPU6050,PWR_MGMT_1);
		MPU6050_Write(PWR_MGMT_1,MPU6050->Reg_Bits_Value.value,1);
		Delay_ms(125);

		/**********RESET ALL SIGNAL PATH**************/
		MPU6050->SIGNAL_PATH_RESET_Reg.TEMP_RESET=1;
		MPU6050->SIGNAL_PATH_RESET_Reg.ACCEL_RESET=1;
		MPU6050->SIGNAL_PATH_RESET_Reg.GYRO_RESET=1;
		Set_Reg_Position_and_Value(MPU6050,SIGNAL_PATH_RESET);
		MPU6050_Write(SIGNAL_PATH_RESET,MPU6050->Reg_Bits_Value.value,1);
		Delay_ms(125);

	}
	else{
		//write error such as not take device id
	}

}

void Set_Reg_Position_and_Value(s_DEVICE *MPU6050,uint8_t SetRegAdr){

	MPU6050->Reg_Bits_Value.value=0;
	if(PWR_MGMT_1==SetRegAdr){

		MPU6050->Reg_Bits_Value.value |=MPU6050->PWR_MNG_1_Reg.CLKSEL;
		MPU6050->Reg_Bits_Value.value |=(MPU6050->PWR_MNG_1_Reg.TEMP_DIS<<3);
		MPU6050->Reg_Bits_Value.value |=(MPU6050->PWR_MNG_1_Reg.CYCLE<<5);
		MPU6050->Reg_Bits_Value.value |=(MPU6050->PWR_MNG_1_Reg.SLEEP<<6);
		MPU6050->Reg_Bits_Value.value |=(MPU6050->PWR_MNG_1_Reg.DEVICE_RESET<<7);

	}
	if(SIGNAL_PATH_RESET==SetRegAdr){

		MPU6050->Reg_Bits_Value.value |=MPU6050->SIGNAL_PATH_RESET_Reg.TEMP_RESET;
		MPU6050->Reg_Bits_Value.value |=(MPU6050->SIGNAL_PATH_RESET_Reg.ACCEL_RESET<<1);
		MPU6050->Reg_Bits_Value.value |=(MPU6050->SIGNAL_PATH_RESET_Reg.GYRO_RESET<<2);

	}
	if(PWR_MGMT_2==SetRegAdr){

		MPU6050->Reg_Bits_Value.value |=MPU6050->PWR_MNG_2_Reg.STBY_ZG;
		MPU6050->Reg_Bits_Value.value |=(MPU6050->PWR_MNG_2_Reg.STBY_YG<<1);
		MPU6050->Reg_Bits_Value.value |=(MPU6050->PWR_MNG_2_Reg.STBY_XG<<2);
		MPU6050->Reg_Bits_Value.value |=(MPU6050->PWR_MNG_2_Reg.STBY_ZA<<3);
		MPU6050->Reg_Bits_Value.value |=(MPU6050->PWR_MNG_2_Reg.STBY_YA<<4);
		MPU6050->Reg_Bits_Value.value |=(MPU6050->PWR_MNG_2_Reg.STBY_XA<<5);
		MPU6050->Reg_Bits_Value.value |=(MPU6050->PWR_MNG_2_Reg.LP_WAKE_CTRL<<6);
	}

	if(USER_CTRL==SetRegAdr){

		MPU6050->Reg_Bits_Value.value |=MPU6050->USER_CONTROL_Reg.SIG_COND_RESET;
		MPU6050->Reg_Bits_Value.value |=(MPU6050->USER_CONTROL_Reg.I2C_MST_RESET<<1);
		MPU6050->Reg_Bits_Value.value |=(MPU6050->USER_CONTROL_Reg.FIFO_RESET<<2);
		MPU6050->Reg_Bits_Value.value |=(MPU6050->USER_CONTROL_Reg.I2C_IF_DIS<<4);
		MPU6050->Reg_Bits_Value.value |=(MPU6050->USER_CONTROL_Reg.I2C_MST_EN<<5);
		MPU6050->Reg_Bits_Value.value |=(MPU6050->USER_CONTROL_Reg._FIFO_EN<<6);
	}

	if(SMPLRT_DIV==SetRegAdr){

		MPU6050->Reg_Bits_Value.value |=MPU6050->SMPLRT_DIV_Reg.SMPLRT_DIVI;

	}

	if(CONFIG==SetRegAdr){

		MPU6050->Reg_Bits_Value.value |=MPU6050->CONFIG_Reg.DLPF_CFG;
		MPU6050->Reg_Bits_Value.value |=(MPU6050->CONFIG_Reg.EXT_SYNC_SET<<3);
	}

	if(GYRO_CONFIG==SetRegAdr){

		MPU6050->Reg_Bits_Value.value |=(MPU6050->GYRO_CONFIG_Reg.FS_SEL<<3);
		MPU6050->Reg_Bits_Value.value |=(MPU6050->GYRO_CONFIG_Reg.ZG_ST<<5);
		MPU6050->Reg_Bits_Value.value |=(MPU6050->GYRO_CONFIG_Reg.YG_ST<<6);
		MPU6050->Reg_Bits_Value.value |=(MPU6050->GYRO_CONFIG_Reg.XG_ST<<7);

	}

	if(ACCEL_CONFIG==SetRegAdr){

		MPU6050->Reg_Bits_Value.value |=(MPU6050->ACCEL_CONFIG_Reg.AFS_SEL<<3);
		MPU6050->Reg_Bits_Value.value |=(MPU6050->ACCEL_CONFIG_Reg.ZA_ST<<5);
		MPU6050->Reg_Bits_Value.value |=(MPU6050->ACCEL_CONFIG_Reg.YA_ST<<6);
		MPU6050->Reg_Bits_Value.value |=(MPU6050->ACCEL_CONFIG_Reg.XA_ST<<7);
	}
}

void MPU6050_Id_and_ResetDevice(s_DEVICE *MPU6050){

	Whoami(WHO_AM_I,MPU6050);

}

void SelfTest(s_DEVICE *MPU6050){

    uint8_t i,*Self_Test_Reg_Raw_Value;
    int8_t *Self_Test_Response,*Temp_Self_Values;
    float *Factory_Trim;

    Temp_Self_Values=(int8_t*)calloc(6,sizeof(int8_t));
    Self_Test_Response=(int8_t*)calloc(6,sizeof(int8_t));
    Factory_Trim=(float*)calloc(6,sizeof(float));
    Self_Test_Reg_Raw_Value=(uint8_t*)calloc(4,sizeof(uint8_t));


    /***********DISABLE SELF TEST********/
    /****WHEN PERFORMING ACCELEROMETER SELF TEST,THE FULL-SCALE RANGE SHOULD BE SET TO 8g ****/
    /****WHEN PERFORMING SELF TEST FOR GYROSCOPE,THE FULL-SCALE RANGE SHOULD BE SET TO 250DPS */

    MPU6050->ACCEL_CONFIG_Reg.AFS_SEL=AFS_SEL_8_g;
    Set_Reg_Position_and_Value(MPU6050,ACCEL_CONFIG);
    MPU6050_Write(ACCEL_CONFIG,MPU6050->Reg_Bits_Value.value,1);

	MPU6050_Read(SELF_TEST_X,Self_Test_Reg_Raw_Value,4);

	MPU6050->Get_Self_Test.AccelSelfValue[0] |=(Self_Test_Reg_Raw_Value[0]>>3);
	MPU6050->Get_Self_Test.AccelSelfValue[0] |=(((0x30)&(Self_Test_Reg_Raw_Value[3]))>>4);

	MPU6050->Get_Self_Test.AccelSelfValue[1] |=(Self_Test_Reg_Raw_Value[1]>>3);
	MPU6050->Get_Self_Test.AccelSelfValue[1] |=(((0x0C)&(Self_Test_Reg_Raw_Value[3]))>>2);

	MPU6050->Get_Self_Test.AccelSelfValue[2] |=(Self_Test_Reg_Raw_Value[2]>>3);
	MPU6050->Get_Self_Test.AccelSelfValue[2] |=((0x03)&(Self_Test_Reg_Raw_Value[3]));


	MPU6050->Get_Self_Test.GyroSelfValue[0] |=((0x1F)&(Self_Test_Reg_Raw_Value[0]));
	MPU6050->Get_Self_Test.GyroSelfValue[1] |=((0x1F)&(Self_Test_Reg_Raw_Value[1]));
	MPU6050->Get_Self_Test.GyroSelfValue[2] |=((0x1F)&(Self_Test_Reg_Raw_Value[2]));

	for(i=0;i<6;i++){

		if(i<3){

			Temp_Self_Values[i]=MPU6050->Get_Self_Test.AccelSelfValue[i];

		}
		else{

			Temp_Self_Values[i]=MPU6050->Get_Self_Test.GyroSelfValue[i-3];

		}
	}

	for(i=0;i<3;i++){

		MPU6050->Get_Self_Test.AccelSelfValue[i]=0;
		MPU6050->Get_Self_Test.GyroSelfValue[i]=0;
	}


	/****ENABLE SELF TEST*****/
	/****WHEN PERFORMING ACCELEROMETER SELF TEST,THE FULL-SCALE RANGE SHOULD BE SET TO 8g ****/
	/****WHEN PERFORMING SELF TEST FOR GYROSCOPE,THE FULL-SCALE RANGE SHOULD BE SET TO 250DPS */

	MPU6050->GYRO_CONFIG_Reg.ZG_ST=1;//ENABLE SELF TEST FOR GYROSCOPE Z AXES
	MPU6050->GYRO_CONFIG_Reg.YG_ST=1;//ENABLE SELF TEST FOR GYROSCOPE Y AXES
	MPU6050->GYRO_CONFIG_Reg.XG_ST=1;//ENABLE SELF TEST FOR GYROSCOPE X AXES
	Set_Reg_Position_and_Value(MPU6050,GYRO_CONFIG);
	MPU6050_Write(GYRO_CONFIG,MPU6050->Reg_Bits_Value.value,1);

	MPU6050->ACCEL_CONFIG_Reg.ZA_ST=1;//ENABLE SELF TEST FOR ACCELEROMETER Z AXES
	MPU6050->ACCEL_CONFIG_Reg.YA_ST=1;//ENABLE SELF TEST FOR ACCELEROMETER Y AXES
	MPU6050->ACCEL_CONFIG_Reg.XA_ST=1;//ENABLE SELF TEST FOR ACCELEROMETER X AXES
	MPU6050->ACCEL_CONFIG_Reg.AFS_SEL=AFS_SEL_8_g;
	Set_Reg_Position_and_Value(MPU6050,ACCEL_CONFIG);
	MPU6050_Write(ACCEL_CONFIG,MPU6050->Reg_Bits_Value.value,1);

	MPU6050_Read(SELF_TEST_X,Self_Test_Reg_Raw_Value,4);

	MPU6050->Get_Self_Test.AccelSelfValue[0] |=(((0XE0)&Self_Test_Reg_Raw_Value[0])>>3);
	MPU6050->Get_Self_Test.AccelSelfValue[0] |=(((0x30)&(Self_Test_Reg_Raw_Value[3]))>>4);

	MPU6050->Get_Self_Test.AccelSelfValue[1] |=(((0XE0)&Self_Test_Reg_Raw_Value[1])>>3);
	MPU6050->Get_Self_Test.AccelSelfValue[1] |=(((0x0C)&(Self_Test_Reg_Raw_Value[3]))>>2);

	MPU6050->Get_Self_Test.AccelSelfValue[2] |=(((0XE0)&Self_Test_Reg_Raw_Value[2])>>3);
	MPU6050->Get_Self_Test.AccelSelfValue[2] |=((0x03)&(Self_Test_Reg_Raw_Value[3]));

	MPU6050->Get_Self_Test.GyroSelfValue[0] |=((0x1F)&(Self_Test_Reg_Raw_Value[0]));
	MPU6050->Get_Self_Test.GyroSelfValue[1] |=((0x1F)&(Self_Test_Reg_Raw_Value[1]));
	MPU6050->Get_Self_Test.GyroSelfValue[2] |=((0x1F)&(Self_Test_Reg_Raw_Value[2]));

/*CALCULATE ACCELEROMETER STR VALUE and GYROSCOPE STR VALUE*/
//SELF TEST RESPONSE(STR)=ACCELEROMETER OUTPUT WITH SELF TEST ENABLED-ACCELEROMETER OUTPUT WITH SELF TEST DISABLE
//SELF TEST RESPONSE(STR)=GYROSCOPE OUTPUT WITH SELF TEST ENABLED-GYROSCOPE OUTPUT WITH SELF TEST DISABLE

	for(i=0;i<6;i++){

		if(i<3){

			Self_Test_Response[i]=MPU6050->Get_Self_Test.AccelSelfValue[i]-Temp_Self_Values[i];

		}
		else{

			Self_Test_Response[i]=MPU6050->Get_Self_Test.GyroSelfValue[i-3]-Temp_Self_Values[i];

		}

	}



	/***********CALCULATE FACTORY TRIM FOR ACCELEROMETER and GYROSCOPE**********/



	/****ACCELEROMETER*****/
	// FT[XA]=4069*0.34*((0.92/0.34)^(XA_TEST-1/30))
	// FT[YA]=4069*0.34*((0.92/0.34)^(YA_TEST-1/30))
	// FT[ZA]=4069*0.34*((0.92/0.34)^(ZA_TEST-1/30))

	for(i=0;i<3;i++){

		if(MPU6050->Get_Self_Test.AccelSelfValue[i]==0){

			Factory_Trim[i]=0;
		}
		else{

			Factory_Trim[i]=(4096*0.34)*(pow((0.92/0.34),(((float)MPU6050->Get_Self_Test.AccelSelfValue[i]-1)/30)));
		}
	}

	/****GYROSCOPE*****/
	// FT[XG]=25*131*1.046^(XG_TEST-1)
	// FT[YG]=-25*131*1.046^(YG_TEST-1)
	// FT[ZG]=25*131*1.046^(XG_TEST-1)

	for(i=0;i<3;i++){

		if((MPU6050->Get_Self_Test.GyroSelfValue[i]!=0 && i==0)||(MPU6050->Get_Self_Test.GyroSelfValue[i]!=0 && i==2)){

			Factory_Trim[i+3]=(25*131)*pow(1.046,(MPU6050->Get_Self_Test.GyroSelfValue[i]-1));
		}

		if(MPU6050->Get_Self_Test.GyroSelfValue[i]!=0 && i==1){

			Factory_Trim[i+3]=(-25*131)*pow(1.046,(MPU6050->Get_Self_Test.GyroSelfValue[i]-1));
		}

	}


	/*CHANGE from FACTORY TRIM OF THE SELF TEST RESPONSE(%)=100*((STR-FT)/(FT))*/

	//VALUE CHANGING from FACTORY TRIM OF THE SELF TEST RESPONSE must be 14% or smaller than 14%



	for(i=0;i<6;i++){

		MPU6050->Get_Self_Test.Change_FT_STR[i]=100+(100*((float)(Self_Test_Response[i]-Factory_Trim[i])/Factory_Trim[i]));
	}

	//CHECK RESULT OF SELF TEST BETWEEN -0,14 AND 0,14

	for(i=0;i<6;i++){

		if((MPU6050->Get_Self_Test.Change_FT_STR[i]<(-0.14))||(MPU6050->Get_Self_Test.Change_FT_STR[i]>(0.14))){

			MPU6050->Get_Self_Test.Self_Result=101;
			//YOU CAN WRITE ERROR or BLINKING LED etc
		}

	}


	/****RELEASE MEMORY AREA****/
	free(Temp_Self_Values);
	free(Factory_Trim);
	free(Self_Test_Reg_Raw_Value);
	free(Self_Test_Response);

}


void Calibration(float *Gyroscope_Bias,float *Accelerometer_Bias){

	uint8_t *Data;
	int16_t *Accel_Temp,*Gyro_Temp;
	uint16_t i,Packet_Count=0,Fifo_Count=0;
	int32_t *Gyro_Bias,*Accel_Bias;

	Accel_Temp=(int16_t*)calloc(3,sizeof(int16_t));
	Gyro_Temp=(int16_t*)calloc(3,sizeof(int16_t));
	Data=(uint8_t*)calloc(12,sizeof(uint8_t));
	Gyro_Bias=(long*)calloc(3,sizeof(long));
	Accel_Bias=(int32_t*)calloc(3,sizeof(int32_t));

	/**********RESET DEVICE**************/
	MPU6050_Write(PWR_MGMT_1,0x80,1);
	Delay_ms(200);

	//GET STABLE TIME SOURCE,SO SET CLOCK SOURCE TO BE PLL with X AXIS GYROSCOPE
	MPU6050_Write(PWR_MGMT_1,0x01,1);
	MPU6050_Write(PWR_MGMT_2,0x00,1);
	Delay_ms(200);

	/****CONFIGURE DEVICE for BIAS CALCULATION****/

	MPU6050_Write(INT_ENABLE,0x00,1);  //DISABLE ALL INTERRUPT
	MPU6050_Write(FIFO_EN,0x00,1);     //DISABLE FIFO
	MPU6050_Write(PWR_MGMT_1,0x00,1);  //TURN ON INTERNAL CLOCK SOURCE
	MPU6050_Write(I2C_MST_CTRL,0x00,1);//DISABLE I2C MASTER
	MPU6050_Write(USER_CTRL,0x00,1);   //DISABLE FIFO and I2C MASER MODE
	MPU6050_Write(USER_CTRL,0x04,1);   //RESET FIFO and DMP
    Delay_ms(15);

	/*****CONFIGURE MPU6050 GYRO and ACCELEROMETER for BIAS CALCULATION*****/

	MPU6050_Write(CONFIG,0x01,1);      //SET LOW-PASS FILTER TO 188 Hz
	MPU6050_Write(SMPLRT_DIV,0x00,1);  //SET SAMPLE RATE TO 1 kHz
	MPU6050_Write(GYRO_CONFIG,0x00,1); //SET GYRO SCALE as 250 DEGREE PER SECOND
	MPU6050_Write(ACCEL_CONFIG,0x00,1);//SET ACCELEROMETER SCALE as 2 g DEGREE PER SECOND

	Delay_ms(200);

	uint16_t  gyrosensitivity  = 131;  //32768/250 = 131 LSB/degrees/sec
	uint16_t  accelsensitivity = 16384;//32768/2 = 16384 LSB/g


	/*****Configure FIFO to capture accelerometer and gyro data for bias calculation*****/
	MPU6050_Write(USER_CTRL,0x40,1); //ENABLE FIFO
	MPU6050_Write(FIFO_EN,0x78,1);   //ENABLE GYRO and ACCELEROMETER SENSORS for FIFO (max size 1024 bytes in MPU-6050)
	Delay_ms(160); //ACCUMULATE SAMPLES THROUGHTOUT 160 MILLISECONDS

	/*****At end of SAMPLE ACCUMULATION,TURN OFF FIFO SENSOR READ*****/
	MPU6050_Write(FIFO_EN, 0x00,1);       //DISABLE GYRO and ACCELEROMETER SENSOR for FIFO
	MPU6050_Read(FIFO_COUNTH,&Data[0],2); //READ FIFO SAMPLE COUNT
	Fifo_Count=((uint16_t)Data[0]<<8)|Data[1];
	Packet_Count=Fifo_Count/12;//HOW MANY SETS of FULL GYRO and ACCELEROMETER DATA for AVERAGING

	for(i=0;i<Packet_Count;i++){

		MPU6050_Read(FIFO_R_W,&Data[0],12);//READ DATA FOR AVERAGING

		//FORM SIGNED 16 BIT INTEGER FOR EACH SAMPLE in FIFO
		Accel_Temp[0]=(int16_t)(((int16_t)Data[0]<<8)|Data[1]);
		Accel_Temp[1]=(int16_t)(((int16_t)Data[2]<<8)|Data[3]);
		Accel_Temp[2]=(int16_t)(((int16_t)Data[4]<<8)|Data[5]);

		Gyro_Temp[0]=(int16_t)(((int16_t)Data[6]<<8)|Data[7]);
		Gyro_Temp[1]=(int16_t)(((int16_t)Data[8]<<8)|Data[9]);
		Gyro_Temp[2]=(int16_t)(((int16_t)Data[10]<<8)|Data[11]);

		//SUM INDIVIDUAL SIGNED 16 BIT BIASES to GET ACCUMULATED SIGNED 32 BIT BIAS
		Accel_Bias[0]+=(int32_t)Accel_Temp[0];
		Accel_Bias[1]+=(int32_t)Accel_Temp[1];
		Accel_Bias[2]+=(int32_t)Accel_Temp[2];

		Gyro_Bias[0]+=(int32_t)Gyro_Temp[0];
		Gyro_Bias[1]+=(int32_t)Gyro_Temp[1];
		Gyro_Bias[2]+=(int32_t)Gyro_Temp[2];


	}

	//NORMALIZE SUMS to GET AVERAGE COUNT BIASES
	Accel_Bias[0] /= (int32_t)Packet_Count;
	Accel_Bias[1] /= (int32_t)Packet_Count;
	Accel_Bias[2] /= (int32_t)Packet_Count;

	Gyro_Bias[0] /= (int32_t)Packet_Count;
	Gyro_Bias[1] /= (int32_t)Packet_Count;
	Gyro_Bias[2] /= (int32_t)Packet_Count;


	//REMOVE GRAVITY from the Z-AXIS ACCELEROMETER BIAS CALCULATION
	if (Accel_Bias[2] > 0L) {
	    Accel_Bias[2] -= (int32_t) accelsensitivity;
	}
	else {
	    Accel_Bias[2] += (int32_t) accelsensitivity;
	 }

	//GYROSCOPE OFFSET VALUE EACH OTHER AXES
	Gyroscope_Bias[0] =(float)Gyro_Bias[0]/(float)gyrosensitivity;
	Gyroscope_Bias[1] =(float)Gyro_Bias[1]/(float)gyrosensitivity;
	Gyroscope_Bias[2] =(float)Gyro_Bias[2]/(float)gyrosensitivity;

	//ACCELEROMETER OFFSET VALUE EACH OTHER AXES
	Accelerometer_Bias[0]=(float)Accel_Bias[0]/(float)accelsensitivity;
	Accelerometer_Bias[1]=(float)Accel_Bias[1]/(float)accelsensitivity;
	Accelerometer_Bias[2]=(float)Accel_Bias[2]/(float)accelsensitivity;


	//****RELEASE MEMORY AREA****/
	free(Accel_Temp);
	free(Gyro_Temp);
	free(Data);
	free(Gyro_Bias);
	free(Accel_Bias);


}

void MPU6050_Config(s_DEVICE *MPU6050){

	if(MPU6050_Id==MPU6050->DeviceId){

		/**********PWR MNG 1 REGISTER CONFIGURATE**************/
		MPU6050->PWR_MNG_1_Reg.CLKSEL=CLKSEL_0;
		MPU6050->PWR_MNG_1_Reg.TEMP_DIS=0;
		MPU6050->PWR_MNG_1_Reg.CYCLE=0;
		MPU6050->PWR_MNG_1_Reg.SLEEP=0;
		MPU6050->PWR_MNG_1_Reg.DEVICE_RESET=0;
		Set_Reg_Position_and_Value(MPU6050,PWR_MGMT_1);
		MPU6050_Write(PWR_MGMT_1,MPU6050->Reg_Bits_Value.value,1);
		Delay_ms(125);

		/**********RESET ALL SIGNAL PATH**************/
		MPU6050->SIGNAL_PATH_RESET_Reg.TEMP_RESET=0;
		MPU6050->SIGNAL_PATH_RESET_Reg.ACCEL_RESET=0;
		MPU6050->SIGNAL_PATH_RESET_Reg.GYRO_RESET=0;
		Set_Reg_Position_and_Value(MPU6050,SIGNAL_PATH_RESET);
		MPU6050_Write(SIGNAL_PATH_RESET,MPU6050->Reg_Bits_Value.value,1);
		Delay_ms(125);

		/***********PWR MNG 2 REGISTER CONFIGURATE*************/
		MPU6050->PWR_MNG_2_Reg.STBY_ZG=0;
		MPU6050->PWR_MNG_2_Reg.STBY_YG=0;
		MPU6050->PWR_MNG_2_Reg.STBY_XG=0;
		MPU6050->PWR_MNG_2_Reg.STBY_ZA=0;
		MPU6050->PWR_MNG_2_Reg.STBY_YA=0;
		MPU6050->PWR_MNG_2_Reg.STBY_XA=0;
		MPU6050->PWR_MNG_2_Reg.LP_WAKE_CTRL=0;
		Set_Reg_Position_and_Value(MPU6050,PWR_MGMT_2);
		MPU6050_Write(PWR_MGMT_2,MPU6050->Reg_Bits_Value.value,1);

		/***********USER CTRL REGISTER CONFIGURATE*************/
		MPU6050->USER_CONTROL_Reg.SIG_COND_RESET=0;
		MPU6050->USER_CONTROL_Reg.I2C_MST_RESET=0;
		MPU6050->USER_CONTROL_Reg.FIFO_RESET=0;
		MPU6050->USER_CONTROL_Reg.I2C_IF_DIS=0;
		MPU6050->USER_CONTROL_Reg.I2C_MST_EN=0;
		MPU6050->USER_CONTROL_Reg._FIFO_EN=0;
		Set_Reg_Position_and_Value(MPU6050,USER_CTRL);
		MPU6050_Write(USER_CTRL,MPU6050->Reg_Bits_Value.value,1);

		/***********SAMPLE RATE DIVIDER REGISTER CONFIGURATE*************/
		MPU6050->SMPLRT_DIV_Reg.SMPLRT_DIVI=0x07;
		Set_Reg_Position_and_Value(MPU6050,SMPLRT_DIV);
		MPU6050_Write(SMPLRT_DIV,MPU6050->Reg_Bits_Value.value,1);

		/***********CONFIGURATION REGISTER CONFIGURATE*************/
		MPU6050->CONFIG_Reg.DLPF_CFG=DLPG_CFG_0;
		MPU6050->CONFIG_Reg.EXT_SYNC_SET=CR_Input_disabled;
		Set_Reg_Position_and_Value(MPU6050,CONFIG);
		MPU6050_Write(CONFIG,MPU6050->Reg_Bits_Value.value,1);

		/***********GYROSCOPE CONFIGURATION REGISTER CONFIGURATE*************/

		MPU6050->GYRO_CONFIG_Reg.FS_SEL=FS_SEL_250;
		MPU6050->GYRO_CONFIG_Reg.ZG_ST=0;
		MPU6050->GYRO_CONFIG_Reg.YG_ST=0;
		MPU6050->GYRO_CONFIG_Reg.XG_ST=0;
		Set_Reg_Position_and_Value(MPU6050,GYRO_CONFIG);
		MPU6050_Write(GYRO_CONFIG,MPU6050->Reg_Bits_Value.value,1);


		/***********ACCELEROMETER CONFIGURATION REGISTER CONFIGURATE*************/

		MPU6050->ACCEL_CONFIG_Reg.AFS_SEL=AFS_SEL_2_g;
		MPU6050->ACCEL_CONFIG_Reg.ZA_ST=0;
		MPU6050->ACCEL_CONFIG_Reg.YA_ST=0;
		MPU6050->ACCEL_CONFIG_Reg.XA_ST=0;
		Set_Reg_Position_and_Value(MPU6050,ACCEL_CONFIG);
		MPU6050_Write(ACCEL_CONFIG,MPU6050->Reg_Bits_Value.value,1);

		}

		else{

			//write error such as not match device id
		}

}


void AccelRead(s_DEVICE *MPU6050){

	int16_t Ax,Ay,Az;
	uint8_t Afs_Sel;
	float Sensivity;
	//READ ACCELEROMETER X AXES RAW VALUE
	MPU6050_Read(ACCEL_XOUT_H,&MPU6050->Accel_Out_Value.ACCEL_XOUT_RAW_H,2);

	//READ ACCELEROMETER Y AXES RAW VALUE
	MPU6050_Read(ACCEL_YOUT_H,&MPU6050->Accel_Out_Value.ACCEL_YOUT_RAW_H,2);

	//READ ACCELEROMETER Z AXES RAW VALUE
	MPU6050_Read(ACCEL_ZOUT_H,&MPU6050->Accel_Out_Value.ACCEL_ZOUT_RAW_H,2);

	//GET ACCEL X AXES OUT for COMBINE ACCEL X AXES RAW VALUES
	Ax=((int16_t)MPU6050->Accel_Out_Value.ACCEL_XOUT_RAW_H<<8)|MPU6050->Accel_Out_Value.ACCEL_XOUT_RAW_L;

	//GET ACCEL Y AXES OUT for COMBINE ACCEL Y AXES RAW VALUES
	Ay=((int16_t)MPU6050->Accel_Out_Value.ACCEL_YOUT_RAW_H<<8)|MPU6050->Accel_Out_Value.ACCEL_YOUT_RAW_L;

	//GET ACCEL Z AXES OUT for COMBINE ACCEL Z AXES RAW VALUES
	Az=((int16_t)MPU6050->Accel_Out_Value.ACCEL_ZOUT_RAW_H<<8)|MPU6050->Accel_Out_Value.ACCEL_ZOUT_RAW_L;


	//Get full scale range of accelerometer
	MPU6050_Read(ACCEL_CONFIG,&Afs_Sel,1);
	Afs_Sel=(Afs_Sel>>3)&0x03;
	switch(Afs_Sel){

	case 0:
		Sensivity=32750/2;
		break;
	case 1:
		Sensivity=32750/4;
		break;
	case 2:
		Sensivity=32750/8;
		break;
	case 3:
		Sensivity=32750/16;
		break;

	}


	MPU6050->Accel_Out_Value.Accel_Xout=((float)Ax/Sensivity)-MPU6050->Accelerometer_Bias[0];
	MPU6050->Accel_Out_Value.Accel_Yout=((float)Ay/Sensivity)-MPU6050->Accelerometer_Bias[1];
	MPU6050->Accel_Out_Value.Accel_Zout=((float)Az/Sensivity)-MPU6050->Accelerometer_Bias[2];


}

void GyroRead(s_DEVICE *MPU6050){

	int16_t Gx,Gy,Gz;
	uint8_t FS_Sel;
	float Sensivity;

	//READ GYROSCOPE X AXES RAW VALUE
	MPU6050_Read(GYRO_XOUT_H,&MPU6050->Gyro_Out_Value.GYRO_XOUT_RAW_H,2);
	//READ GYROSCOPE Y AXES RAW VALUE
	MPU6050_Read(GYRO_YOUT_H,&MPU6050->Gyro_Out_Value.GYRO_YOUT_RAW_H,2);
	//READ GYROSCOPE Z AXES RAW VALUE
	MPU6050_Read(GYRO_ZOUT_H,&MPU6050->Gyro_Out_Value.GYRO_ZOUT_RAW_H,2);

	//GET GYRO X AXES OUT for COMBINE GYRO X AXES RAW VALUES
	Gx=((int16_t)MPU6050->Gyro_Out_Value.GYRO_XOUT_RAW_H<<8)|MPU6050->Gyro_Out_Value.GYRO_XOUT_RAW_L;
	//GET GYRO Y AXES OUT for COMBINE GYRO Y AXES RAW VALUES
    Gy=((int16_t)MPU6050->Gyro_Out_Value.GYRO_YOUT_RAW_H<<8)|MPU6050->Gyro_Out_Value.GYRO_YOUT_RAW_L;
    //GET GYRO Z AXES OUT for COMBINE GYRO Z AXES RAW VALUES
    Gz=((int16_t)MPU6050->Gyro_Out_Value.GYRO_ZOUT_RAW_H<<8)|MPU6050->Gyro_Out_Value.GYRO_ZOUT_RAW_L;


    MPU6050_Read(GYRO_CONFIG,&FS_Sel,1);
    FS_Sel=(FS_Sel>>3)&0x03;
    switch(FS_Sel){

    case 0:
    	Sensivity=32750/250;
    	break;
    case 1:
    	Sensivity=32750/500;
    	break;
    case 2:
    	Sensivity=32750/1000;
    	break;
    case 3:
    	Sensivity=32750/2000;
    	break;
    }

    MPU6050->Gyro_Out_Value.GYRO_XOUT=((float)Gx/Sensivity)-MPU6050->Gyroscope_Bias[0];
    MPU6050->Gyro_Out_Value.GYRO_YOUT=((float)Gy/Sensivity)-MPU6050->Gyroscope_Bias[1];
    MPU6050->Gyro_Out_Value.GYRO_ZOUT=((float)Gz/Sensivity)-MPU6050->Gyroscope_Bias[2];

}


void TemperatureRead(s_DEVICE *MPU6050){

	int16_t TempCount;

	//READ TEMPERATURE RAW VALUE
	MPU6050_Read(TEMP_OUT_H,&MPU6050->Temp_Out_Value.TEMP_XOUT_RAW_H,2);
	//GET TEMPERATURE OUT for COMBINE TEMPERATURE RAW VALUES
	TempCount=((int16_t)MPU6050->Temp_Out_Value.TEMP_XOUT_RAW_H<<8)|MPU6050->Temp_Out_Value.TEMP_XOUT_RAW_L;

	MPU6050->Temp_Out_Value.Temperature_Value=((float)TempCount/340)+36.53;


}

