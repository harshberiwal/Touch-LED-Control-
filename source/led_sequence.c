/*
 * led_sequence.c includes all the definitions of functions declared in
 * led_sequence.h
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

#include "led_sequence.h"


//*****************Variable to Check current LED Status*******************
bool LED_ON_STATUS=false;

//******************VARIABLE TO CHECK TOUCH LED REGION********************
uint8_t led_color = ALL_OFF;

//*******************VARIABLE TO TRACK CHANGE IN COLOR********************
uint8_t past_led_color = 0;

//***************ARRAY WITH ALL INITIAL SEQUENCE DELAY********************
uint8_t initial_arr[] ={MS_FIVE_HUNDRED, MS_HUNDRED, MS_FIVE_HUNDRED,
		MS_HUNDRED, MS_FIVE_HUNDRED, MS_HUNDRED, MS_HUNDRED, MS_HUNDRED,
		MS_HUNDRED, MS_HUNDRED};

//***************ARRAY WITH ALL INITIAL SEQUENCE ORDER********************
uint8_t initial_sequence[] = {RED_LED_ON, ALL_OFF, GREEN_LED_ON, ALL_OFF,
			BLUE_LED_ON, ALL_OFF, ALL_OFF, ALL_OFF, ALL_OFF,
			ALL_OFF, ALL_OFF};

//***************ARRAY WITH ALL INFINITE SEQUENCE ORDER*******************
uint8_t arr[] = {MS_FIVE_HUNDRED, MS_FIVE_HUNDRED, ONE_SECOND,
		MS_FIVE_HUNDRED, TWO_SECOND, MS_FIVE_HUNDRED, THREE_SECOND,
		MS_FIVE_HUNDRED};

int index =0, count =0, touch_val =0;
int offset_R =0, offset_G =0, offset_B =0;


void startup_sequence()
{
	#ifdef DEBUG
		printf("Displaying Initial Sequence...\n");
	#endif

	//****************Starting with Red Led on****************************
	led_color = initial_sequence[index];
	LED_ON_STATUS = change_LED();

	//*************Looping until the sequence is complete*****************
	while(index<(MAX_INDEX+1))
	{
		//*****************Increments count every 100 ms******************
		if((SysTick -> VAL) <= TIME_OFFSET){
			count++;
			SysTick -> VAL = TICKS;

			//************Checks if the required time is reached**********
			if(count==initial_arr[index]){
				led_color = initial_sequence[index + 1];

				//******************Toggles LED***************************
				LED_ON_STATUS = change_LED();
				count =0;
				index++;
			}
		}
	}

	//**********Reinitializing all the values for next sequence***********
	led_color = ALL_OFF;
	index =0;
	count =0;
}


bool change_LED()
{
	//***************Checks if the LED is high or low*********************
	if(!LED_ON_STATUS){

		//*****************Checks if the LED is Red **********************
		if(led_color & (1<<Red)){

			//***************Checks if the Color Changed******************
			if(led_color !=past_led_color){
				#ifdef DEBUG
					printf("Change LED color to RED\n");
				#endif
			}
			//*********************Turns on RED LED***********************
			past_led_color = led_color;
			GPIOB -> PDOR |= green_LED;
			GPIOD -> PDOR |= blue_LED;
			GPIOB -> PDOR &= ~red_LED;
		}

		//*****************Checks if the LED is Green*********************
		else if(led_color & (1<<Green)){

			//***************Checks if the Color Changed******************
			if(led_color !=past_led_color){
				#ifdef DEBUG
					printf("Change LED color to GREEN\n");
				#endif
			}

			//*********************Turns on GREEN LED*********************
			past_led_color = led_color;
			GPIOB -> PDOR |= red_LED;
			GPIOD -> PDOR |= blue_LED;
			GPIOB -> PDOR &= ~green_LED;
		}

		//*****************Checks if the LED is Blue**********************
		else if(led_color & (1<<Blue)){

			//***************Checks if the Color Changed******************
			if(led_color !=past_led_color){
				#ifdef DEBUG
					printf("Change LED color to BLUE\n");
				#endif
			}

			//*********************Turns on BLUE LED**********************
			past_led_color = led_color;
			GPIOB -> PDOR |= green_LED;
			GPIOB -> PDOR |= red_LED;
			GPIOD -> PDOR &= ~blue_LED;
		}
		else{
			//*********************Turns on ALL the LEDs******************
			GPIOB -> PDOR &= ~red_LED;
			GPIOB -> PDOR &= ~green_LED;
			GPIOD -> PDOR &= ~blue_LED;
		}
		return true;
	}
	else{
		//**********If the LED was high, Toggle it to low*****************
		GPIOB -> PDOR |= red_LED;
		GPIOB -> PDOR |= green_LED;
		GPIOD -> PDOR |= blue_LED;
	}
	return false;
}


void check_Touch()
{
	//***************Checks Scanned Val via polling*******************************
	touch_val = Touch_Poll();
	delay_us(1000);

	//***************Checks if Pressed on the Left********************************
	if((touch_val > RED_LOWER_THRSD) && (touch_val < RED_UPPER_THRSD + offset_R)){
		if(LED_ON_STATUS){
			GPIOB -> PDOR |= green_LED;
			GPIOD -> PDOR |= blue_LED;
			GPIOB -> PDOR &= ~red_LED;
		}
		led_color = RED_LED_ON;
		#ifdef DEBUG
			printf("Touch value is %d\n", touch_val);
		#endif
		offset_R =VAL_OFFSET;
		offset_G =0;
		offset_B =0;
	}

	//***************Checks if Pressed on the Middle******************************
	else if((touch_val >=(RED_UPPER_THRSD-offset_G)) &&
			(touch_val < GREEN_UPPER_THRSD + offset_G)){
		if(LED_ON_STATUS){
			GPIOB -> PDOR |= red_LED;
			GPIOD -> PDOR |= blue_LED;
			GPIOB -> PDOR &= ~green_LED;
		}
		led_color = GREEN_LED_ON;
		offset_G =VAL_OFFSET;
		offset_R =0;
		offset_B =0;
		#ifdef DEBUG
			printf("Touch value is %d\n", touch_val);
		#endif

	}

	//***************Checks if Pressed on the Right*******************************
	else if(touch_val >=(GREEN_UPPER_THRSD - offset_B)){
		if(LED_ON_STATUS){
			GPIOB -> PDOR |= green_LED;
			GPIOB -> PDOR |= red_LED;
			GPIOD -> PDOR &= ~blue_LED;
		}
		led_color = BLUE_LED_ON;
		offset_B = VAL_OFFSET;
		offset_R = 0;
		offset_G =0;
		#ifdef DEBUG
			printf("Touch value is %d\n", touch_val);
		#endif
	 }
}

