/**
 * @file
 * @author MUML
 * @brief In this files the data types which are used in the generated Code are defined
 * @warning These types shall be adapted for a specific target platform
 */
#ifndef TYPES_H_
#define TYPES_H_


//define NULL
#define NULL 0
//typedef unsigned short ushort_t;


/**
 * @brief Type to specify a signed Integer
 */
typedef int int_t;

/**
 * @brief Type to specify a signed Integer (8 bit)
 */
typedef short int8_T;
/**
 * @brief Type to specify a signed Integer (16 bit)
 */
typedef int int16_T;
/**
 * @brief Type to specify a signed Integer (32 bit)
 */
typedef long int32_T;
/**
 * @brief Type to specify a signed Integer (64 bit)
 */
typedef long long int64_T;

/**
 * @brief Type to specify an unsigned Integer (8 bit)
 */
typedef unsigned short uint8_T;
/**
 * @brief Type to specify an unsigned Integer (16 bit)
 */
typedef unsigned int uint16_T;
/**
 * @brief Type to specify an unsigned Integer (32 bit)
 */
typedef unsigned long uint32_T;
/**
 * @brief Type to specify an unsigned Integer (64 bit)
 */
typedef unsigned long long uint64_T;


/**
 * @brief Type to specify a Double
 */
typedef double double_T;

/**
 * @brief Type to specify a Boolean Value
 */
#include <stdbool.h>
#ifndef _STDBOOL_H
#define bool	_Bool
#define true	1
#define false	0
#endif
typedef bool bool_T;
typedef bool bool_t;

#endif /* TYPES_H_ */
