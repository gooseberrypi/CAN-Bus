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

#define CAN_11Bit
#ifdef CAN_11Bit
#define CAN_BUFFER_SIZE 	8U
#define CAN_EXTENDED_FLAG	0U
#endif

#define DEFAULT_CAN_TIMEOUT 100

typedef struct CAN_message_t {
  uint32_t id; // can identifier
  uint8_t ext; // identifier is extended
  uint8_t len; // length of data
  uint16_t timeout; // milliseconds, zero will disable waiting
  uint8_t buf[CAN_BUFFER_SIZE];
} CAN_message_t;

typedef struct pid_request_t {
	uint16_t pid; // pid request
	uint8_t mode; // mode of the request
	uint8_t pid_len;
}pid_request_t;

typedef struct can_packet_manager {
	CAN_message_t msg;
}can_packet_manager;

typedef enum can_packet_manager_status {
	can_pm_success,
	can_pm_error
} can_packet_manager_status;

can_packet_manager_status can_pm_set_id(CAN_message_t *packetPtr, uint32_t new_id);

can_packet_manager_status can_pm_generate_message(CAN_message_t *packetPtr, uint8_t numPackets, uint8_t mode ,pid_request_t *pidPtr, uint8_t numPids);

#ifdef TEST
uint8_t get_PID_length(uint16_t pid);
void populate_PID_array_length(pid_request_t *pidPtr, uint8_t numPids);
#endif


#endif /* CAN_PACKET_MANAGER_H_ */
