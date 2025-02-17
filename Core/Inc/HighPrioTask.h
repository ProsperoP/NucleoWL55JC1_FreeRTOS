/*
 * HighPrioTask.h
 *
 *  Created on: Feb 5, 2025
 *      Author: Administrator
 */

#ifndef INC_HIGHPRIOTASK_H_
#define INC_HIGHPRIOTASK_H_

#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h" //For task creation

//Task handle
extern osThreadId_t highPrio_TaskHandle;
extern const osThreadAttr_t highPrio_Task_attributes;

//Queues used by this task

//Task function
void HighPrioTask_Begin(void* argument);




#endif /* INC_HIGHPRIOTASK_H_ */
