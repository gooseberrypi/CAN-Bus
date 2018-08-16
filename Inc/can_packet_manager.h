/*
 * can_packet_manager.h
 *
 *  Created on: Aug 16, 2018
 *      Author: mkaiser
 */

#ifndef CAN_PACKET_MANAGER_H_
#define CAN_PACKET_MANAGER_H_

#ifdef STM32F446xx
#include "stm32f4xx_hal.h"
#endif

#ifdef TEST
uint8_t get_PID_length(uint16_t pid);
#endif


#endif /* CAN_PACKET_MANAGER_H_ */
