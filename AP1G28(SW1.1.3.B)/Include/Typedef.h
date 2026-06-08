/*
 * Typedef.h
 *
 *  Created on: 2017��12��20��
 *      Author: jacksom
 */

#ifndef TYPEDEF_H_
#define TYPEDEF_H_

#ifndef FALSE
   #define FALSE  0u
#endif
#ifndef TRUE
   #define TRUE  1u
#endif
#ifndef FAR
#define FAR
#endif
#define Zero       0u
#define One	       1u
#define Two        2u
#define Three      3u
#define Four       4u




#ifndef CAEA_ON
	#define CAEA_ON    1U
#endif

#ifndef CAEA_OFF
	#define CAEA_OFF    0U
#endif

#ifndef CAEA_TRUE
#define CAEA_TRUE    1U
#endif

#ifndef CAEA_FALSE
	#define CAEA_FALSE    0U
#endif

#ifndef CAEA_HIGH
	#define CAEA_HIGH    1U
#endif

#ifndef CAEA_LOW
	#define CAEA_LOW    0U
#endif

#ifndef CAEA_ACTIVE
	#define CAEA_ACTIVE    1U
#endif

#ifndef CAEA_INACTIVE
	#define CAEA_INACTIVE    0U
#endif

#ifndef CAEA_VALID
	#define CAEA_VALID    1U
#endif

#ifndef CAEA_INVALID
	#define CAEA_INVALID    0U
#endif

#ifndef CAEA_NULL
	#define CAEA_NULL    0U
#endif

/* NULL_PTR define with a void pointer to zero definition*/
#ifndef CAEA_NULL_PTR
	#define CAEA_NULL_PTR  ((void *)0)
#endif
/*Port*/


/*General*/
typedef unsigned char uint8;
typedef signed char int8;
typedef unsigned short int uint16;
typedef short int int16;
typedef short int sint16;
typedef unsigned long int uint32;
typedef long int int32;
typedef unsigned char       boolean; /*                 TRUE .. FALSE                */
#endif /* TYPEDEF_H_ */
