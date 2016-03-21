/*********************************************************************************
 * Copyright (c) 2012 Solunar GmbH and others.
 * All rights reserved.
 *
 * Contributors:
 *     Solunar GmbH and others - initial API and implementation
 *******************************************************************************/
/**
 * @file
 * @author Solunar
 * @brief This file specifies how Clocks are read for a specific Target Platform
 * @details The function to read and set Clocks are defined as Preprocessor MACROS
 * @warning This needs to be adapted for specific Target Platforms
 */
#ifndef CLOCK_H_
#define CLOCK_H_
#include "OS.h"




#ifdef ARDUINO
unsigned long millis(void);
typedef long Clock;
#define Clock_getTime(aClock) (  (millis() - (aClock)) )

#define Clock_reset(aClock) ((aClock) = millis())
#endif /* C99 */


#endif /* CLOCK_H_ */
