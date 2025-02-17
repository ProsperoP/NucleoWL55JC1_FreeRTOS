/*
 * HighPrioTask.c
 *
 *  Created on: Feb 5, 2025
 *      Author: Administrator
 */

#include "HighPrioTask.h"
#include "app_queues.h"
#include "queue.h"
#include "communicationTask.h" //To be able to notify CommunicationTask

osThreadId_t highPrio_TaskHandle;
const osThreadAttr_t highPrio_Task_attributes =
{
    .name       = "HighPrio_Task",
    .stack_size = 128 * 32,
    .priority   = (osPriority_t) osPriorityHigh,
};

osMessageQueueId_t highPrioTaskReturnQueue;
const osMessageQueueAttr_t highPrioTaskReturnQueue_attributes = {.name = "highPrioTaskReturnQueue"};

void HighPrioTask_Begin(void* argument)
{
	uint32_t notificationBits = 0;
	//ASCII table fun
	//From 33 to 126 are characters
	uint32_t actChar = 33;

	for (;;)
	{
		//Wait for any notification. This is the HighPrioTask so the notifs come from CommunicationTask
		xTaskNotifyWait(0x00, 	// ulBitsToClearOnEntry
			  0xFFFFFFFF,			// ulBitsToClearOnExit
			  &notificationBits,	// *pulNotificationValue
			  portMAX_DELAY);		// xTicksToWait
		if (notificationBits & HIGHPRIOTASK_MASK_REQUEST)
		{
			//We received a notif from CommunicationTask, which is now suspended. Fill queue, then notif CommunicationTask.
			xQueueSend(highPrioTaskReturnQueue, &actChar, portMAX_DELAY);
			actChar++;
			if (actChar >126)
			{
				actChar = 33;
			}
			xTaskNotify(defaultTaskHandle, COMMUNICATIONTASK_MASK_DATAFROMHIGH_AVAILABLE, eSetBits);
		}
//			osDelay(1);
	}
}

