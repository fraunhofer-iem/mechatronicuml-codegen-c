/*
 * Debug.c
 *
 *  Created on: 15.06.2015
 *      Author: badrobot
 */

#include "Debug.h"
 

void printDebugInformation(char * debugInformation){

	printf("%lu : %s\n",clock(),debugInformation);
	fflush(stdout);
}
