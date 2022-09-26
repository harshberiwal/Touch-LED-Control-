/*
 * test.h includes all the declarations of functions used in test.c
 * The details of each function is given below.
 *
 * Author: Harsh Beriwal
 * IDE Used: MCUXpresso IDE v11.6.0 [Build 8187] [2022-07-13]
 *
 * No leveraged code or files
 *
 */

#ifndef TEST_H_
#define TEST_H_

#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"


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
#define MAX_INDEX 		sizeof(arr)
#define HUNDRED_MS 		4800000
#define TICKS 			(HUNDRED_MS + TIME_OFFSET)
#define PORT_A 			(uint32_t)(1 <<10)
#define PORT_B 			(uint32_t)(1 <<12)
#define ALL_OFF 		248
#define MS_FIVE_HUNDRED 5
#define MS_HUNDRED		1
#define ONE_SECOND 		10
#define TWO_SECOND 		20
#define THREE_SECOND 	30
#define VAL_OFFSET  	30
#define OSC_PRESCALER	4
#define ELECTRODES		11
#define ELEC_CHARGE		7


typedef enum LED_toggle{
	Blue =0,
	Green,
	Red,
	all_LEDs
}LED_toggle_t;

bool LED_ON_STATUS=false;
uint8_t led_color = 248;
uint8_t past_led_color = 0;

uint8_t initial_arr[] ={MS_FIVE_HUNDRED, MS_HUNDRED, MS_FIVE_HUNDRED, MS_HUNDRED,
		MS_FIVE_HUNDRED, MS_HUNDRED, MS_HUNDRED, MS_HUNDRED, MS_HUNDRED, MS_HUNDRED};

uint8_t initial_sequence[] = {RED_LED_ON, ALL_OFF, GREEN_LED_ON, ALL_OFF,
			BLUE_LED_ON, ALL_OFF, ALL_OFF, ALL_OFF, ALL_OFF, ALL_OFF, ALL_OFF};

uint8_t arr[] = {MS_FIVE_HUNDRED, MS_FIVE_HUNDRED, ONE_SECOND, MS_FIVE_HUNDRED,
		TWO_SECOND, MS_FIVE_HUNDRED, THREE_SECOND, MS_FIVE_HUNDRED};

int index =0, count =0, touch_val =0 ;
int offset_R =0, offset_G =0, offset_B =0;

/*
 * Initializes pins as GPIO output
 *
 * Parameters:
 *   None
 *
 * Returns:
 *   None
 */
void gpio_init();

/*
 * A crude way to generate delay using a increment for loop
 *
 * Parameters:
 *   None
 *
 * Returns:
 *   None
 */
void delay_us(uint32_t value);

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
 * Scans the capacitive Touch Slider and returns value corresponding to the touch strength and area.
 *
 * Parameters:
 *   None
 *
 * Returns:
 *   Scanned Value between 0 to 65535
 */
int Touch_Poll(void);


/*
 * Initializes the capacitive Touch Slider and the GENCS and DATA register to get the Touch Value
 *
 * Parameters:
 *   None
 *
 * Returns:
 *   None
 */
void Touch_Init();


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

/*
 * Initializes SysTick and its registers like VAL, LOAD for precise delays
 *
 * Parameters:
 *   None
 *
 * Returns:
 *   None
 */
void initialize_SysTick();


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

#endif /* TEST_H_ */







