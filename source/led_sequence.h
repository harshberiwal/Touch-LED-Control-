/*
 * led_sequence.h includes all the declaration of functions related to LED
 * This include startup_sequence() and change_led() and Check_Touch()
 *
 * Author: Harsh Beriwal
 * IDE Used: MCUXpresso IDE v11.6.0 [Build 8187] [2022-07-13]
 *
 * Github Link: https://github.com/harshberiwal/PES_Assignment_3
 *
 * No leveraged code or files
 *
 */

#ifndef LED_SEQUENCE_H_
#define LED_SEQUENCE_H_

#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "system.h"
#include "touch.h"
#include "gpio.h"
#include "delay.h"
#include "test.h"

#define red_LED 		((uint32_t)(1 << 18))
#define green_LED 		((uint32_t)(1 << 19))
#define blue_LED 		((uint32_t)(1 << 1))
#define RED 			18
#define GREEN 			19
#define BLUE 			1
#define TIME_OFFSET 	1100
#define RED_LOWER_THRSD 480
#define RED_UPPER_THRSD 580
#define GREEN_UPPER_THRSD 730
#define RED_LED_ON 		252
#define GREEN_LED_ON 	250
#define BLUE_LED_ON 	249
#define ALL_ON			255
#define MAX_INDEX 		8
#define ALL_OFF 		248
#define MS_FIVE_HUNDRED 5
#define MS_HUNDRED		1
#define ONE_SECOND 		10
#define TWO_SECOND 		20
#define THREE_SECOND 	30
#define VAL_OFFSET  	30

typedef enum LED_toggle{
	Blue =0,
	Green,
	Red,
	all_LEDs
}LED_toggle_t;


/*
 * Generates the Startup Sequence of Red Green Blue LEDs
 *
 * Parameters:
 *   None
 *
 * Returns:
 *   None
 */
void startup_sequence();

/*
 * Toggles the LED and returns if the LED is on or off
 *
 * Parameters:
 *   None
 *
 * Returns:
 *  Returns the value into the LED_ON_STATUS flag.
 *  True if LED is ON and False if the LED is off
 */
bool change_LED();

/*
 * Checks if the scanned value from the touch slider falls in which category.
 * There are various category that changes LED Color in the function.
 *
 * Parameters:
 *   None
 *
 * Returns:
 *   None
 */
void check_Touch();

#endif /* LED_SEQUENCE_H_ */
