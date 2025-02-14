/*
 * interrupts.c
 *
 *  Created on: Feb 14, 2025
 *      Author: Administrator
 */

#include "main.h"
#include "communicationTask.h"

extern osThreadId_t defaultTaskHandle; //Defined as extern to be used

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	BaseType_t taskWoken = pdFALSE;
	xTaskNotifyFromISR(defaultTaskHandle, COMMUNICATIONTASK_MASK_USART_AVAILABLE, eSetBits, &taskWoken);
	portYIELD_FROM_ISR(taskWoken);
}


