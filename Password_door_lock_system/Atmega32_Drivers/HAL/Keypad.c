/*
 * Keypad.c
 *
 * Created: 11/8/2022 4:06:01 AM
 *  Author: vip
 */ 

#include "Keypad.h"

char keypad[4][4]={{'7','8','9','/'},{'4','5','6','*'},{'1','2','3','-'},{'c','0','=','+'}};
	
char keypad_NUM[4][4]={{7,8,9,'/'},{4,5,6,'*'},{1,2,3,'-'},{'c',0,'=','+'}};

int Keypad_Read_Row[]={0,1,2,3};
int Keypad_Row[]={R0,R1,R2,R3};
int Keypad_Col[]={C0,C1,C2,C3};

void keypad_init(void)
{
	GPIO_Pinconfig_t keypad_Conf ;
	keypad_Conf.GPIO_MODE=GPIO_MODE_OUTPUT;
	keypad_Conf.pinNumber=C0;
	MCAL_GPIO_Init(Keypad_Col_port,&keypad_Conf);
	
	keypad_Conf.GPIO_MODE=GPIO_MODE_OUTPUT;
	keypad_Conf.pinNumber=C1;
	MCAL_GPIO_Init(Keypad_Col_port,&keypad_Conf);
	
	keypad_Conf.GPIO_MODE=GPIO_MODE_OUTPUT;
	keypad_Conf.pinNumber=C2;
	MCAL_GPIO_Init(Keypad_Col_port,&keypad_Conf);
	
	keypad_Conf.GPIO_MODE=GPIO_MODE_OUTPUT;
	keypad_Conf.pinNumber=C3;
	MCAL_GPIO_Init(Keypad_Col_port,&keypad_Conf);
	
	keypad_Conf.GPIO_MODE=GPIO_MODE_INPUT_PU;
	keypad_Conf.pinNumber=R0;
	MCAL_GPIO_Init(Keypad_port,&keypad_Conf);
	
	keypad_Conf.GPIO_MODE=GPIO_MODE_INPUT_PU;
	keypad_Conf.pinNumber=R1;
	MCAL_GPIO_Init(Keypad_port,&keypad_Conf);
	
	keypad_Conf.GPIO_MODE=GPIO_MODE_INPUT_PU;
	keypad_Conf.pinNumber=R2;
	MCAL_GPIO_Init(Keypad_port,&keypad_Conf);
	
	keypad_Conf.GPIO_MODE=GPIO_MODE_INPUT_PU;
	keypad_Conf.pinNumber=R3;
	MCAL_GPIO_Init(Keypad_port,&keypad_Conf);
	
}

char keypad_getkey(void)
{
	int i,j;
	for(i=0;i<4;i++)
	{
		MCAL_GPIO_WritePin(Keypad_Col_port,C0,GPIO_PIN_SET);
		MCAL_GPIO_WritePin(Keypad_Col_port,C1,GPIO_PIN_SET);
		MCAL_GPIO_WritePin(Keypad_Col_port,C2,GPIO_PIN_SET);
		MCAL_GPIO_WritePin(Keypad_Col_port,C3,GPIO_PIN_SET);
		MCAL_GPIO_WritePin(Keypad_Col_port,Keypad_Col[i],GPIO_PIN_RESET);
		for(j=0;j<4;j++)
		{
			if(!(((uint8_t)MCAL_GPIO_ReadPort(Keypad_port)) & (1<<Keypad_Read_Row[j])))
			{
				while(!(((uint8_t)MCAL_GPIO_ReadPort(Keypad_port)) & (1<<Keypad_Read_Row[j])));
				return keypad_NUM[j][i];
			}
		}
	}
	return 'n';
}