/**
 * @file 
 * @author [author]
 * @brief The NetworkInterfaces to send MiddlewareMessages, e.g., Wifi, Cable
 * @details  A NetworkInterface serves as an Interface (programmaticaly) for all Kinds of Network-Devices.
 *          A NetworkInterface is used as a general Interface to send/receive #MiddlewareMessage%s  via the Middleware. 
 * @warning
 *  Developers have to implement a NetworkInterface for each Network Device manually.
 */
#ifndef MW_NETWORKINTERFACE_H_
#define MW_NETWORKINTERFACE_H_
#include "MiddlewareTypes.h"
#include "stdlib.h"

/**
 * 
 * @brief An Interface for Network/Interfaces/Devices
 * @details This struct serves as an Interface for all Kinds of Network-Devices. This interface is used to send MiddlewareMessages to other ECUs. Thus the function pointers are called during the execution of the Middleware
 *      
 */
typedef struct NetworkInterface{
	char* name; /**< The name of this NetworkInterace */
	bool (*initMethod)(void); /**< A function pointer to an initFunction of a specific NetworkInterface */
	bool (*sendMethod)(MiddlewareMessage*); /**< A function pointer to a send Function of a NetworkInterace which takes a MiddlewareMessage as a parameter */
	MiddlewareMessage* (*receiveMethod)(void); /**< A function pointer to a receive Function of a NetworkInterface which returns a MiddlewareMessage */
} NetworkInterface;

/**
 * @brief The generall create Function for all NetworkInterface
 * @details Memory for the struct NetworkInterface is created and initialized with the given name
 * 
 * @param name The name as an String for the NetworkInterface
 * @return A Pointer to the new created NetworkInterface
 */
NetworkInterface* NetworkInterface_create(char *name);

/**
 * @brief The init Function for #NetworkInterface%s
 * 
 * @param ni The NetworkInterface to be initialized
 * @param init A function pointer to an implementation of the init Function for a specific Network-Device
 * @param send A function pointer to an implementation of the send Function for a specific Network-Device
 * @param receive A function pointer to an implementation of the receive Function for a specific Network-Device
 */
void NetworkInterface_init(NetworkInterface* ni, bool_t (*init)(void), bool_t (*send)(MiddlewareMessage*), MiddlewareMessage* (*receive)(void));

/**
 * @brief Destroys a NetworkInterface and free its Memory
 * 
 * @param ni The NetworkInterface to be destroyed
 * @return 0, if the NetworkInterface is successfully destroyed, otherwise 0
 */
bool_t NetworkInterface_destroy(NetworkInterface* ni);
#endif /* MW_NETWORKINTERFACE_H_ */
