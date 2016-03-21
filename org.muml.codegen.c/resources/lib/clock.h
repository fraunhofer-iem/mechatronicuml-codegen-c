/**
 * @file
 * @author Fraunhofer IPT-EM
 * @brief This file specifies the MessageBuffer, which are contained at the Components
 * @details  The MessageBuffer are used at the Components to store  MiddlewareMessage%s
 */
#ifndef CLOCK_H_
#define CLOCK_H_
#include "../Middleware/OS.h"


#ifdef NXTOSEK
#include "ecrobot_interface.h"
#include <time.h>
typedef long Clock;
#define Clock_getTime(aClock) (  (systick_get_ms() - (aClock)) )

#define Clock_reset(aClock) ((aClock) = systick_get_ms())
#endif /* NXTOSEK */

#ifdef C99
#include <time.h>
typedef long Clock;
#define Clock_getTime(aClock) ( (CLOCKS_PER_SEC == 1000) ? (clock() - (aClock)) : ((clock() - (aClock)) * 1000 / CLOCKS_PER_SEC) )

#define Clock_reset(aClock) ((aClock) = clock())
#endif /* C99 */




#endif /* CLOCK_H_ */
