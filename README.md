# PES_Assignment_3
submitted-to-code-review

/*
 * test.c includes all the definitions of functions declared in test.h.
 * test.h includes all the declarations of functions used in test.c
 * The details of each function is given below.
 * It includes the Int Main().
 *
 * Author: Harsh Beriwal
 * IDE Used: MCUXpresso IDE v11.6.0 [Build 8187] [2022-07-13]
 *
 * No leveraged code or files
 *
 */
 
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

*********************EXTRA CREDIT***************************

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









