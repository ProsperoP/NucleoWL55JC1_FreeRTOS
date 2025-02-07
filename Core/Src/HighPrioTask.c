/*
 * HighPrioTask.c
 *
 *  Created on: Feb 5, 2025
 *      Author: Administrator
 */

#include "HighPrioTask.h"

osThreadId_t highPrio_TaskHandle;
const osThreadAttr_t highPrio_Task_attributes =
{
    .name       = "ROIC_Task",
    .stack_size = 512 * 32,
    .priority   = (osPriority_t) osPriorityHigh,
};

