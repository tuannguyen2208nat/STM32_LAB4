/*
 * scheduler.c
 *
 *  Created on: Nov 30, 2023
 *      Author: tuann
 */


#include "task.h"
#include "main.h"
#include "scheduler.h"
#include <stdio.h>

sTask SCH_tasks_G[SCH_MAX_TASKS];


void SCH_Init(void){
	unsigned char task_index;
	for (task_index = 0; task_index < SCH_MAX_TASKS; task_index++){
		SCH_Delete_Task(task_index);
	}
}

void SCH_Update(void){
	unsigned char task_index;
	for (task_index = 0; task_index < SCH_MAX_TASKS; task_index++){
		if (SCH_tasks_G[task_index].pTask){
			if (SCH_tasks_G[task_index].Delay <= 0){
				SCH_tasks_G[task_index].RunMe += 1; 		//flag for execute task
				if (SCH_tasks_G[task_index].Period){
					SCH_tasks_G[task_index].Delay = SCH_tasks_G[task_index].Period;
				}
			}
			else {
				SCH_tasks_G[task_index].Delay -= 1;
			}
		}
	}
}

unsigned char SCH_Add_Task(void (*pFunction)(), unsigned int delay, unsigned int period){
	unsigned char task_index = 0;

	while ((SCH_tasks_G[task_index].pTask != 0) && (task_index < SCH_MAX_TASKS)){
		task_index++;
	}

	if (task_index == SCH_MAX_TASKS){
		return SCH_MAX_TASKS;
	}
	SCH_tasks_G[task_index].pTask = pFunction;
	SCH_tasks_G[task_index].Delay = delay;
	SCH_tasks_G[task_index].Period = period;
	SCH_tasks_G[task_index].RunMe = 0;
	SCH_tasks_G[task_index].TaskID = task_index;

	return task_index;
}

void SCH_Dispatch_Tasks(void){
	// Dispatches (runs) the next task (if there is one ready).
	for (unsigned task_index = 0; task_index < SCH_MAX_TASKS; task_index++){
		if (SCH_tasks_G[task_index].RunMe > 0){
			//printf("\r\n> Execute task ID %lu with period = %lu\r\n", SCH_tasks_G[task_index].TaskID, SCH_tasks_G[task_index].Period);
			(*SCH_tasks_G[task_index].pTask)();
			SCH_tasks_G[task_index].RunMe -= 1; 				// Set flag for execute  = 0

			// ONE SHOT_TASK GET REMOVED
			if (SCH_tasks_G[task_index].Period == 0){
				SCH_Delete_Task(task_index);
			}
		}
	}
	SCH_Go_To_Sleep();
}

unsigned char SCH_Delete_Task(uint32_t task_index){
	unsigned char Return_code = 0;
	if (SCH_tasks_G[task_index].pTask == 0)
	{
		// Error_code_G = ERROR_SCH_CANNOT_DELETE_TASK;
		// Return_code = RETURN_ERROR;
	}
	else
	{
		// Return_code = RETURN_NORMAL;
	}
	SCH_tasks_G[task_index].pTask = 0x000;
	SCH_tasks_G[task_index].Delay = 0;
	SCH_tasks_G[task_index].Period = 0;
	SCH_tasks_G[task_index].RunMe = 0;
	return Return_code;
}

void SCH_Go_To_Sleep(void){
	HAL_SuspendTick();
	HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);
	HAL_ResumeTick();
}
