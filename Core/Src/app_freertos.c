/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : app_freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "communicationTask.h" //To use notif bit private define
#include "HighPrioTask.h" //To be initialized ans started in here
#include <stdarg.h>
#include <stdio.h>
//#include "LowPrioTask.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
char outputBuffer[256]; //For output message
/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 128 * 4
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
void SendOutputMessage(const char* format, ...);
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */

  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
	uint32_t notificationBits = 0;
	char receivedChar = '\0';
	uint32_t sentNb = 0;

	//Start listening for one byte RX on serial port
	HAL_UART_Receive_IT(&huart2, (uint8_t*)&receivedChar, 1);
  /* Infinite loop */
  for(;;)
  {
	  //Wait for any notification. This is the communication task, so it will be notified (by interrupt) when data is received.
	  xTaskNotifyWait(0x00, 	// ulBitsToClearOnEntry
			  0xFFFFFFFF,			// ulBitsToClearOnExit
			  &notificationBits,	// *pulNotificationValue
			  portMAX_DELAY);		// xTicksToWait

	  if (notificationBits & COMMUNICATIONTASK_MASK_USART_AVAILABLE)
	  {
		  //A new character arrived and has been stored in receivedChar
		  //Send to end user the next char over USART
		  SendOutputMessage("Sent nb from commTask: %u\r\n", sentNb);
		  sentNb++;
		  HAL_UART_Abort_IT(&huart2); //Due to a bug in Cube, we have to abort IT to be able to receive properly after 1st receive (EIE flag not set, I think - tbd)
		  HAL_UART_Receive_IT(&huart2, (uint8_t*)&receivedChar, 1);
	  }
	  osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
void SendOutputMessage(const char* format, ...)
{
	va_list args;
	va_start(args, format);
	int strSize = vsnprintf(outputBuffer, 256, format, args); //Size does not include \0 char; snprintf is used to protect memory overflow
	HAL_UART_Transmit(&huart2, (uint8_t*)outputBuffer, strSize, 100);
}
/* USER CODE END Application */
