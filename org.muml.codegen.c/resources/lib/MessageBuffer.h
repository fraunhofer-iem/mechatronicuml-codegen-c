/**
 * @file 
 * @author badrobot
 * @brief This file specifies the MessageBuffer, which are contained at the Components
 * @details  The MessageBuffer are used at the Components to store  MiddlewareMessage%s
 */
#ifndef MESSAGEBUFFER_H_
#define MESSAGEBUFFER_H_


#include "stdlib.h"
#include "stdio.h"
#include "MiddlewareTypes.h"
#include "../types/standardTypes.h"
#include "../types/customTypes.h"
#include "../messages/Messages.h"


/**
 * 
 * @brief A MessageBuffer of a Port
 * @details MessageBuffers are contained at a Port and store received MiddlewareMessages in MessageBuffer::queue
 * 
 */
typedef struct MessageBuffer{
	int_t numberOfSupportedIDs; /**< The number of #MessageID%s which are supported; The length of the Array MessageBuffer::supportedIDs */
	MessageID* supportedIDs; /**< An Array of #MessageID%s which are supported by the MessageBuffer */
    
	MiddlewareMessage** queue; /**< A ring buffer of MiddlewareMessages  */
	queue_size_t maxSize; /**< The maximal Size of the Queue */
	queue_size_t currentSize; /**< The number of currently enqueued MiddlewareMessages; The current Size of the Queue */
	queue_size_t index;  /**< The current Index of the MessageBuffer::queue */
	queue_size_t tail;  /**< The current Tail of the MessageBuffer::queue */
    bool bufferMode;  /**< The mode of a MessageBuffer - false: discard new incoming message; true: replace oldest message*/
}MessageBuffer;


 /**
  * @brief Creates a new MessageBuffer
  * @details Memory for a MessageBuffer and its queue is allocated and the MessageBuffer is initialized
  * 
  * @param size the size of the queue for this MessageBuffer
  * @param mode description
  * @param numberOfIDs the number of IDs which are supported, the size of the Array numberIfIDs
  * @param supportedIDs an Array of IDs which are can be stored in this MessageBuffer
  * @return the pointer to the allocated MessageBuffer
  */
MessageBuffer* MessageBuffer_create(queue_size_t size, bool_t mode, int_t numberOfIDs, MessageID* supportedIDs);


/**
 * @brief Initializes the MessagesBuffer
 * @details This Function initializes the variables of the MessageBuffer
 * 
 * @param buf the MessageBuffer which shall be initialized
 */
void MessageBuffer_initialize(MessageBuffer* buf);


 /**
  * @brief Checks if the MessageBuffer supports the given MessageID
  * 
  * @param buf The MessageBuffer for which shall be checked, if the given MessageID is supported
  * @param msgID The MessageID which shall be checked
  * 
  * @return True, if the buffer supports a given MessageID, otherwise False
  */
bool_t MessageBuffer_containsID(MessageBuffer *buf, MessageID msgID);



 /**
  * @brief Get the current size of a MessageBuffer
  * @details Returns the current number of MiddlewareMessage%s, which are enqueued in a MessageBuffer
  * 
  * @param buf The  MessageBuffer
  * @return MessageBuffer::currentSize
  */
queue_size_t MessageBuffer_getSize(MessageBuffer* buf);


 /**
  * @brief Get the maximum Size of a MessageBuffer
  * @details Returns the number of Messages which can be stored in MessageBuffer::queue
  * 
  * @param buf the specific MessageBuffer
  * @return MessageBuffer::maxSize
  */
queue_size_t MessageBuffer_getMaxSize(MessageBuffer* buf);


 /**
  * @brief Enqueues a new MiddlewareMessage to a MessageBuffer
  * @details  before you enqueue the MiddlewareMessage, make sure that you have checked that this is the correct buffer
  * 
  * @param buf The MessageBuffer to which the MiddlewareMessage shall be enqueued
  * @param msg The MiddlewareMessage which shall be enqueued
  * 
  * @return True, if the MiddlewareMessage could be enqueued, otherwise False
  */
bool_t MessageBuffer_enqueue(MessageBuffer* buf, MiddlewareMessage* msg);


 /**
  * @brief Whether a MessageBuffer contains a MiddlewareMessage with a specific MessageID
  * 
  * @param buf The MessageBuffer
  * @param ID The ID of a MiddlewareMessage for which it shall be checked if suchone exists
  * 
  * @return True, if a MiddlewareMessage with the given MessageID is contained, otherwise False
  */
bool_t MessageBuffer_doesMessageExists(MessageBuffer* buf, MessageID ID);


 /**
  * @brief Dequeues the Head of the MessageBuffer and returns the MiddlewareMessage
  * 
  * @param buf The MessageBuffer
  *
  * @return A pointer to the MiddlewareMessage if one is contained, otherwise NULL
  */
MiddlewareMessage* MessageBuffer_dequeue(MessageBuffer* buf);


 /**
  * @brief Destroys the MessageBuffer
  * @details Destroys the MessageBuffer and all MiddlewareMessage which are contained in MessageBuffer::queue
  * 
  * @param buf The MessageBuffer which shall be destroyed
  */
void MessageBuffer_destroy(MessageBuffer* buf);

#endif /* MESSAGEBUFFER_H_ */
