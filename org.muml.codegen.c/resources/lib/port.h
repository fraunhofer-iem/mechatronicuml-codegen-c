/**
 * @file 
 * @author badrobot
 * @brief The Ports of ComponentInstances
 * @details  In MechatronicUML this correspond to the PortInstance of a Component-Instance.
 *       Since the Codegen-model does only contain discretePorts, we do not need to provide
 *      an implementation of hybrid, continuous or delegation ports.
 */
#ifndef PORT_H_
#define PORT_H_

#include "stdlib.h"
#include "MessageBuffer.h"
#include "../types/standardTypes.h"
#include "../types/customTypes.h"
#include "MiddlewareTypes.h"

/**
 * @brief The structure Port
 * @details A Port is contained at an Instance of a Component and has some #MessageBuffer%s to store incoming Messages.
 * 			Furthermore, a Port has an unique ID which is used to identify the Port
 * @note 	The PortID is not only unique for one ECU, but for all ECUs, it serves as an unique address
 */
typedef struct Port {
	PortID ID; /**< the ID of this Port, the ID of a Port is used to identify targetPorts for receiving/sending of Messages */
	int_t numberOfIncomingBuffer; /**< The number of #MessageBuffer%s which are associated to a Port  */
	MessageBuffer** allMessageBuffers; /**< The #MessageBuffer%s of a Port */
}Port;


 /**
  * @brief Creates a new Port
  * @details Allocates memory for a Port and initializes it
  * @todo is this correct? for every needed MessageBuffer(pointer)
  * 
  * @param id the PortID of this Port, to identify it
  * @param numberOfBuffers the number of #MessageBuffer%s to be associated with this Port
  * @param msgBuffer the #MessageBuffer%s to be associated with this Port
  * @return A Pointer to the new created Port
  */
Port* Port_create(PortID id, int_t numberOfBuffers, MessageBuffer** msgBuffer);



 /**
  * @brief Initializes the Port and all Buffers
  * @details The members of the struct Port are initialized
  * 
  * @param port The Port to be initialized
  */
void Port_initialize(Port * port);


 /**
  * @brief Adds a given MiddlewareMessage to the correct MessageBuffer
  * 
  * @param port The Port to which the MiddlewareMessage shall be added
  * @param msg The MiddlewareMessage which shall be enqueued
  * 
  * @return True, if the MiddlewareMessage could be successfully enqueued, otherwise False
  */
bool_t Port_addMessage(Port* port, MiddlewareMessage* msg);


 /**
  * @brief Get the MessageBuffer for a specific MessageID
  * 
  * @param port The Port which MessageBuffer shall be returned
  * @param msgID The MessageID
  * 
  * @return A Pointer to the corresponding MessageBuffer, if one exists, otherwise NULL
  */
MessageBuffer * Port_getMessageBuffer(Port * port, MessageID msgID);


/**
 * @brief Checks, if there exists a received MiddlewareMessage with the given MessageID in the corresponding MessageBuffer
 * 
 * @param port The Port for the contained MiddlewareMessages shall be checked
 * @param msgID The MessageID
 * 
 * @return True, if a MiddlewareMessage with the given MessageID exists, otherwise False
 */
bool_t Port_doesMessageExist(Port * port, MessageID msgID);


/**
 * @brief Get a MiddlewareMessage with the given MessageID and removes it from the MessageBuffer
 * 
 * @param port The Port which stores the MiddlewareMessage in one of its MessageBuffer%s
 * @param msgID The MessageID of the MiddlewareMessage, which shall be returned
 * 
 * @return The MiddlewareMessage with the given MessageID, if none exists NULL is returned
 * @warning Before you call this method, you definitively should call Port_doesMessageExists()
 */
MiddlewareMessage* Port_receiveMessage(Port * port, MessageID msgID);


/**
 * @brief Destroys the Port
 * @details Frees the Memory which is reserved for the struct Port
 * 
 * @param port The Port which shall be destroyed
 */
void Port_destroy(Port * port);

#endif /* PORT_H_ */
