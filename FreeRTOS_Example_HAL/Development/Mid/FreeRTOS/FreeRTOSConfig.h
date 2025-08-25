/*
 * FreeRTOS V202212.01
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * https://www.FreeRTOS.org
 * https://github.com/FreeRTOS
 *
 */

#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H



/*-----------------------------------------------------------
 * Application specific definitions.
 *
 * These definitions should be adjusted for your particular hardware and
 * application requirements.
 *
 * THESE PARAMETERS ARE DESCRIBED WITHIN THE 'CONFIGURATION' SECTION OF THE
 * FreeRTOS API DOCUMENTATION AVAILABLE ON THE FreeRTOS.org WEB SITE.
 *
 * See http://www.freertos.org/a00110.html
 *----------------------------------------------------------*/

#define configUSE_PREEMPTION		1
#define configUSE_IDLE_HOOK			0
#define configUSE_TICK_HOOK			0
#define configCPU_CLOCK_HZ			( ( unsigned long ) 72000000 )
#define configTICK_RATE_HZ			( ( TickType_t ) 1000 )
#define configMAX_PRIORITIES		( 5 )
#define configMINIMAL_STACK_SIZE	( ( unsigned short ) 128 )
#define configTOTAL_HEAP_SIZE		( ( size_t ) ( 17 * 1024 ) )
#define configMAX_TASK_NAME_LEN		( 16 )
#define configUSE_TRACE_FACILITY	0
#define configUSE_16_BIT_TICKS		0
#define configIDLE_SHOULD_YIELD		1


/* Set the following definitions to 1 to include the API function, or zero
to exclude the API function. */

#define INCLUDE_vTaskPrioritySet		1
#define INCLUDE_uxTaskPriorityGet		1
#define INCLUDE_vTaskDelete				1
#define INCLUDE_vTaskCleanUpResources	0
#define INCLUDE_vTaskSuspend			1
#define INCLUDE_vTaskDelayUntil			1
#define INCLUDE_vTaskDelay				1

/* This is the raw value as per the Cortex-M3 NVIC.  Values can be 255
(lowest) to 0 (1?) (highest). */
#define configKERNEL_INTERRUPT_PRIORITY 		255
/* !!!! configMAX_SYSCALL_INTERRUPT_PRIORITY must not be set to zero !!!!
See http://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html. */
#define configMAX_SYSCALL_INTERRUPT_PRIORITY 	191 /* equivalent to 0xb0, or priority 11. */


/* This is the value being used as per the ST library which permits 16
priority values, 0 to 15.  This must correspond to the
configKERNEL_INTERRUPT_PRIORITY setting.  Here 15 corresponds to the lowest
NVIC value of 255. */
#define configLIBRARY_KERNEL_INTERRUPT_PRIORITY	15

/* 自定义代码 start */
// 将 xPortPendSVHandler 定义为硬件的 PendSV_Handler 中断处理函数，用于 FreeRTOS 的 PendSV 中断处理
#define xPortPendSVHandler PendSV_Handler
// 将 vPortSVCHandler 定义为硬件的 SVC_Handler 中断处理函数，用于 FreeRTOS 的 SVC 中断处理
#define vPortSVCHandler SVC_Handler
// 包含 xTaskGetSchedulerState 函数，该函数可用于获取 FreeRTOS 调度器的当前状态
#define INCLUDE_xTaskGetSchedulerState	1
/* 自定义代码 end */


#endif /* FREERTOS_CONFIG_H */

// 在 FreeRTOS 中，函数名和变量名通常会带有特定的前缀，这些前缀遵循一定的命名规范，用于标识函数的返回值类型或变量的属性。以下是一些常见前缀的含义：
// v：表示函数返回值为 void（无返回值），例如 vTaskDelay()、vQueueDelete()。
// x：表示函数返回值为一个非标准类型（通常是结构体、枚举或 FreeRTOS 自定义类型），例如 xTaskCreate() 返回 BaseType_t 类型，xQueueReceive() 返回 BaseType_t 类型。
// u：表示无符号整数类型（unsigned），例如 uTaskNumber 可能表示一个无符号的任务编号。
// s：表示有符号整数类型（signed），例如 sTimeout 可能表示一个有符号的超时值。
// p：表示指针类型（pointer），例如 pTaskParameters 可能表示一个指向任务参数结构体的指针。
// c：表示字符类型（char），例如 cQueueName 可能表示一个队列的名称（字符数组）。
// ul：表示无符号长整数类型（unsigned long），例如 ulBaudRate 可能表示波特率（无符号长整数）。
// us：表示无符号短整数类型（unsigned short），例如 usDataLength 可能表示数据长度（无符号短整数）。
