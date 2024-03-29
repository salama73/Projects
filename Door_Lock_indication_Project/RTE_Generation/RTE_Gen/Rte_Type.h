/********************************************************************
 * Automatically generated by ARUnit
 * Filename: Rte_Type.h
 * Generated on: Sun Oct 22 16:43:23 EEST
 ********************************************************************/

#ifndef RTE_TYPE_H
#define RTE_TYPE_H


#include "Rte.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
/**************************** datatypes ******************************/

typedef unsigned char myuint8;


/********************* mode declaration groups ***********************/


/********************** per instance memories ************************/


/******************* implicit buffer declaration *********************/

typedef struct {
	myuint8 value;
} Rte_DE_myuint8;


/******************** component data structures **********************/

/*********************************************************************
 * component data structure for SWC: DoorLock_indication 
 *********************************************************************/
typedef struct Rte_CDS_DoorLock_indication
{
	/* Data Handles section*/
	Rte_DE_myuint8 *DoorLock_indication_RP_SR_DOOR_State_Door_State;
	Rte_DE_myuint8 *DoorLock_indication_PP_SR_LED_State_LED_State;
	/* Per-Instance Memory Handles section*/
	/* Inter-runnable Variable Handles section*/
	/* Calibration Parameter Handles section*/
	/* Exclusive-area Handles section*/
	/* Port API Handles section*/
	/* Inter Runnable Variable API Handles section*/
} Rte_CDS_DoorLock_indication;

/*********************************************************************
 * component data structure for SWC: ECU_Abstraction_SWC 
 *********************************************************************/
typedef struct Rte_CDS_ECU_Abstraction_SWC
{
	/* Data Handles section*/
	Rte_DE_myuint8 *Read_Door_Sensor_PP_SR_DOOR_State_Sensor_Reading;
	/* Per-Instance Memory Handles section*/
	/* Inter-runnable Variable Handles section*/
	/* Calibration Parameter Handles section*/
	/* Exclusive-area Handles section*/
	/* Port API Handles section*/
	/* Inter Runnable Variable API Handles section*/
} Rte_CDS_ECU_Abstraction_SWC;

/*********************************************************************
 * component data structure for SWC: LED_Actuator 
 *********************************************************************/
typedef struct Rte_CDS_LED_Actuator
{
	/* Data Handles section*/
	Rte_DE_myuint8 *Read_LED_State_RP_SR_LED_State_LED_State;
	/* Per-Instance Memory Handles section*/
	/* Inter-runnable Variable Handles section*/
	/* Calibration Parameter Handles section*/
	/* Exclusive-area Handles section*/
	/* Port API Handles section*/
	/* Inter Runnable Variable API Handles section*/
} Rte_CDS_LED_Actuator;

/*********************************************************************
 * component data structure for SWC: Read_Door_State 
 *********************************************************************/
typedef struct Rte_CDS_Read_Door_State
{
	/* Data Handles section*/
	Rte_DE_myuint8 *Read_Door_State_RP_DOOR_State_Sensor_Reading;
	Rte_DE_myuint8 *Read_Door_State_PP_DOOR_State_Door_State;
	/* Per-Instance Memory Handles section*/
	/* Inter-runnable Variable Handles section*/
	/* Calibration Parameter Handles section*/
	/* Exclusive-area Handles section*/
	/* Port API Handles section*/
	/* Inter Runnable Variable API Handles section*/
} Rte_CDS_Read_Door_State;

/*********************************************************************
 * component data structure for SWC: SWC_Composition 
 *********************************************************************/
typedef struct Rte_CDS_SWC_Composition
{
	/* Data Handles section*/
	/* Per-Instance Memory Handles section*/
	/* Inter-runnable Variable Handles section*/
	/* Calibration Parameter Handles section*/
	/* Exclusive-area Handles section*/
	/* Port API Handles section*/
	/* Inter Runnable Variable API Handles section*/
	uint8 _dummy;
} Rte_CDS_SWC_Composition;


#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* RTE_TYPE_H */
