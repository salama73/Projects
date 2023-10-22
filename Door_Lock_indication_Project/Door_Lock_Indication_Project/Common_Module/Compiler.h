/******************************************************************************
* @Module		: Common
* @File Name	: Compiler.h
* @Description 	: This document specifies macros for the abstraction of compiler specific keywords
				  used for addressing data and code within declarations and definitions.
* Author		: Salama Mohamed
*******************************************************************************/

/******************************************************************************
* Project				: Door_Lock_Indication
* Platform				: STM32F103C8
* Autosar Version		: 4.8.0
* SW Version		    : 1.0.0
******************************************************************************/
#ifndef COMPILER_H_
#define COMPILER_H_
/*****************************************************************************
							Source File Version Informations
*****************************************************************************/
#define COMPILER_VERSION_ID							51
#define COMPILER_AR_RELEASE_MAJOR_VERSION			4
#define COMPILER_AR_RELEASE_MINOR_VERSION			8
#define COMPILERAR_RELEASE_PATCH_VERSION			0
#define COMPILER_SW_RELEASE_MAJOR_VERSION			1
#define COMPILER_SW_RELEASE_MINOR_VERSION			0
#define COMPILER_SW_RELEASE_PATCH_VERSION		    0
/*****************************************************************************
							Symbol and Module Data Types
*****************************************************************************/
/*
The memory class AUTOMATIC shall be provided as empty definition, used for
the declaration of local pointers.
*/
#define AUTOMATIC
/*
 The memory class TYPEDEF shall be provided as empty definition. This memory
 class shall be used within type definitions, where no memory qualifier can be
 specified. This can be necessary for defining pointer types,
*/
#define TYPEDEF
/*
The compiler abstraction shall provide the INLINE define for abstraction of the
keyword inline
*/
#define INLINE	inline
/*
The compiler abstraction shall provide the LOCAL_INLINE define for abstraction
of the keyword inline in functions with �static� scope.
*/
#define LOCAL_INLINE	static inline
/*
The compiler abstraction shall define the FUNC macro for the declaration and
definition of functions that ensures correct syntax of function declarations as
required by a specific compiler
*/
#define FUNC(rettype, memclass)	rettype#define STATIC	static

#endif /* COMPILER_H_ */
