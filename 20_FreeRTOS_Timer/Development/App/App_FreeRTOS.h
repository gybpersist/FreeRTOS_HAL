#ifndef __APP_FREERTOS_H__
#define __APP_FREERTOS_H__

#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"

#include "Com_Debug.h"

#include "Int_LED.h"
#include "Int_Key.h"


/**
 * @brief FreeRTOS Æô¶¯º¯Êý
 
 */
void App_FreeRTOS_Start(void);

#endif /* __APP_FREERTOS_H__ */
