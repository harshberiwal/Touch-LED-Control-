# PES_Assignment_3
Test Blinking Pattern and Touch Slider 

/*
 * Author: Harsh Beriwal
 * IDE Used: MCUXpresso IDE v11.6.0 [Build 8187] [2022-07-13]
 * Github Link: https://github.com/harshberiwal/PES_Assignment_3
 * No leveraged code or files
 * 
 * test.c includes all the definitions of functions declared in test.h.
 * test.h includes all the declarations of functions used in test.c
 *
 * touch.h includes all the declarations of functions related to Touch.
 * This include Touch_Init() and Touch_Poll()
 *
 * led_sequence.c includes all the definitions of functions declared in
 * led_sequence.h
 * This include startup_sequence() and change_led() and Check_Touch()
 *
 * system.c includes all the definition of initialzing the SysTick
 * This include initialize_Systick()
 *
 * gpio.c includes all the definitions of functions in gpio.h
 * This include gpio_Init()
 * 
 * delay.h includes all the declarations of function related to delay
 * This include delay_us()
 *
 */


1. At program startup, test will “test” the LED by blinking in the following pattern:

RED for 500 msec, OFF for 100 msec, 
GREEN for 500 msec, OFF for 100 msec,
BLUE for 500 msec, OFF for 100 msec
WHITE (that is, RED, GREEN, and BLUE all on) for 100 msec, OFF for 100 msec
WHITE for 100 msec, OFF for 100 MSEC

2. Blinkenlights will then enter an infinite loop where the LED will be flashed using the following 
pattern:

ON for 500 msec, OFF for 500 msec, 
ON for 1000 msec, OFF for 500 msec,
ON for 2000 msec, OFF for 500 msec,
ON for 3000 msec, OFF for 500 msec
Go back to the top (e.g., ON for 500 msec...)

3. During the infinite loop, the color when the LED is ON will initially be white. If the user touches the 
capacitive touch slider, the color will change as follows:

User touches Color
Left side of slider Red
Center of slider Green
Right side of slider Blue
(There is no way to get back to white after touching the slider.) 
The test poll the touch slider at least once every 100 msec. If the LED is on 
when a touch is detected, the light color should change immediately.

4. The code has two build targets, DEBUG and RUN. The LED and touch behavior will be the 
same under both targets; however, the DEBUG target will additionally cause the following debug 
output (via printf) to a serial console:

 CHANGE LED TO RED, etc. for changes to the LED color
 SLIDER VALUE 87 for changes to the slider value including showing the value read1
 START TIMER 2000 for starting a 2000 mSec delay


## Below are all the Functions Used ##

 *
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

##EXTRA CREDIT##

1) What is the address of your main() function, and what is the size in bytes of your delay() function?  

The Main() Function address starts at 0x535. 

Below is the Definition of the Delay() function in the map file 

.text.delay_us
                0x00003670       0x26 ./source/test.o
                0x00003670                delay_us

The Delay() function has a Size of 38 bytes. 

2) Show the full disassembly of your delay() function, adding comments to each line to explain the 
functionality.  [+4 points]

delay_us(1000); 

00000992:   movs    r3, #250        ; 0xfa (250 Decimal) to the R3 register 
00000994:   lsls    r3, r3, #2      ; Left shifted twice to get the Required Count 
00000996:   movs    r0, r3          ; Copied the Same value from R3 to the Accumulator 
