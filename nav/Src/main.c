/*

  *FILE   		  :  Capstone project mm
  *PROJECT		  :  Truck space detection system
  *PROGRAMMER     	  :  Ashni Upadhyay, Navreet kaur harika, Nimal krishna
  *FIRST VERSION  	  :  07/10/2017
  *DESCRIPTION   	  :  This project is  for detecting the free space available in the commercial trucks using the
  *				  :   UV sensor
  *				  :   echo pin->PA0;Trig->PE10
  *				  : lcd connections  1->5v,2->gnd,3->contrast,4->PD0,5->PD1,6->PD2,
  *				  :11->PD4,12->PD5,13->PD6,14->PD7,15->5v,16->GND
  *				  stm connections: PE10->DEMUX 1,PE11->DEMUX 2,PE12->DEMUX 3,PE13->MUX 11,PE14->MUX 10,PE15->MUX 9,PA0->MUX 5
  *				  SENSOR1:TRIG->DEMUX 15,ECHO->MUX 4
  *				  SENSOR2:TRIG->DEMUX 14,ECHO->MUX 3
  *				  SENSOR3:TRIG->DEMUX 13,ECHO->MUX 2
  *				  SENSOR4:TRIG->DEMUX 12,ECHO->MUX 1
  *				  DEMUX:8,4,5->GND,16->VCCn
  *				  MUX:7,8->GND,16,6->VCC

An
n
 */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f3xx_hal.h"
#include "usart.h"
#include "gpio.h"
#include "dwt_stm32_delay.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void SystemClock_Config(void);
static void MX_NVIC_Init(void);
uint64_t volatile timer;
void HD44780_Init(void);
void HD44780_PutChar(unsigned char c);
void HD44780_GotoXY(unsigned char x, unsigned char y);
void HD44780_PutStr(char *str);
void HD44780_ClrScr(void);



static void MX_NVIC_Init(void)
{
  /* EXTI0_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);
}
void UU_PutChar(USART_TypeDef* USARTx, uint8_t ch)
{
  while(!(USARTx->ISR & USART_ISR_TXE));
  USARTx->TDR = ch;
}

void UU_PutString(USART_TypeDef* USARTx, uint8_t * str)
{
  while(*str != 0)
  {
    UU_PutChar(USARTx, *str);
    str++;
  }
}


void UU_PutNumber(USART_TypeDef* USARTx, uint32_t x)
{
  char value[10]; //a temp array to hold results of conversion
  int i = 0; //loop index

  do
  {
    value[i++] = (char)(x % 10) + '0'; //convert integer to character
    x /= 10;
  } while(x);

  while(i) //send data
  {
    UU_PutChar(USARTx, value[--i]);
  }
}

int main(void)
{

	char buffer[10];
		char buffer1[10];
		char buffer2[10];
		char buffer3[10];


  HAL_Init();
  MX_NVIC_Init();
 	  HD44780_Init();


  SystemClock_Config();

  MX_GPIO_Init();
  MX_USART1_Init();
  if(DWT_Delay_Init())
 	    {
 	      Error_Handler(); /* Call Error Handler */
 	    }

  while (1)
  {

	  HD44780_ClrScr();
	  HD44780_GotoXY(0, 0);						//set the character cursor to col=0, row=0
	  HD44780_PutStr("measuring...");			//display text
	 // HAL_Delay(500);


	  if(DWT_Delay_Init())
	    {
	      Error_Handler(); /* Call Error Handler */
	    }

	//send the trigger signal to sensor1

	//PE10,PE11,PE12 are selction pins
	for(int i=0;i<=3;i++)
	{

	if(i==0)  // trigger the sensor1
	{

		HAL_GPIO_WritePin(GPIOE,GPIO_PIN_10,1);
			HAL_GPIO_WritePin(GPIOE,GPIO_PIN_11,1);
			HAL_GPIO_WritePin(GPIOE,GPIO_PIN_12,1);
			DWT_Delay_us(1);
			HAL_GPIO_WritePin(GPIOE,GPIO_PIN_10,0);
			HAL_GPIO_WritePin(GPIOE,GPIO_PIN_11,0);
			HAL_GPIO_WritePin(GPIOE,GPIO_PIN_12,0);
			DWT_Delay_us(10);
			HAL_GPIO_WritePin(GPIOE,GPIO_PIN_10,1);
			HAL_GPIO_WritePin(GPIOE,GPIO_PIN_11,1);
			HAL_GPIO_WritePin(GPIOE,GPIO_PIN_12,1);

			HAL_GPIO_WritePin(GPIOE,GPIO_PIN_13,0);
			HAL_GPIO_WritePin(GPIOE,GPIO_PIN_14,0);
			HAL_GPIO_WritePin(GPIOE,GPIO_PIN_15,0);


			HAL_Delay(2000);

			timer =   (34000* timer) ;
			timer = (timer/72000000);
			sprintf(buffer1, "%d", timer);
			 HD44780_ClrScr();
			HD44780_GotoXY(7, 0);				//set the character cursor to col=0, row=0
			HD44780_PutStr(buffer1);				//display text
			HD44780_GotoXY(10, 0);
			HD44780_PutStr("cm");				//display text
			HAL_Delay(500);
			UU_PutNumber(USART1, timer);
					  UU_PutString(USART1, "\n");
					 // HAL_Delay(1000);


	
		  HAL_Delay(1000);*/

	}


	if(i==1)  // trigger the sensor2
	{

	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_10,1);
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_11,1);
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_12,1);
	DWT_Delay_us(1);
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_10,1);
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_11,0);
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_12,0);
	DWT_Delay_us(10);
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_10,1);
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_11,1);
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_12,1);

	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_13,1);
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_14,0);
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_15,0);


	HAL_Delay(2000);

	timer =   (34000* timer) ;
	timer = (timer/72000000);
	sprintf(buffer1, "%d", timer);

	HD44780_GotoXY(7, 0);				//set the character cursor to col=0, row=0
	HD44780_PutStr(buffer1);				//display text
	HD44780_GotoXY(10, 0);
	HD44780_PutStr("cm");				//display text
	HAL_Delay(500);
	UU_PutNumber(USART1, timer);
						  UU_PutString(USART1, "\n");
						  //HAL_Delay(1000);

	}

	if(i==2)  // trigger the sensor3
	{

	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_10,1);
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_11,1);
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_12,1);
	DWT_Delay_us(1);
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_10,0);
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_11,1);
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_12,0);
	DWT_Delay_us(10);
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_10,1);
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_11,1);
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_12,1);

	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_13,0);
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_14,1);
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_15,0);


	HAL_Delay(2000);


	timer =   (34000* timer) ;
	timer = (timer/72000000);			//calculate the distance
	sprintf(buffer2, "%d", timer);

	HD44780_GotoXY(0, 1);				//set the character cursor to col=0, row=0
	HD44780_PutStr(buffer2);				//display text
	HD44780_GotoXY(3, 1);
	HD44780_PutStr("cm");				//display text
	HAL_Delay(500);
	UU_PutNumber(USART1, timer);
						  UU_PutString(USART1, "\n");
						 // HAL_Delay(1000);

	}


	if(i==3)  // trigger the sensor4
	{

	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_10,1);
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_11,1);
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_12,1);
	DWT_Delay_us(1);
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_10,1);
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_11,1);
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_12,0);
	DWT_Delay_us(10);
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_10,1);
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_11,1);
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_12,1);

	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_13,1);
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_14,1);
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_15,0);


	HAL_Delay(2000);



	timer =   (34000* timer) ;
	timer = (timer/72000000);
	sprintf(buffer3, "%d", timer);

	HD44780_GotoXY(7, 1);				//set the character cursor to col=0, row=0
	HD44780_PutStr(buffer3);				//display text
	HD44780_GotoXY(10, 1);
	HD44780_PutStr("cm");				//display text
	HAL_Delay(500);
	UU_PutNumber(USART1, timer);
						  UU_PutString(USART1, "\n");
						 // HAL_Delay(1000);

	}

	}

  }


}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL12;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void _Error_Handler(char * file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1) 
  {
  }
  /* USER CODE END Error_Handler_Debug */ 
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
