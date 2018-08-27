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

typedef struct CAN_message_t {
  uint32_t id; // can identifier
  uint8_t ext; // identifier is extended
  uint8_t len; // length of data
  uint16_t timeout; // milliseconds, zero will disable waiting
  uint8_t buf[8];
} CAN_message_t;

typedef struct pid_request_t {
	uint16_t pid; // pid request
	uint8_t mode; // mode of the request
}pid_request_t;

typedef enum can_packet_manager_status {
	can_pm_success,
	can_pm_error
} can_packet_manager_status;

can_packet_manager_status can_pm_set_id(CAN_message_t *packetPtr, uint32_t new_id);

can_packet_manager_status can_pm_generate_message(CAN_message_t *packetPtr, pid_request_t *pid, uint8_t numPids);

#ifdef TEST
uint8_t get_PID_length(uint16_t pid);
#endif


#endif /* CAN_PACKET_MANAGER_H_ */
