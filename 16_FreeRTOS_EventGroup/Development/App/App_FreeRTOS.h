#ifndef __APP_FREERTOS_H__
#define __APP_FREERTOS_H__

#include "FreeRTOS.h"
#include "task.h"
#include "event_groups.h"

#include "Com_Debug.h"

#include "Int_LED.h"
#include "Int_Key.h"

// 宏定义：事件组标志位
#define EVENT_GROUP_BIT0 (1 << 0)           // 00000001
#define EVENT_GROUP_BIT1 (1 << 1)           // 00000010
#define EVENT_GROUP_BIT2 (1 << 2)           // 00000100


/**
 * @brief FreeRTOS 启动函数
 
 */
void App_FreeRTOS_Start(void);

#endif /* __APP_FREERTOS_H__ */
