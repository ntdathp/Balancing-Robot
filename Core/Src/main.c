/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "usb.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "mpu6050.h"
#include "motor.h"
#include "Balance_fis.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <complex.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#define K_pitch 1/5
#define K_pitch_dot 1/100
#define K_u 3000
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */


typedef struct {
	float pitch_dot;
	float pitch;
	float input[2];
	float output;
}Balance_t;

enum filter
{
	Kalman,
	CF,
	R,
	L,
	F,
	D
};

enum filter current;



uint32_t tim;

MPU6050_t MPU;
Motor_t motor1, motor2;
Balance_t Balance;

uint8_t buff[1];
int i;

uint8_t buffer[10];

char result[20];

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_USART2_UART_Init();
  MX_I2C1_Init();
  MX_TIM1_Init();
  MX_TIM4_Init();
  MX_USART3_UART_Init();
  MX_USB_PCD_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT(&htim2);

  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);

  HAL_UART_Receive_IT(&huart2,(uint8_t*)buff, 1);
  HAL_UART_Transmit(&huart3, (uint8_t *)result, sizeof(result), 100);

  MPU6050_Init(&hi2c1);

  Balance_init();


  current = CF;

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */


  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLL;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{

	    if(huart ->Instance == huart2.Instance)
	    {


	    	if(buff[0] == 'R')
	    		{
	    			current = R;
	    		}
	    	else if(buff[0] == 'L')
	    		{
	    			current = L;
	    		}
	    	else if(buff[0] == 'F')
	    		{
	    			current = F;
	    		}
	    	else if(buff[0] == 'D')
	    		{
	    		    current = D;
	    		}
	    	else if (buff[0] == 'C')
	    	{
	    		current = CF;
	    	}
	    	}
	    HAL_UART_Receive_IT(&huart2,(uint8_t*)buff, 1);

}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{

	  if(htim->Instance == htim2.Instance)
	  {

		  double dt = (double)(HAL_GetTick() - tim) / 1000;
		  tim = HAL_GetTick();

		  MPU6050_Read_All(&hi2c1, &MPU);

		  switch(current){

		  case Kalman:
			  MPU.KalmanAngleY += 1.12;

			  Balance.pitch_dot = (MPU.KalmanAngleY - Balance.pitch) / dt ;


			  Balance.input[0] = MPU.KalmanAngleY *  K_pitch;
			  Balance.input[1] = Balance.pitch_dot * K_pitch_dot;

			  Balance.pitch = MPU.KalmanAngleY;

			  Balance_run(Balance.input, &Balance.output);

			  if(Balance.input[0] < -10 || Balance.input[0] > 10)
				  	  {
					  	  Balance.output = 0;
				  	  }


			  MotorSetDuty1(Balance.output * K_u);
			  MotorSetDuty2(Balance.output * K_u);
			  break;

		  case CF:

			  Balance.pitch_dot = MPU.Gy;

			  Balance.input[0] = MPU.CFAngleY *  K_pitch;
			  Balance.input[1] = Balance.pitch_dot * K_pitch_dot;

			  Balance.pitch = MPU.CFAngleY;

			  Balance_run(Balance.input, &Balance.output);

			  if(Balance.input[0] < -10 || Balance.input[0] > 10)
				  	  {
					  	  Balance.output = 0;
				  	  }


			  MotorSetDuty1(Balance.output * K_u);
			  MotorSetDuty2(Balance.output * K_u);


			    double real[3] = {Balance.input[0], Balance.input[1], Balance.output};

			    strcpy(result, "=");
			    for (int i = 0; i < 3; i++) {
			          char buffer[20];
			          snprintf(buffer, sizeof(buffer), "%.2f", creal(real[i]));
			          strcat(result, buffer);

			          if (i < 2) {
			              strcat(result, ",");
			          }
			      }
			    strcat(result, "!");
			    HAL_UART_Transmit(&huart3, (uint8_t *)result, sizeof(result), 100);

			   break;
		   case R:
			              Balance.pitch_dot = MPU.Gy + 2;

			 			  Balance.input[0] = MPU.CFAngleY *  K_pitch;
			 			  Balance.input[1] = Balance.pitch_dot * K_pitch_dot;

			 			  Balance.pitch = MPU.CFAngleY;

			 			  Balance_run(Balance.input, &Balance.output);

			 			  if(Balance.input[0] < -10 || Balance.input[0] > 10)
			 				  	  {
			 					  	  Balance.output = 0;
			 				  	  }


			 			  MotorSetDuty1(Balance.output * K_u - 1000);
			 			  MotorSetDuty2(Balance.output * K_u);

				  if(Balance.input[0] < -0.75 || Balance.input[0] > 0.75)
					  	  {
						  	  current = CF;
					  	  }


			   break;
		   case L:
			                          Balance.pitch_dot = MPU.Gy + 2;

			  			 			  Balance.input[0] = MPU.CFAngleY *  K_pitch;
			  			 			  Balance.input[1] = Balance.pitch_dot * K_pitch_dot;

			  			 			  Balance.pitch = MPU.CFAngleY;

			  			 			  Balance_run(Balance.input, &Balance.output);

			  			 			  if(Balance.input[0] < -10 || Balance.input[0] > 10)
			  			 				  	  {
			  			 					  	  Balance.output = 0;
			  			 				  	  }


			  			 			  MotorSetDuty1(Balance.output * K_u );
			  			 			  MotorSetDuty2(Balance.output * K_u - 1000);
				  if(Balance.input[0] < -0.75 || Balance.input[0] > 0.75)
					  	  {
						  	  current = CF;
					  	  }


			   break;
		   case F:
			                                      Balance.pitch_dot = MPU.Gy + 2;

			   			  			 			  Balance.input[0] = MPU.CFAngleY *  K_pitch;
			   			  			 			  Balance.input[1] = Balance.pitch_dot * K_pitch_dot;

			   			  			 			  Balance.pitch = MPU.CFAngleY;

			   			  			 			  Balance_run(Balance.input, &Balance.output);

			   			  			 			  if(Balance.input[0] < -10 || Balance.input[0] > 10)
			   			  			 				  	  {
			   			  			 					  	  Balance.output = 0;
			   			  			 				  	  }


			   			  			 			  MotorSetDuty1(Balance.output * K_u );
			   			  			 			  MotorSetDuty2(Balance.output * K_u);
				  if(Balance.input[0] < -0.75 || Balance.input[0] > 0.75)
					  	  {
						  	  current = CF;
					  	  }


			   break;
		   case D:
			   Balance.pitch_dot = MPU.Gy - 2;

			 			   			  			 			  Balance.input[0] = MPU.CFAngleY *  K_pitch;
			 			   			  			 			  Balance.input[1] = Balance.pitch_dot * K_pitch_dot;

			 			   			  			 			  Balance.pitch = MPU.CFAngleY;

			 			   			  			 			  Balance_run(Balance.input, &Balance.output);

			 			   			  			 			  if(Balance.input[0] < -10 || Balance.input[0] > 10)
			 			   			  			 				  	  {
			 			   			  			 					  	  Balance.output = 0;
			 			   			  			 				  	  }


			 			   			  			 			  MotorSetDuty1(Balance.output * K_u );
			 			   			  			 			  MotorSetDuty2(Balance.output * K_u);
				  if(Balance.input[0] < -0.75 || Balance.input[0] > 0.75)
					  	  {
						  	  current = CF;
					  	  }


			   break;

		  }

		  		  current = CF;
	  }
}



/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
