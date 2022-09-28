/*
 * delay.h includes all the declarations of function related to delay
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

#ifndef DELAY_H_
#define DELAY_H_

#include <stdint.h>

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


#endif /* DELAY_H_ */
