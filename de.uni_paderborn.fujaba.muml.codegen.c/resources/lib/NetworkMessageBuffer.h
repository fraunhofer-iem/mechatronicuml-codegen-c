/**
 * @file 
 * @author badrobot
 * @brief A NetworkMessageBuffer is used to store MiddlewareMessages
 * @details The NetworkMessageBuffer%s are used to enqueue and dequeue #MiddlewareMessage%s which are received via #NetworkInterface%s or shall be sent via them
 *          A NetworkMessageBuffer is used in the Middleware
 */
#ifndef NETWORKMESSAGEBUFFER_H_
#define NETWORKMESSAGEBUFFER_H_

#include "stdlib.h"
#include "stdio.h"
#include "MiddlewareTypes.h"
#include "../types/standardTypes.h"
#include "../types/customTypes.h"
#include "../messages/Messages.h"

/**
 * 
 * @brief A Buffer for #MiddlewareMessage%s, which are received via #NetworkInterface%s
 * @details A NetworkMessageBuffer is contained in the Middleware and contains a queue in which the #MiddlewareMessage%s are stored
 */
typedef struct NetworkMessageBuffer{
	MiddlewareMessage** queue; /**< The Queue which stores the MiddlewareMessage%s */
	queue_size_t maxSize; /**< The maximum Size of the Queue */
	queue_size_t currentSize; /**< The current Size of the Queue; the Number of currently stored MiddlewareMessages */
	queue_size_t index; /**< The current Index of the Queue */
	queue_size_t tail; /**< The current Tail of the Queue */
	bool_t bufferMode; /**< The mode of a NetworkMessageBuffer */
} NetworkMessageBuffer;


 /**
  * @brief Creates a new NetworkMessageBuffer
  * @details Memory for a NetworkMessageBuffer and its queue is allocated and the NetworkMessageBuffer is initialized
  * 
  * @param size The size of the queue for the NetworkMessageBuffer
  *
  * @return The Pointer to created NetworkMessageBuffer
  */
NetworkMessageBuffer* NetworkMessageBuffer_create(queue_size_t size, bool_t mode);


/**
 * @brief Initializes the NetworkMessageBuffer
 * @details This Function initializes the members of the struct NetworkMessageBuffer
 * 
 * @param buf The NetworkMessageBuffer which shall be initialized
 */
void NetworkMessageBuffer_initialize(NetworkMessageBuffer* buf);



/**
 * @brief Get the current Size of a NetworkMessageBuffer
 * @details Returns the current number of MiddlewareMessage%s which are enqued in the NetworkMessageBuffer
 * 
 * @param buf The NetworkMessageBuffer
 * @return NetworkMessageBuffer::currentSize
 */
queue_size_t NetworkMessageBuffer_getSize(NetworkMessageBuffer* buf);

/*
 * returns the maximum size of the message buffer aka the buffer size
 */
/**
 * @brief Get the maximum Size of a NetworkMessageBuffer
 * @details Returs the maximum number of MiddlewareMessage%s which can be stored in the NetworkMessageBuffer::queue
 * 
 * @param buf The NetworkMessageBuffer
 * @return NetworkMessageBuffer::maxSize
 */
queue_size_t NetworkMessageBuffer_getMaxSize(NetworkMessageBuffer* buf);


/**
 * @brief Enqueues a new MiddlewareMessage to a NetworkMessageBuffer
 * @details Before you enqueue the MiddlewareMessage, make sure that you have checked that this is the correct buffer
 * 
 * @param buf The NetworkMessageBuffer to which the MiddlewareMessage shall be enqueued
 * @param msg The MiddlewareMessage to be enqueued
 * 
 * @return True, iff the MiddlewareMessage could be enqueued, otherwise False
 */
bool_t NetworkMessageBuffer_enqueue(NetworkMessageBuffer* buf, MiddlewareMessage* msg);


/**
 * @brief Whether a NetworkMessageBuffer contains a MiddlewareMessage
 * 
 * @param buf The NetworkMessageBuffer which shall be checked
 * @return True, if a MiddlewareMessage is contained in the NetworkMessageBuffer, otherwise False
 */
bool_t NetworkMessageBuffer_doesMessageExists(NetworkMessageBuffer* buf);


/**
 * @brief Dequeues the Head of the NetworkMessageBuffer and returns a MiddlewareMessage
 * 
 * @param buf The NetworkMessageBuffer
 * @return A Pointer to the MiddlewareMessage, if one exists, otherwise Null
 */
MiddlewareMessage* NetworkMessageBuffer_dequeue(NetworkMessageBuffer* buf);


/**
 * @brief Destroy a NetworkMessageBuffer
 * 
 * @param buf The NetworkMessageBuffer which shall be destroyed
 */
void NetworkMessageBuffer_destroy(NetworkMessageBuffer* buf);

#endif /* NETWORKMESSAGEBUFFER_H_ */
