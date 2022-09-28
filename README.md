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

RED for 500 msec, OFF for 100 msec, <br />
GREEN for 500 msec, OFF for 100 msec,<br />
BLUE for 500 msec, OFF for 100 msec<br />
WHITE (that is, RED, GREEN, and BLUE all on) for 100 msec, OFF for 100 msec<br />
WHITE for 100 msec, OFF for 100 MSEC<br />

2. Blinkenlights will then enter an infinite loop where the LED will be flashed using the following 
pattern:

ON for 500 msec, OFF for 500 msec, <br />
ON for 1000 msec, OFF for 500 msec, <br />
ON for 2000 msec, OFF for 500 msec,<br />
ON for 3000 msec, OFF for 500 msec<br />
Go back to the top (e.g., ON for 500 msec...)<br />

3. During the infinite loop, the color when the LED is ON will initially be white. If the user touches the 
capacitive touch slider, the color will change as follows:

User touches Color  <br />
Left side of slider Red<br />
Center of slider Green<br />
Right side of slider Blue<br />

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

  The Main() Function address starts at **0x9FD. **

  Below is the Definition of the Delay() function in the map file 

  .text.delay_us
                0x0000332c       0x26 ./source/delay.o
                0x0000332c                delay_us

  The Delay() function has a Size of **38 bytes. **

2) Show the full disassembly of your delay() function, adding comments to each line to explain the 
functionality.  [+4 points]

           delay_us:
0000332c:   push    {r7, lr}                ; For stack Manipulation. Putting Value in R7 from the Stack pointer <br />
0000332e:   sub     sp, #16                 ; Immediate Value addressing Subtracing 16 from stack pointer<br />
00003330:   add     r7, sp, #0           <br />
00003332:   str     r0, [r7, #4]         <br />
19        	for(int i =0; i<value;i++);  <br />
00003334:   movs    r3, #0                  ; Initialization for variable i in C <br />
00003336:   str     r3, [r7, #12]           ; Store Register with the corresponding offset in the memory  <br />
00003338:   b.n     0x3340 <delay_us+20>    ; unconditional branch. The .N suffix tells the assembler to encode the instruction using 16 bits.<br />
0000333a:   ldr     r3, [r7, #12]           ; Load Register with the <br />
0000333c:   adds    r3, #1                  ; Incrementing 1 to i everytime <br />
0000333e:   str     r3, [r7, #12]           ; Storing the After results every 12 clock cycles <br />
00003340:   ldr     r3, [r7, #12]           ; Loading the register with stored value in the store Register <br />
00003342:   ldr     r2, [r7, #4]            <br />
00003344:   cmp     r2, r3                  ; Comparing if value Variable is equal to the current i count <br />
00003346:   bhi.n   0x333a <delay_us+14>    ; If equal exit, otherwise jump to b.n branch. <br />
20        }<br />

##PEER REVIEW##

Comments for Assignment 3:

1) Seperate files for each aspect of the project i.e. led, touch, etc or wrt functions can be
used instead of writing everything in 2 files i.e. test.c and test.h
It wouldn’t be possible to make these changes at this point, but still just mentioned it
here as an observation

2) PORT masks can be used instead of defining them again (only used at some instances)
As used in the code snippets of White book, particularly for MUX bits

3) Rather than shifting it like (1<<x) each time, a define can be created as shown in White
book
#define Mask(x) (1UL << x)

4) For DEBUG statements, rather than writing it again and again with #ifdef, a log/debug
header can be created to avoid repeated conventions and making the code modular

5) Create functions for toggling leds(individual LEDs) apart from the change_led()function
(as it provides collective operation of the desired output as a whole and not individual) as
individual LED control statements are repeated many times in check_touch() function

##Following Changes were made post the PEER_REVIEW##

1) Seperate Files were made in the project for touch, gpio, system, delay, led, etc. 

2) Not chnaged as I have only initialized port once and not defined again. 

3) Macro was created for all. The one where Left shift is used in the function is because of making the reader understand of the logic. 

4) Didn't make any change. 

5) I had placed Macros and using a led_color variable for making quick changes in the Change_LED function. So, didn't make any changes to the code for this. 

