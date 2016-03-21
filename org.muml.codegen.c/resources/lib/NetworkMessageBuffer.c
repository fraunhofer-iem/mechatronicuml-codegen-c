/*
 * MessageBuffer.c
 *
 *  Created on: 13.03.2014
 *      Author: badrobot
 */

#include "NetworkMessageBuffer.h"


NetworkMessageBuffer* NetworkMessageBuffer_create(queue_size_t size, bool_t mode){
	NetworkMessageBuffer* buf = (NetworkMessageBuffer*) malloc(sizeof(NetworkMessageBuffer));
	if (buf != NULL) {
    buf->maxSize = size;
    buf->bufferMode = mode;
	buf->queue = (MiddlewareMessage**) malloc(size * sizeof(MiddlewareMessage*));
	//initialize the new created NetworkMessageBuffer
	NetworkMessageBuffer_initialize(buf);
	}
	else {
			fprintf(stderr, "Creation of Port failed.\n");
		}
	return buf;
}

void NetworkMessageBuffer_initialize(NetworkMessageBuffer* buf){
	buf->currentSize = 0;
	buf->index = 0;
	buf->tail = 0;
}


queue_size_t NetworkMessageBuffer_getSize(NetworkMessageBuffer* buf){
	return buf->currentSize;
}

queue_size_t NetworkMessageBuffer_getMaxSize(NetworkMessageBuffer* buf){
	return buf->maxSize;
}

bool_t NetworkMessageBuffer_enqueue(NetworkMessageBuffer* buf, MiddlewareMessage* msg){

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
	free(msg);
	return false;
}

bool_t NetworkMessageBuffer_doesMessageExists(NetworkMessageBuffer* buf){
	return (buf->currentSize > 0);
}

MiddlewareMessage* NetworkMessageBuffer_dequeue(NetworkMessageBuffer* buf){
	if (buf->currentSize > 0){
		MiddlewareMessage *returnMsg = buf->queue[buf->index];
        
		queue_size_t foo = (++(buf->index)) % (buf->maxSize);
		buf->index = foo;
		(buf->currentSize)--;
		return (returnMsg);
	}
	return NULL;
}

void NetworkMessageBuffer_destroy(NetworkMessageBuffer* buf){
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
