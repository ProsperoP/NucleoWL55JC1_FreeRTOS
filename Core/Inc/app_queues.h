/*
 * app_queues.h
 *
 *  Created on: Feb 5, 2025
 *      Author: Administrator
 */

#ifndef INC_APP_QUEUES_H_
#define INC_APP_QUEUES_H_

#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h" //For task creation

//Here lies the extern declaration of queues. The declaration is done in each task's .c file, and the definition of each queue is done in app_freertos.c.
//So, to use the queues, we just have to include this file.
extern osMessageQueueId_t highPrioTaskReturnQueue;
extern const osMessageQueueAttr_t highPrioTaskReturnQueue_attributes;

//NOTIFICATION BITS DEFINITION

//Bits to notify
//To communication task from various places:
#define COMMUNICATIONTASK_USART_AVAILABLE 1 //From ISR to comm task
#define COMMUNICATIONTASK_MASK_USART_AVAILABLE NOTIFY_BIT_TO_MASK(COMMUNICATIONTASK_USART_AVAILABLE)
#define COMMUNICATIONTASK_DATAFROMHIGH_AVAILABLE 2 //From HighPrioTask to comm task, when data is avail in queue to be sent to host
#define COMMUNICATIONTASK_MASK_DATAFROMHIGH_AVAILABLE NOTIFY_BIT_TO_MASK(COMMUNICATIONTASK_DATAFROMHIGH_AVAILABLE)
#define COMMUNICATIONTASK_DATAFROMLOW_AVAILABLE 3 //From LowPrioTask when data is available (LowPrio is triggered by timer)
#define COMMUNICATIONTASK_MASK_DATAFROMLOW_AVAILABLE NOTIFY_BIT_TO_MASK(COMMUNICATIONTASK_DATAFROMLOW_AVAILABLE)

//To HighPrioTask :
#define HIGHPRIOTASK_REQUEST 1 //Request from CommunicationTask
#define HIGHPRIOTASK_MASK_REQUEST NOTIFY_BIT_TO_MASK(HIGHPRIOTASK_REQUEST)


#endif /* INC_APP_QUEUES_H_ */
