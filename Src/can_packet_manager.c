/*
 * can_packet_manager.c
 *
 *  Created on: Aug 16, 2018
 *      Author: mkaiser
 */

#include "can_packet_manager.h"

#ifdef STM32F446xx
#include "stm32f4xx_hal.h"
#endif

#ifdef TEST
    #define STATIC
#else
    #define STATIC static
#endif

STATIC uint8_t get_PID_length(uint16_t pid) {
	return 1U + (pid >> 8 || 0);
}
