/*
 * test.c includes all the definitions of functions declared in test.h.
 *
 * It includes the Int Main().
 *
 * Author: Harsh Beriwal
 * IDE Used: MCUXpresso IDE v11.6.0 [Build 8187] [2022-07-13]
 *
 * Github Link: https://github.com/harshberiwal/PES_Assignment_3
 *
 * No leveraged code or files
 *
 */

#include "test.h"

int main(void) {

    //**********************Init board hardware***************************
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();

#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    //*********************Init FSL debug console*************************
    BOARD_InitDebugConsole();
#endif
	gpio_init();
	initialize_SysTick();
	startup_sequence();
	Touch_Init();

	//****************Starting with Red Led on****************************
	LED_ON_STATUS = change_LED();
    while(1) {
    	//*************Increments count every 100 ms**********************
		if((SysTick->VAL) <= TIME_OFFSET){
			count++;

			//*****Polling within the 100 ms if a button is pressed*******
			check_Touch();

			//*************Reinitializing the System timer****************
			SysTick->VAL = TICKS;

			//*********If Required Count reached then Toggles Led*********
			if(count==arr[index]){
				#ifdef DEBUG
					printf("STARTED TIMER of %d00 ms\n", arr[index]);
				#endif
				LED_ON_STATUS = change_LED();
				count =0;
				index++;
			}
    	}
		//***********Restart Sequence after it elapses********************
    	if(index == MAX_INDEX)
    		index =0;
    }
}
















