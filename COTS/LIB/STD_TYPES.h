#ifndef STD_TYPES_H
#define STD_TYPES_H

#include <stdint.h> 

typedef uint8_t                Std_ReturnType;           /**< Standard return type for functions */
#define E_OK                 ((Std_ReturnType)1)         /**< Function execution successful */
#define E_NOT_OK             ((Std_ReturnType)0)         /**< Function execution failed */
#define NULL                 ((void*)0x0)                /**< Null pointer definition */

#endif /*STD_TYPES_H*/
