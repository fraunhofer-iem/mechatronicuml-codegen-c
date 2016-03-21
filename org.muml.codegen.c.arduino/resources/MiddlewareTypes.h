/*
 * MiddlewareTypes.h
 *
 *  Created on: 11.03.2014
 *      Author: badrobot
 */
/**
 * @file 
 * @author badrobot
 * @brief The data types which are used in the MiddleWare
 * @warning These data types shall be adapted for a specific target platform
 */

#ifndef MIDDLEWARETYPES_H_
#define MIDDLEWARETYPES_H_
#include "standardTypes.h"
#include "customTypes.h"

// If we change defs like "typedef signed long PortID", we have to make sure, what protobuf generates is fitting to this
/**
 * @brief Type to specify the length of a Queue
 */
typedef unsigned short queue_size_t;

/**
 * @brief Type to specify the length of a Buffer
 */
typedef int bufferSize_t; 

/**
 * @brief Type to specify the ID of a Message
 */
typedef int_t MessageID;

/**
 * @brief Type to specify the ID of a Port
 */
typedef int_t PortID;

/**
 * @brief Type to specify the ID of a ECU
 */ 
typedef int_t ECUID;



/*
 typedef struct NetworkMessage{
 PortID targetPort;
 Message * content;
 }NetworkMessage;
 */

 /**
  * @brief  A typedef for our MiddlewareMessage
  * @details Since protobuf doesn't use typedef for its structs, we have to do it here
  * @note This must be considered in the Code-Generation
  * 
  */
typedef struct MiddlewareMessage MiddlewareMessage;

/**
 * @brief Type to specify QoS Properties for Messages
 * @note shall be later used to ensure QoS Properties for Messages
 */
typedef struct QoSProps QoSProps;

/**
 * @brief Type to specify a ECU
 */
typedef int_t ECU;

#endif /* MIDDLEWARETYPES_H_ */
