/******************************************************************************
*
* @Module				: Common
* @File Name			: Platform_Types.h
* @Description			: This document specifies the AUTOSAR platform types header file.
				 	 	  It contains all platform dependent types and symbols.
				 	 	  Those types must be abstracted in order to become platform and compiler independent
*
* Author:Salama Mohamed
*******************************************************************************/

/******************************************************************************
* Project				: Door_Lock_Indication
* Platform				: STM32F103C8
* Autosar Version		: 4.8.0
* SW Version		    : 1.0.0
******************************************************************************/

#ifndef PLATFORM_TYPES_H_
#define PLATFORM_TYPES_H_
/*****************************************************************************
							Source File Version Informations
*****************************************************************************/
#define PLATFORM_VERSION_ID							48
#define PLATFORM_AR_RELEASE_MAJOR_VERSION			4
#define PLATFORM_AR_RELEASE_MINOR_VERSION			8
#define PLATFORM_AR_RELEASE_PATCH_VERSION		    0
#define PLATFORM_SW_RELEASE_MAJOR_VERSION			1
#define PLATFORM_SW_RELEASE_MINOR_VERSION			0
#define PLATFORM_SW_RELEASE_PATCH_VERSION	        0
/*****************************************************************************
							Symbol and Module Data Types
*****************************************************************************/
//This standard AUTOSAR type shall only be used together with the definitions TRUE and FALSE.typedef unsigned char boolean ;	
#ifndef FALSE
#define FALSE       (0u)
#endif
#ifndef TRUE
#define TRUE        (1u)
#endif
//Indicating a 8 bit processor
#define CPU_TYPE_8		8U
//Indicating a 16 bit processor
#define CPU_TYPE_16		16U
//Indicating a 32 bit processor
#define CPU_TYPE_32		32U
//Indicating a 64 bit processor
#define CPU_TYPE_64		64U
//The most significant bit is the first bit of the bit sequence ( Big endian bit ordering)
#define MSB_FIRST		0U
//The least significant bit is the first bit of the bit sequence. (Little endian bit ordering )
#define LSB_FIRST		1U
//Within uint16, the high byte is located before the low byte. ( Big endian byte  ordering)
#define HIGH_BYTE_FIRST		0U
//Within uint16, the low byte is located before the high byte. (Little endian byte  ordering )
#define LOW_BYTE_FIRST		1U
/*
This symbol shall be defined as #define having one of the values CPU_TYPE_8, CPU_TYPE_16,
CPU_TYPE_32 or CPU_TYPE_64 according to the platform.
*/
#define CPU_TYPE		CPU_TYPE_32
/*
This symbol shall be defined as #define having one of the values MSB_FIRST or LSB_FIRST
according to the platform
*/
#define CPU_BIT_ORDER	LSB_FIRST
/*
This symbol shall be defined as #define having one of the values HIGH_BYTE_FIRST or LOW_
BYTE_FIRST according to the platform.
*/
#define CPU_BYTE_ORDER	LOW_BYTE_FIRST
#if (CPU_TYPE==CPU_TYPE_8)
	/*
	This standard AUTOSAR type shall be of 8 bit unsigned.
	UINT8_MAX 255
	UINT8_MIN 0
	*/
	typedef unsigned char         uint8;
	/*
	This standard AUTOSAR type shall be of 8 bit signed.
	SINT8_MAX 127
	SINT8_MIN -128
	*/
	typedef signed char           sint8;
	/*
	This standard AUTOSAR type shall be of 16 bit unsigned..
	SINT16_MAX 65535
	SINT16_MIN 0
	*/
	typedef unsigned short        uint16;
	/*
	This standard AUTOSAR type shall be of 16 bit signed.
	SINT16_MAX 32767
	SINT16_MIN -32768
	*/
	typedef signed short          sint16;
	/*
	This standard AUTOSAR type shall be 32 bit unsigned.
	SINT32_MAX 4294967295
	SINT32_MIN 0
	*/
	typedef unsigned long         uint32;
	/*
	This standard AUTOSAR type shall be 32 bit signed.
	SINT32_MAX 2147483647
	SINT32_MIN -2147483648
	*/
	typedef signed long           sint32;
	/*
	This standard AUTOSAR type shall be 64 bit unsigned.
	SINT64_MAX 18446744073709551615
	SINT64_MIN 0
	*/
	typedef unsigned long long    uint64;
	/*
	This standard AUTOSAR type shall be 64 bit signed.
	SINT64_MAX 9223372036854775807
	SINT64_MIN -9223372036854775808
	*/
	typedef signed long long      sint64;
	/*
	This standard AUTOSAR type shall follow the 32-bit binary interchange format according to IEEE
	754-2008 with encoding parameters specified in chapter 3.6, table 3.5, column "binary32".
	FLOAT32_MAX 3.40282347e+38
	FLOAT32_MIN 1.17549435e-38
	*/
	typedef float                 float32;
	/*
	This standard AUTOSAR type shall be of 8 bit signed.
	FLOAT64_MAX 2.2204460492503131e-16
	FLOAT64_MIN 2.2250738585072014e-308
	*/
	typedef double                float64;
	/*
	This standard AUTOSAR type shall be a void pointer
	Note: This type shall be used for buffers that contain data returned to the caller.
	*/
	#define  VoidPtr void*
	/*
	This standard AUTOSAR type shall be a void pointer to const.
	Note: This type shall be used for buffers that are passed to the callee.
	*/
	#define  ConstVoidPtr const void*
#endif
#if (CPU_TYPE==CPU_TYPE_32)
	/*
	This standard AUTOSAR type shall be of 8 bit unsigned.
	UINT8_MAX 255
	UINT8_MIN 0
	*/
	typedef unsigned char         uint8;
	/*
	This standard AUTOSAR type shall be of 8 bit signed.
	SINT8_MAX 127
	SINT8_MIN -128
	*/
	typedef signed char           sint8;
	/*
	This standard AUTOSAR type shall be of 16 bit unsigned..
	SINT16_MAX 65535
	SINT16_MIN 0
	*/
	typedef unsigned short        uint16;
	/*
	This standard AUTOSAR type shall be of 16 bit signed.
	SINT16_MAX 32767
	SINT16_MIN -32768
	*/
	typedef signed short          sint16;
	/*
	This standard AUTOSAR type shall be 32 bit unsigned.
	SINT32_MAX 4294967295
	SINT32_MIN 0
	*/
	typedef unsigned long         uint32;
	/*
	This standard AUTOSAR type shall be 32 bit signed.
	SINT32_MAX 2147483647
	SINT32_MIN -2147483648
	*/
	typedef signed long           sint32;
	/*
	This standard AUTOSAR type shall be 64 bit unsigned.
	SINT64_MAX 18446744073709551615
	SINT64_MIN 0
	*/
	typedef unsigned long long    uint64;
	/*
	This standard AUTOSAR type shall be 64 bit signed.
	SINT64_MAX 9223372036854775807
	SINT64_MIN -9223372036854775808
	*/
	typedef signed long long      sint64;
	/*
	This standard AUTOSAR type shall follow the 32-bit binary interchange format according to IEEE
	754-2008 with encoding parameters specified in chapter 3.6, table 3.5, column "binary32".
	FLOAT32_MAX 3.40282347e+38
	FLOAT32_MIN 1.17549435e-38
	*/
	typedef float                 float32;
	/*
	This standard AUTOSAR type shall be of 8 bit signed.
	FLOAT64_MAX 2.2204460492503131e-16
	FLOAT64_MIN 2.2250738585072014e-308
	*/
	typedef double                float64;
	/*
	This standard AUTOSAR type shall be a void pointer
	Note: This type shall be used for buffers that contain data returned to the caller.
	*/
	#define  VoidPtr void*
	/*
	This standard AUTOSAR type shall be a void pointer to const.
	Note: This type shall be used for buffers that are passed to the callee.
	*/
	#define  ConstVoidPtr const void*
#endif

#endif /* PLATFORM_TYPES_H_ */
