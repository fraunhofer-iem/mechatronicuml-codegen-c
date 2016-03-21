/*
 * port.c
 *
 *  Created on: 13.03.2014
 *      Author: badrobot
 */

#include "port.h"


Port* Port_create(PortID id, int_t numberOfBuffers, MessageBuffer** msgBuffer) {
	//alloc mem for the port
	Port* port = (Port*) calloc(1, sizeof(Port));
	if (port != NULL) {
	//set ID
	port->ID = id;

	//alloc space for messageBuffers
	if (numberOfBuffers > 0) {
		port->numberOfIncomingBuffer = numberOfBuffers;
		port->allMessageBuffers = msgBuffer;
	}

		Port_initialize(port);
	} else {
		printDebugInformation("Creation of Port failed.\n");
	}

	return port;
}

void Port_initialize(Port * port) {
	//do some init stuff

}

bool_t Port_addMessage(Port* port, MiddlewareMessage* msg) {
	//get messageBuffer for the given message
	MessageBuffer* buf = Port_getMessageBuffer(port, (MessageID) msg->_msgID);
	//add message to buffer
	if (buf != NULL) {
		if (MessageBuffer_enqueue(buf, msg)) {
			return true;
		}
		//printf("buffer of port %d received msg of type %d\n", (int) port->ID,(int) msg->_msgID);
	}
	//on error: return failure

	return false;
}

MessageBuffer * Port_getMessageBuffer(Port * port, MessageID msgID) {
	int_t i = 0;
	for (i = 0; i < port->numberOfIncomingBuffer; i++) {
		if (MessageBuffer_containsID(port->allMessageBuffers[i], msgID)) {
			return port->allMessageBuffers[i];
		}
	}
	return NULL;
}

bool_t Port_doesMessageExist(Port * port, MessageID msgID) {
	MessageBuffer* buffer = Port_getMessageBuffer(port, msgID);
	if (buffer != 0) {

		if (MessageBuffer_doesMessageExists(buffer,msgID)) {
			return true;
		}


	}
	return false;
}

MiddlewareMessage* Port_receiveMessage(Port * port, MessageID msgID) {
	MessageBuffer* buffer = Port_getMessageBuffer(port, msgID);
	if (buffer) {
		return MessageBuffer_dequeue(buffer);
	}
	return NULL;
}

void Port_destroy(Port * port) {
	if (port != NULL) {
		int_t i = 0;
		// free all message buffers of this port
		for (i = 0; i < port->numberOfIncomingBuffer; i++) {
			if (port->allMessageBuffers[i] != NULL) {
				MessageBuffer_destroy(port->allMessageBuffers[i]);
			}
		}

		free(port);
	}

}
