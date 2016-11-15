/**
 * @file
 * @author Fraunhofer IPT-EM
 * @brief This file specifies the MessageBuffer, which are contained at the Components
 * @details  The MessageBuffer are used at the Components to store  MiddlewareMessage%s
 */
#ifndef CLOCK_H_
#define CLOCK_H_
//#include "../Middleware/OS.h"


#ifdef NXTOSEK
#include "ecrobot_interface.h"
#include <time.h>
typedef long Clock;
#define Clock_getTime(aClock) (  (systick_get_ms() - (aClock)) )
#define Clock_reset(aClock) ((aClock) = systick_get_ms())
#endif /* NXTOSEK */

#ifdef C99
#include <time.h>
#include <stdint.h>
typedef uint64_t Clock;
static inline Clock Clock_getTime2(Clock aClock) {
	struct timespec spec;
    clock_gettime(CLOCK_REALTIME, &spec);
	return spec.tv_sec * 1000 + (spec.tv_nsec / 1.0e6) - aClock;
}
static inline void Clock_reset2(Clock* clock) { *clock = Clock_getTime2(0); }


#define Clock_getTime(aClock) Clock_getTime2(aClock)
#define Clock_reset(aClock) Clock_reset2(&aClock)


#endif /* C99 */


#endif /* CLOCK_H_ */
