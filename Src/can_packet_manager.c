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
    #define Static
#else
    #define Static static
#endif

Static void nextByte(CAN_message_t *packetPtr, uint8_t numPackets);

/***************************************************************************************************
* Determine if the PID is 1 byte long or 2 bytes long. By assuming that a leading 0x00 is empty
* data.
***************************************************************************************************/
Static uint8_t get_PID_length(uint16_t pid) {
	if (pid > 0x0000) {
		return 1U + (pid >> 8 || 0);
	} else {
		return 0;
	}
}

Static void populate_PID_array_length(pid_request_t *pidPtr, uint8_t numPids) {
	for(uint8_t i = 0; i < numPids; i++)
	{
		pidPtr[i].pid_len = get_PID_length(pidPtr[i].pid);
	}
}


Static void init_CAN_message_t (CAN_message_t *CAN_mssg)
{
	CAN_mssg->ext	= CAN_EXTENDED_FLAG;
	CAN_mssg->id	= 0x7E0;
	CAN_mssg->len	= CAN_BUFFER_SIZE;

	CAN_mssg->timeout = DEFAULT_CAN_TIMEOUT;

	for(uint8_t i = 0; i < CAN_BUFFER_SIZE; i++)
	{
		CAN_mssg->buf[i] = 0x00;
	}
}

/***************************************************************************************************
* Set the message ID, currently there is no error checking, future improvements will address this.
***************************************************************************************************/
can_packet_manager_status can_pm_set_id(CAN_message_t *packetPtr, uint32_t new_id) {
	packetPtr->id = new_id;
	return can_pm_success;
}

can_packet_manager_status can_pm_generate_message(CAN_message_t *packetPtr, uint8_t numPackets, uint8_t mode ,pid_request_t *pidPtr, uint8_t numPids) {
	uint8_t numBytes = 1; //+1 for Mode
	uint8_t pidCount = 0;
	uint8_t curBtye = 0;
	uint8_t frame = 0;

	/*************************************************************************
	 * Parse through the PID array and determine the length of each PID.
	 * Populate the PID length in each typedef.
	 *************************************************************************/
	populate_PID_array_length(pidPtr, numPids);

	/*************************************************************************
	 * Parse through the PID array and count the number of bytes that are
	 * required for the packet request.
	 *************************************************************************/
	for(uint8_t i = 0; i < numPids; i++)
	{
		numBytes += pidPtr[i].pid_len;
	}

	/*************************************************************************
	 * Parse through each packet and initialize it to the determined header,
	 * CAN bus mode and fill the packet buffer with 0x00.
	 *************************************************************************/
	for(uint8_t i = 0; i < numPackets; i++)
	{
		init_CAN_message_t(&packetPtr[i]);
	}

	/*************************************************************************
	 * Determine if this will be a single frame request or multiframe
	 * request. This is directly related to the number of bytes in the packet
	 * and the size of the buffer.
	 *************************************************************************/
	if(numBytes < (CAN_BUFFER_SIZE - 1U)) // -1 for length byte
	{
		/*************** Length ***************/
		packetPtr[0].buf[curBtye++] = numBytes;

		/**************** Mode ****************/
		packetPtr[0].buf[curBtye++] = mode;
	}
	else  // Multi frame
	{
		/**************** Frame ****************/
		packetPtr[0].buf[curBtye++] = (frame | 0x10);

		/*************** Length ***************/
		packetPtr[0].buf[curBtye++] = numBytes;

		/**************** Mode ****************/
		packetPtr[0].buf[curBtye++] = mode;
	}

	/*************************************************************************
	 * Iterate through every single PID and fill the buffer.
	 *************************************************************************/
	for(pidCount = 0; pidCount < numPids; pidCount++)
	{
		if(pidPtr[pidCount].pid_len == 1)
		{
			/**************** PID byte 1 ****************/
			packetPtr[frame].buf[curBtye++] = pidPtr[pidCount].pid;
		}
		else if(pidPtr[pidCount].pid_len == 2)
		{
			/**************** PID byte 1 ****************/
			packetPtr[frame].buf[curBtye++] = ((pidPtr[pidCount].pid) >> 8U) & 0xFF;

			/**************** PID byte 2 ****************/
			packetPtr[frame].buf[curBtye++] = (pidPtr[pidCount].pid) & 0xFF;
		} else {
		}
	}
	return can_pm_success;
}

Static void nextByte(CAN_message_t *packetPtr, uint8_t numPackets)
{

}

