/*
 * Keypad.c
 *
 * Created: 25/08/2022 01:25:49 ص
 *  Author: elmnshawy
 */ 

#include "Keypad.h"
char keypad[4][4]={{'7','8','9','/'},{'4','5','6','*'},{'1','2','3','-'},{'c','0','=','+'}};
uint16_t Keypad_Row[]={R0,R1,R2,R3};
uint16_t Keypad_Col[]={C0,C1,C2,C3};
GPIO_Pinconfig_t pincfg_Key;
void keypad_init(void)
{
	// pin{0,1,2,3} connected with row as input , pin{4,5,6,7} connected whit columns as output
	// pull_up active with  input

	pincfg_Key.pinNumber=C0;
	//PORTB Pin4 as output_pull_push
	pincfg_Key.GPIO_MODE=GPIO_MODE_OUTPUT_PP;
	//PORTB Pin4 at 10 MHZ
	pincfg_Key.GPIO_OUTPUT_Speed=GPIO_speed_10M;
	//init pin
	MCAL_GPIO_Init(Keypad_port,&pincfg_Key);

	pincfg_Key.pinNumber=C1;
	//PORTB Pin5 as output_pull_push
	pincfg_Key.GPIO_MODE=GPIO_MODE_OUTPUT_PP;
	//PORTB Pin4 at 10 MHZ
	pincfg_Key.GPIO_OUTPUT_Speed=GPIO_speed_10M;
	//init pin
	MCAL_GPIO_Init(Keypad_port,&pincfg_Key);

	pincfg_Key.pinNumber=C2;
	//PORTB Pin6 as output_pull_push
	pincfg_Key.GPIO_MODE=GPIO_MODE_OUTPUT_PP;
	//PORTB Pin6 at 10 MHZ
	pincfg_Key.GPIO_OUTPUT_Speed=GPIO_speed_10M;
	//init pin
	MCAL_GPIO_Init(Keypad_port,&pincfg_Key);

	pincfg_Key.pinNumber=C3;
	//PORTB Pin4 as output_pull_push
	pincfg_Key.GPIO_MODE=GPIO_MODE_OUTPUT_PP;
	//PORTB Pin7 at 10 MHZ
	pincfg_Key.GPIO_OUTPUT_Speed=GPIO_speed_10M;
	//init pin
	MCAL_GPIO_Init(Keypad_port,&pincfg_Key);

	pincfg_Key.pinNumber=R0;
	//PORTB Pin0 as Input pull_up
	pincfg_Key.GPIO_MODE=GPIO_MODE_INPUT_PD;
	//init pin
	MCAL_GPIO_Init(Keypad_port,&pincfg_Key);

	pincfg_Key.pinNumber=R1;
	//PORTB Pin1 as Input pull_up
	pincfg_Key.GPIO_MODE=GPIO_MODE_INPUT_PD;
	//init pin
	MCAL_GPIO_Init(Keypad_port,&pincfg_Key);

	pincfg_Key.pinNumber=R2;
	//PORTB Pin2 as Input pull_up
	pincfg_Key.GPIO_MODE=GPIO_MODE_INPUT_PD;
	//init pin
	MCAL_GPIO_Init(Keypad_port,&pincfg_Key);

	pincfg_Key.pinNumber=R3;
	//PORTB Pin3 as Input pull_up
	pincfg_Key.GPIO_MODE=GPIO_MODE_INPUT_PD;
	//init pin
	MCAL_GPIO_Init(Keypad_port,&pincfg_Key);


}

char keypad_getkey(void)
{
	int i,j;
	for(i=0;i<4;i++)
	{
		// set output pins is high
		MCAL_GPIO_WritePin(Keypad_port, C0, GPIO_PIN_RESET);
		MCAL_GPIO_WritePin(Keypad_port, C1, GPIO_PIN_RESET);
		MCAL_GPIO_WritePin(Keypad_port, C2, GPIO_PIN_RESET);
		MCAL_GPIO_WritePin(Keypad_port, C3, GPIO_PIN_RESET);

		MCAL_GPIO_WritePin(Keypad_port, Keypad_Col[i], GPIO_PIN_SET);  // set a column number i as low signal
		for(j=0;j<4;j++)
		{
			//while(!(MCAL_GPIO_ReadPort(Keypad_port) & Keypad_Row[j]));
			if((MCAL_GPIO_ReadPin(GPIOB,Keypad_Row[j]))==GPIO_PIN_SET)
			{
				while((MCAL_GPIO_ReadPin(GPIOB,Keypad_Row[j]))==GPIO_PIN_SET);
				return keypad[j][i];
			}
		}
	}
	return 'n';
}
