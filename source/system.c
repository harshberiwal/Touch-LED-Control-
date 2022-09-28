/*
 * system.c includes all the definition of initialzing the SysTick
 * This include initialize_Systick()
 *
 * Author: Harsh Beriwal
 * IDE Used: MCUXpresso IDE v11.6.0 [Build 8187] [2022-07-13]
 *
 * Github Link: https://github.com/harshberiwal/PES_Assignment_3
 *
 * No leveraged code or files
 *
 */


#include "system.h"

void initialize_SysTick(){

	//************Initialize System Timer with the Required Ticks of 4.8 MHz********
	SysTick->LOAD = TICKS;
	SysTick->VAL  = TICKS;
	SysTick->CTRL = 0b0101;
}
