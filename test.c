/*
 * test.c includes all the definitions of functions declared in test.h.
 * It includes the Int Main().
 *
 * Author: Harsh Beriwal
 * IDE Used: MCUXpresso IDE v11.6.0 [Build 8187] [2022-07-13]
 *
 * No leveraged code or files
 *
 */

#include "test.h"

int main(void) {

    /* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
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
					printf("START TIMER of %d00 ms\n", arr[index]);
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


void gpio_init()
{
	//****************Turning on Clock for GPIOs**************************
	SIM -> SCGC5 |= PORT_A;
	SIM -> SCGC5 |= PORT_B;

	//****************Configuring Pins as GPIO****************************
	PORTB -> PCR[RED] = (uint32_t)(0x00000100);
	PORTB -> PCR[GREEN] = (uint32_t)(0x00000100);
	PORTD -> PCR[BLUE]= (uint32_t)(0x00000100);

	//****************Configuring Pins as output**************************
	GPIOB -> PDDR |= red_LED;
	GPIOB -> PDDR |= green_LED;
	GPIOD -> PDDR |= blue_LED;

	//****************Initializing Pins to Low****************************
	GPIOB -> PDOR |= red_LED;
	GPIOB -> PDOR |= green_LED;
	GPIOD -> PDOR |= blue_LED;
}


void startup_sequence()
{
	#ifdef DEBUG
		printf("Displaying Initial Sequence...\n");
	#endif

	//****************Starting with Red Led on****************************
	led_color = initial_sequence[index];
	LED_ON_STATUS = change_LED();

	//*************Looping until the sequence is complete*****************
	while(index<9)
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
	led_color = 248;
	index =0;
	count =0;
}


bool change_LED(){

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


void delay_us(uint32_t value)
{
	//***********Iterate here until the intended value is reached*******************
	for(int i =0; i<value;i++);
}


void Touch_Init()
{
    //***************Enable clock for TSI PortB 16 and 17***************************
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
    SIM->SCGC5 |= SIM_SCGC5_TSI_MASK;

    //Setting End of Scan Flag, RefChrg as 8uA, ExtChrg as 64uA
    //and 11 as the number of Electrodes
    TSI0->GENCS |= (TSI_GENCS_ESOR_MASK | TSI_GENCS_REFCHRG(OSC_PRESCALER)
    				| TSI_GENCS_EXTCHRG(ELEC_CHARGE) | TSI_GENCS_PS(OSC_PRESCALER)
					| TSI_GENCS_NSCN(ELECTRODES)     | TSI_GENCS_TSIIEN_MASK
                    | TSI_GENCS_STPE_MASK);

    //***************************Enabling the TSI Sensor****************************
    TSI0->GENCS |= TSI_GENCS_TSIEN_MASK;

}

int Touch_Poll(void)
{
    int scanned_val;
    TSI0->DATA =  TSI_DATA_TSICH(10u); // Using channel 10 of The TSI
    TSI0->DATA |= TSI_DATA_SWTS_MASK; // Triggering to scan the value
    scanned_val = (uint16_t)((TSI0 -> DATA) & (0xffff));
    TSI0->GENCS |= TSI_GENCS_EOSF_MASK; // EOSF flag set after getting the value
    return scanned_val;
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

	//***************Checks if Pressed on the Middle********************************
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

	//***************Checks if Pressed on the Right********************************
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


void initialize_SysTick(){

	//************Initialize System Timer with the Required Ticks of 4.8 MHz********
	SysTick->LOAD = TICKS;
	SysTick->VAL  = TICKS;
	SysTick->CTRL = 0b0101;
}








