
#include "i2cConfig.h"
#include "TimerConfig.h"
void i2cConfig(){

	RCC->APB1ENR |=(1<<21); //ENABLE CLOCK BUS of I2C1

	//RESET I2C
	I2C1->CR1 |=(1<<15);
	I2C1->CR1 &=~(1<<15);


	I2C1->CR2 =0x2A;        //SET PERIPHERAL CLOCK FREQUENCY(DETERMINED BY USED CLOCK BUS->APB1)
	//FOR FAST MODE
	I2C1->CCR |=(1<<15);    //I2C MASTER MODE SELECTED AS FM MODE
	I2C1->CCR |=(38<<0);	//SET SCL CLOCK->TSCL=1/(400*10^3)->TSCL=2.5us THIGH=(9/25)(2.5us)->THIGH=0.9us
	                        //CRR=THIGH/TPCLK=0.9us/23.8ns-> CCR=38 TPCLK=1/APB1->BECAUSE I2C LINE is on APB1 CLOCK BUS
	I2C1->TRISE |=(14<<0);  //TRISE=(TRISE/TPCLK)+1 WE DETERMINE TRISE ACCORDING TO SM OR FM MODE.TRISE VALUE SELECTED
							//BY FM MODE and THIS VALUE is 300 KHz
	//FOR STANDART MODE
	//I2C1->CCR |=(210<<0);
	//I2C1->TRISE |=(42<<0);

	//I2C1->FLTR =0;	    //NOT USE FILTER
	I2C1->CR1 |=(1<<0);		//ENABLE I2C


}

void i2cStart(){

	I2C1->CR1 |= (1<<10);//Enable the ACK Bit
	I2C1->CR1 |=(1<<8);
	while (!(I2C1->SR1 & (1<<0)));

}

void i2cStop(){

	I2C1->CR1 |=(1<<9);

}

void i2cDeviceAdrTrans(uint8_t Adr){

	I2C1->DR =Adr;
	while(!(I2C1->SR1 & (1<<1)));

}

void i2cRegAdrTrans(uint8_t Reg){

	uint8_t temp=I2C1->SR1 | I2C1->SR2; //Clear ADDR BIT
	temp*=temp;
	while(!(I2C1->SR1 & (1<<7))); //TO CHECK TXE-> EMPTY DATA REGISTER
	I2C1->DR=Reg;
	while(!(I2C1->SR1 & (1<<2))); //TO CHECK BTF-> BYTE TRANSFER FINISHED
}

void i2cDataTrans(uint8_t *Data,uint8_t Size){

	while(Size){

		while(!(I2C1->SR1 & (1<<7)));        //TO CHECK TXE-> EMPTY DATA REGISTER
		I2C1->DR=(uint8_t)*Data++;
		Size--;

	}

	while(!(I2C1->SR1 & (1<<2)));            //TO CHECK BTF-> BYTE TRANSFER FINISHED

}

void i2cDataReceive(uint8_t Address,uint8_t *Buffer,uint8_t Size){

	uint8_t remaining,temp;
	temp*=0;
	remaining=Size;


	if(Size==1){

		i2cDeviceAdrTrans(Address);
		while(!(I2C1->SR1 & (1<<1)));
		I2C1->CR1 &=~(1<<10); //GENERATE NACK SIGNAL
		temp=(I2C1->SR1 | I2C1->SR2); //Clear ADDR BIT
		i2cStop();
		while(!(I2C1->SR1 & (1<<6)));//CHECK DATA REGISTER NOT EMPTY
		Buffer[Size-remaining]=I2C1->DR; //READ DATA REGISTER

	}

	else{

		i2cDeviceAdrTrans(Address);
		temp=I2C1->SR1 | I2C1->SR2; //Clear ADDR BIT

		while(remaining>2){

			while(!(I2C1->SR1 & (1<<6)));      //CHECK DATA REGISTER NOT EMPTY
			Buffer[Size-remaining]=I2C1->DR;   //READ DATA REGISTER
			I2C1->CR1 |=(1<<10);			   //GENERATE ACK SIGNAL
			remaining--;
		}

		while(!(I2C1->SR1 & (1<<6)));    //CHECK DATA REGISTER NOT EMPTY
		Buffer[Size-remaining]=I2C1->DR; //READ DATA REGISTER
		I2C1->CR1 &=~(1<<10);            //GENERATE NACK SIGNAL
		I2C1->CR1 |=(1<<9);              //SET STOP BIT
		remaining--;
		while(!(I2C1->SR1 & (1<<6)));    //CHECK DATA REGISTER NOT EMPTY
		Buffer[Size-remaining]=I2C1->DR; //READ DATA REGISTER

	}
}


