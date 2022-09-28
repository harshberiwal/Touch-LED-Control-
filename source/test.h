/*
 * test.h includes all the declarations of functions used in test.c
 * The details of each function is given below.
 *
 * Author: Harsh Beriwal
 * IDE Used: MCUXpresso IDE v11.6.0 [Build 8187] [2022-07-13]
 *
 * Github Link: https://github.com/harshberiwal/PES_Assignment_3
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
#include "touch.h"
#include "system.h"
#include "led_sequence.h"
#include "gpio.h"

extern bool LED_ON_STATUS;
extern int count;
extern uint8_t arr[];
extern int index;

#endif /* TEST_H_ */







