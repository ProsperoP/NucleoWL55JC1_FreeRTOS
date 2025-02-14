/*
 * communicationTask.h
 *
 *  Created on: Feb 14, 2025
 *      Author: Administrator
 */

#ifndef INC_COMMUNICATIONTASK_H_
#define INC_COMMUNICATIONTASK_H_

#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h" //For task creation

//Bits to notify
//To communication task from various places:
#define COMMUNICATIONTASK_USART_AVAILABLE 1 //From ISR to comm task
#define COMMUNICATIONTASK_MASK_USART_AVAILABLE NOTIFY_BIT_TO_MASK(COMMUNICATIONTASK_USART_AVAILABLE)
#define COMMUNICATIONTASK_DATAFROMHIGH_AVAILABLE 2 //From HighPrioTask to comm task, when data is avail in queue to be sent to host
#define COMMUNICATIONTASK_MASK_DATAFROMHIGH_AVAILABLE NOTIFY_BIT_TO_MASK(COMMUNICATIONTASK_DATAFROMHIGH_AVAILABLE)
#define COMMUNICATIONTASK_DATAFROMLOW_AVAILABLE 3 //From LowPrioTask when data is available (LowPrio is triggered by timer)
#define COMMUNICATIONTASK_MASK_DATAFROMLOW_AVAILABLE NOTIFY_BIT_TO_MASK(COMMUNICATIONTASK_DATAFROMLOW_AVAILABLE)

//From communication task to HighPrioTask
#define HIGHPRIOTASK_REQUEST 1 //Request to HighPrioTask
#define HIGHPRIOTASK_MASK_REQUEST NOTIFY_BIT_TO_MASK(HIGHPRIOTASK_REQUEST)



#endif /* INC_COMMUNICATIONTASK_H_ */
