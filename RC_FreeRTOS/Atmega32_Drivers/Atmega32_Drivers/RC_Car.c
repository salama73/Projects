/*
 * RC_Car.c
 * Created: 14/09/2023
 * Author : Salama Mohamed
 */ 
/*********************************************************************************
***********************************Include****************************************
*********************************************************************************/
#include "RC_Car.h"
/********************************************************************************/
//Data buffer
uint8_t CMD_Data=0;
/*********************************************************************************
***********************************Semaphore Handle********************************
*********************************************************************************/
SemaphoreHandle_t MOTOR_Sem;
SemaphoreHandle_t Speed_Sem;
SemaphoreHandle_t LCD_Sem;
SemaphoreHandle_t Traffic_Sem;
SemaphoreHandle_t Turn_Signal_Sem;
/*********************************************************************************
***********************************Task Handle************************************
*********************************************************************************/
TaskHandle_t Bluetooth_RX_Handle=NULL;
TaskHandle_t MOTOR_State_Handle=NULL;
TaskHandle_t Set_Speed_Handle=NULL;
TaskHandle_t Print_State_Handle=NULL;
TaskHandle_t Traffic_State_Handle=NULL;
TaskHandle_t Turn_Signal_Handle=NULL;
/*********************************************************************************
***********************************service functions******************************
*********************************************************************************/
void GPIO_Init(void)
{
	GPIO_Pinconfig_t GPIO_Conf ;
	//Front Light Pin
	GPIO_Conf.pinNumber = GPIO_PIN_1 ;
	GPIO_Conf.GPIO_MODE =  GPIO_MODE_OUTPUT ;
	MCAL_GPIO_Init(GPIOC , &GPIO_Conf ) ;
	//Back Light Pin
	GPIO_Conf.pinNumber = GPIO_PIN_2 ;
	GPIO_Conf.GPIO_MODE =  GPIO_MODE_OUTPUT ;
	MCAL_GPIO_Init(GPIOC , &GPIO_Conf ) ;
	//Buzzer Pin
	GPIO_Conf.pinNumber = GPIO_PIN_3 ;
	GPIO_Conf.GPIO_MODE =  GPIO_MODE_OUTPUT ;
	MCAL_GPIO_Init(GPIOC , &GPIO_Conf ) ;
	//L298 MOTOR DRIVER Pin
	GPIO_Conf.pinNumber = GPIO_PIN_4 ;
	GPIO_Conf.GPIO_MODE =  GPIO_MODE_OUTPUT ;
	MCAL_GPIO_Init(GPIOC , &GPIO_Conf ) ;
	
	GPIO_Conf.pinNumber = GPIO_PIN_5 ;
	GPIO_Conf.GPIO_MODE =  GPIO_MODE_OUTPUT ;
	MCAL_GPIO_Init(GPIOC , &GPIO_Conf ) ;
	
	GPIO_Conf.pinNumber = GPIO_PIN_6 ;
	GPIO_Conf.GPIO_MODE =  GPIO_MODE_OUTPUT ;
	MCAL_GPIO_Init(GPIOC , &GPIO_Conf ) ;
	
	GPIO_Conf.pinNumber = GPIO_PIN_7 ;
	GPIO_Conf.GPIO_MODE =  GPIO_MODE_OUTPUT ;
	MCAL_GPIO_Init(GPIOC , &GPIO_Conf ) ;
	//PWM Pin For DC Motor
	GPIO_Conf.pinNumber = GPIO_PIN_4 ;
	GPIO_Conf.GPIO_MODE = GPIO_MODE_OUTPUT ;
	MCAL_GPIO_Init(GPIOD , &GPIO_Conf ) ;
}
//init Timer zero to Turn_Signal
void Timer0_init(void)
{
	TIMER0_config_t conf;
	conf.Timer0_Mode=TIMER0_MODE_CTC;
	conf.TOIE0_EN=TIMER0_TOIE0_ENABLE_Disable;
	conf.OCIE0_EN=TIMER0_OCIE0_ENABLE_Disable;
	conf.P_TOIE0_CALL=NULL;
	conf.P_OCIE0_CALL=NULL;
	conf.Output_Compare_pin=TIMER0_Output_Compare_pin_Toggle;
	conf.Compare_Value=255;
	conf.Clock_Source=TIMER0_Clock_Source_clk_1024;
	MCAL_TIMER0_Init(&conf);
	MCAL_TIMER0_Stop();
}
//Create  all the Tasks and semaphore 
void Task_init(void)
{
	//init pins
	GPIO_Init();
	//timer0 init to Traffic signal lights
	Timer0_init();
	//init 7 segment
	SEG_Init();
	//lcd init
	LCD_init();
	//DC MOTOR Init
	MOTOR_Init();
	//Set speed 1
	MOTOR_Speed(1);
	//Bluetooth module init
	Bluetooth_Init( INT_Disable);
	//Create Tasks
	xTaskCreate(CMD_RX,"CMD RX FROM Bluetooth Module",64,NULL,2,Bluetooth_RX_Handle);
	xTaskCreate(Moter_State,"Moter_States",64,NULL,1,MOTOR_State_Handle);
	xTaskCreate(Set_Speed,"Moter_Speed",64,NULL,1,Set_Speed_Handle);
	xTaskCreate(Print_State,"Print State on LCD",64,NULL,1,Print_State_Handle);
	xTaskCreate(Traffic_State,"Traffic_State Sound and lights",64,NULL,1,Traffic_State_Handle);
	xTaskCreate(Turn_Signal_State,"Traffic signal lights",64,NULL,1,Turn_Signal_Handle);
	//Create Semaphore
	MOTOR_Sem=xSemaphoreCreateBinary();
	Speed_Sem=xSemaphoreCreateBinary();
	LCD_Sem=xSemaphoreCreateBinary();
	Traffic_Sem=xSemaphoreCreateBinary();
	Turn_Signal_Sem=xSemaphoreCreateBinary();
}
/*********************************************************************************
***********************************Task Call Back*********************************
*********************************************************************************/
//receive command from Bluetooth
void CMD_RX(void *pvparam)
{
	uint8_t data=0;
	while (1)
	{
		Bluetooth_RX_Byte(&CMD_Data);
		switch(CMD_Data)
		{
			case 'B':
			case 'F':
			case 'R':
			case 'L':
			case 'S':
			//LCD task Check previous status
			if (data != CMD_Data)
			{
				xSemaphoreGive(LCD_Sem);
				vTaskPrioritySet(Print_State_Handle,2);
			}
			data=CMD_Data;
			xSemaphoreGive(MOTOR_Sem);
			vTaskPrioritySet(MOTOR_State_Handle,2);
			break;
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			xSemaphoreGive(Speed_Sem);
			vTaskPrioritySet(Set_Speed_Handle,2);
			break;
			case 'W':
			case 'w':
			case 'V':
			case 'v':
			case 'U':
			case 'u':
			xSemaphoreGive(Traffic_Sem);
			vTaskPrioritySet(Traffic_State_Handle,2);
			break;
			case 'X':
			case 'x':
			xSemaphoreGive(Turn_Signal_Sem);
			vTaskPrioritySet(Turn_Signal_Handle,2);
			break;
			default:
			vTaskDelay(10);
		}
		vTaskDelay(10);
	}
}
//start and stop Turn Signal
void Turn_Signal_State(void *pvparam)
{
	while(1)
	{
		if (xSemaphoreTake(Turn_Signal_Sem,0))
		{
			if (CMD_Data == 'X')
			{
				MCAL_TIMER0_Start();
			}
			else if(CMD_Data == 'x')
			{
				MCAL_TIMER0_Stop();
			}
		}
		vTaskPrioritySet(Turn_Signal_Handle,1);
		vTaskDelay(5);
	}
}
//Start and stop sound and light
void Traffic_State(void *pvparam)
{
	while(1)
	{
		if (xSemaphoreTake(Traffic_Sem,0))
		{
			if(CMD_Data =='V')
			{
				MCAL_GPIO_WritePin(GPIOC , GPIO_PIN_3 , GPIO_PIN_SET) ;
			}
			else if(CMD_Data =='v')
			{
				MCAL_GPIO_WritePin(GPIOC , GPIO_PIN_3 , GPIO_PIN_RESET) ;
			}
			else if(CMD_Data =='W')
			{
				MCAL_GPIO_WritePin(GPIOC , GPIO_PIN_1 , GPIO_PIN_SET) ;
			}
			else if(CMD_Data =='w')
			{
				MCAL_GPIO_WritePin(GPIOC , GPIO_PIN_1 , GPIO_PIN_RESET) ;
			}
			else if(CMD_Data =='U')
			{
				MCAL_GPIO_WritePin(GPIOC , GPIO_PIN_2 , GPIO_PIN_SET) ;
			}
			else if(CMD_Data =='u')
			{
				MCAL_GPIO_WritePin(GPIOC , GPIO_PIN_2 , GPIO_PIN_RESET) ;
			}
			else
			{
				//
			}
		}
		vTaskPrioritySet(Traffic_State_Handle,1);
		vTaskDelay(5);
	}
}
//print state car forward , back ....
void Print_State(void *pvparam)
{
	while(1)
	{
		if (xSemaphoreTake(LCD_Sem,0))
		{
			if(CMD_Data =='B')
			{
				lcd_Clear();
				LCD_String("BACK");
			}
			else if(CMD_Data =='F')
			{
				lcd_Clear();
				LCD_String("FORWARD");
			}
			else if(CMD_Data =='R')
			{
				lcd_Clear();
				LCD_String("RIGHT");
			}
			else if(CMD_Data =='L')
			{
				lcd_Clear();
				LCD_String("LIFT");
			}
			else if(CMD_Data =='S')
			{
				lcd_Clear();
				LCD_String("STOP");
			}
		}
		vTaskPrioritySet(Print_State_Handle,1);
		vTaskDelay(5);
	}
}
//Set the direction of a car
void Moter_State(void *pvparam)
{
	while(1)
	{
		if (xSemaphoreTake(MOTOR_Sem,0))
		{
			if(CMD_Data =='B')
			{
				MOTOR_Back();
			}
			else if(CMD_Data =='F')
			{
				MOTOR_Forward();
			}
			else if(CMD_Data =='R')
			{
				MOTOR_Speed(1);
				SEG_Display(1);
				MOTOR_Right();
			}
			else if(CMD_Data =='L')
			{
				MOTOR_Speed(1);
				SEG_Display(1);
				MOTOR_Left();
			}
			else if(CMD_Data =='S')
			{
				MOTOR_Speed(0);
				SEG_Display(0);
				MOTOR_Stop();
			}
		}
		vTaskPrioritySet(MOTOR_State_Handle,1);
		vTaskDelay(5);
	}
}
//Adjust the speed of the car
void Set_Speed(void *pvparam)
{
	uint8_t speed;
	while(1)
	{
		speed=CMD_Data-'0';
		if (xSemaphoreTake(Speed_Sem,0))
		{
			SEG_Display(speed);
			MOTOR_Speed(speed);
		}
		vTaskPrioritySet(Set_Speed_Handle,1);
		vTaskDelay(7);
	}
}
/*********************************************************************************
***********************************End********************************************
*********************************************************************************/