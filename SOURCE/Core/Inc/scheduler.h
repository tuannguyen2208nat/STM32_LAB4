/*
 * scheduler.h
 *
 *  Created on: Nov 30, 2023
 *      Author: tuann
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

typedef struct
{
	void (*pTask)(void); 	// Function pointer
	uint32_t Delay; 		// Delay ban đầu trước khi cho task chạy or delay = period for later
	uint32_t Period;		// Chu kỳ cho mỗi lần execute
	uint8_t RunMe;			// Flag for function to be executed
	uint32_t TaskID;		// Task ID
}sTask;

#define SCH_MAX_TASKS 5


void SCH_Init(void);
void SCH_Update(void);
void SCH_Dispatch_Tasks(void);
unsigned char SCH_Add_Task(void(*pFunction)(), unsigned int DELAY, unsigned int PERIOD);
unsigned char SCH_Delete_Task(uint32_t TASK_INDEX);
void SCH_Go_To_Sleep(void);
#endif /* INC_SCHEDULER_H_ */
