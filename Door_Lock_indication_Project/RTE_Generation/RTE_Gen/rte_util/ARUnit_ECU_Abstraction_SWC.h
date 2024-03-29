/********************************************************************
 * Automatically generated by ARUnit
 * Filename: ARUnit_ECU_Abstraction_SWC.h
 * Generated on: Sun Oct 22 16:43:23 EEST
 ********************************************************************/

#include "Rte_ECU_Abstraction_SWC.h"	

#ifndef ARUNIT_ECU_ABSTRACTION_SWC_H
#define ARUNIT_ECU_ABSTRACTION_SWC_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifndef false
    #define false (0)
#endif
#ifndef true
    #define true  (!false)
#endif


void ARUnit_Initialize ();

/***************************************/
/******** Delegates API  ***************/
/***************************************/

/***************************************/
/******** Flags API  *******************/
/***************************************/

/***************************************/
/******** Implicit API  ****************/
/***************************************/
DECLSPEC_EXPORT void ARUnit_IWrite_ECU_Abstraction_SWC_Read_Door_Sensor_PP_SR_DOOR_State_Sensor_Reading(myuint8 Sensor_Reading);
DECLSPEC_EXPORT myuint8 ARUnit_IRead_ECU_Abstraction_SWC_Read_Door_Sensor_PP_SR_DOOR_State_Sensor_Reading(void);
DECLSPEC_EXPORT myuint8* ARUnit_IWriteRef_ECU_Abstraction_SWC_Read_Door_Sensor_PP_SR_DOOR_State_Sensor_Reading(void);
/***************************************/
/******** Explicit API  ****************/
/***************************************/
/***************************************/
/******** Runnable Calls****************/
/***************************************/
DECLSPEC_EXPORT Std_ReturnType ARUnit_Trigger_ECU_Abstraction_SWC_Switch_LED_State_Runnable(myuint8 LED_State);

DECLSPEC_EXPORT void ARUnit_Trigger_ECU_Abstraction_SWC_Read_Door_Sensor_Runnable(void);

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* ARUNIT_ECU_ABSTRACTION_SWC_H */
