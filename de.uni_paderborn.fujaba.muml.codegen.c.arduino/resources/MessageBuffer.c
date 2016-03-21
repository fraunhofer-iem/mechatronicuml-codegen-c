/*
 * MessageBuffer.c
 *
 *  Created on: 13.03.2014
 *      Author: badrobot
 */

#include "MessageBuffer.h"
 

MessageBuffer* MessageBuffer_create(queue_size_t size, bool_t mode,
		int_t numberOfIDs, MessageID* supportedIDs) {
	MessageBuffer* buf = (MessageBuffer*) calloc(1, sizeof(MessageBuffer));
	if (buf != NULL) {
	buf->maxSize = size;
	buf->numberOfSupportedIDs = numberOfIDs;
	buf->supportedIDs = supportedIDs;
	buf->bufferMode = mode;
	buf->queue = (MiddlewareMessage**) calloc(size, sizeof(MiddlewareMessage*));
	//initialize the new created MessageBuffer
	MessageBuffer_initialize(buf);
	} else {
		printDebugInformation("Creation of buffer failed.\n");
	}

	return buf;
}

void MessageBuffer_initialize(MessageBuffer* buf) {
	buf->currentSize = 0;
	buf->index = 0;
	buf->tail = 0;
}

bool_t MessageBuffer_containsID(MessageBuffer *buf, MessageID msgID) {
	int_t i = 0;
	for (i = 0; i < buf->numberOfSupportedIDs; i++) {
		if ((MessageID) (buf->supportedIDs[i]) == msgID) {

			//awesome, we are supporting the given msgID
			return true;
		}
	}
	//this buffer cannot handle the given msgID
	return false;
}

queue_size_t MessageBuffer_getSize(MessageBuffer* buf) {
	return buf->currentSize;
}

queue_size_t MessageBuffer_getMaxSize(MessageBuffer* buf) {
	return buf->maxSize;
}

bool_t MessageBuffer_enqueue(MessageBuffer* buf, MiddlewareMessage* msg) {
	if (MessageBuffer_containsID(buf, (MessageID) msg->_msgID)) {
		if (buf->currentSize < buf->maxSize) {
			buf->queue[buf->tail] = msg;
			queue_size_t foo = (++(buf->tail)) % (buf->maxSize);
			buf->tail = foo;
			++(buf->currentSize);
			return true;
		} else if (buf->bufferMode) {

			free(buf->queue[buf->tail]);
			buf->queue[buf->tail] = msg;
			queue_size_t foo = (++(buf->tail)) % (buf->maxSize);
			queue_size_t bar = (++(buf->index)) % (buf->maxSize);
			buf->tail = foo;
			buf->index = bar;
			return true;
		}
	}
	free(msg);
	return false;

}

bool_t MessageBuffer_doesMessageExists(MessageBuffer* buf, MessageID msgID) {
	if (buf->currentSize > 0) {
		return ((MessageID) buf->queue[buf->index]->_msgID == msgID);
	}
	return false;
}

MiddlewareMessage* MessageBuffer_dequeue(MessageBuffer* buf) {
	if (buf->currentSize > 0) {
		MiddlewareMessage *returnMsg = buf->queue[buf->index];
		(buf->queue)[buf->index] = NULL;
		queue_size_t foo = (++(buf->index)) % (buf->maxSize);
		buf->index = foo;
		(buf->currentSize)--;
		return (returnMsg);
	}
	return NULL;
}

void MessageBuffer_destroy(MessageBuffer* buf) {
	if (buf != NULL) {
			//free the memory of the messages which are contained in this buffer
		while (buf->currentSize > 0) {
				MiddlewareMessage *returnMsg = buf->queue[buf->index];
				(buf->queue)[buf->index] = NULL;
				queue_size_t foo = (++(buf->index)) % (buf->maxSize);
				buf->index = foo;
				(buf->currentSize)--;
				free(returnMsg);
			}
			//free the memory of the MessageBuffer
			free(buf);
		}
}
