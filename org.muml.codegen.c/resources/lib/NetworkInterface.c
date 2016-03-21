/*
 * MW_NetworkInterface.c
 *
 *  Created on: 03.03.2014
 *      Author: badrobot
 */


#include "NetworkInterface.h"




/*
 * creates a new NetworkInterface and sets the name
 * will be called by the create-method of the middleware
 */
NetworkInterface* NetworkInterface_create(char* name){
	NetworkInterface* ni = (NetworkInterface*) malloc(sizeof(NetworkInterface));
	ni->name = name;
	return ni;
}


/*
 * initializes a given NetworkInterface.
 * here, the specific send- and receive-method are set.
 */
void NetworkInterface_init(NetworkInterface* ni, bool_t (*init)(void), bool_t (*send)(MiddlewareMessage*), MiddlewareMessage* (*receive)(void)){
	if (ni != NULL){
		ni->initMethod = init;
		ni->sendMethod = send;
		ni->receiveMethod = receive;
	}

}

/*
 * releases a given NI, if needed.
 */
bool_t NetworkInterface_destroy(NetworkInterface* ni){
	if (ni != NULL){
		free(ni);
		return true;
	}else
		return false;
}
