/*
 * task.c
 *
 *  Created on: Nov 30, 2023
 *      Author: tuann
 */
#include "main.h"
#include "task.h"

void task1(){
	HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
}
void task2(){
	HAL_GPIO_TogglePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin);
}
void task3(){
	HAL_GPIO_TogglePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin);
}
void task4(){
	HAL_GPIO_TogglePin(LED_WHITE_GPIO_Port, LED_WHITE_Pin);
}
void task5(){
	HAL_GPIO_TogglePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin);
}
