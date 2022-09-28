/*
 * delay.c includes the definition of function related to delay
 * This include delay_us()
 *
 * Author: Harsh Beriwal
 * IDE Used: MCUXpresso IDE v11.6.0 [Build 8187] [2022-07-13]
 *
 * Github Link: https://github.com/harshberiwal/PES_Assignment_3
 *
 * No leveraged code or files
 *
 */

#include "delay.h"

void delay_us(uint32_t value)
{
	//***********Iterate here until the intended value is reached*******************
	for(int i =0; i<value;i++);
}
