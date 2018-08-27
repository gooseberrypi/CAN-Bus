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

/***************************************************************************************************
 * Set the message ID, currently there is no error checking, future improvements will address this.
 ***************************************************************************************************/
can_packet_manager_status can_pm_set_id(CAN_message_t *packetPtr, uint32_t new_id) {
	packetPtr->id = new_id;
	return can_pm_success;
}

can_packet_manager_status can_pm_generate_message(CAN_message_t *packetPtr, pid_request_t *pid, uint8_t numPids) {
	uint8_t numBytes = 0;

}

STATIC uint8_t get_PID_length(uint16_t pid) {
	return 1U + (pid >> 8 || 0);
}
