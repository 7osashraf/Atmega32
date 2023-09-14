/*
 * app.h
 *
 * Created: 10/11/2022 8:03:15 AM
 *  Author: ENG HOSAM
 */ 


#ifndef APP._H_
#define APP._H_

#include "../MCAL/DIO/dio.h"

#include "../HAL/BUTTON/button.h"
#include "../HAL/LED/led.h"


#define CAR_GREEN 0
#define CAR_YELLOW 1
#define CAR_RED 2

void AppStart();
void norma_lMode();
void pedestrianMode();
void callBack();
void off_all_led();



#endif /* APP._H_ */