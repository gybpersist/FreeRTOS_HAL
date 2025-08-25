#include "App_FreeRTOS.h"

// 定义任务1相关的参数 -----------------
// 定义任务1堆栈大小
#define TASK1_STACK_SIZE 128
// 定义任务1优先级
#define TASK1_PRIORITY 1
// 定义任务1句柄
TaskHandle_t xTask1Handle;
// 任务1函数的原型
void vTask1Func(void *pvParameters);

// 定义任务2相关的参数 -----------------
// 定义任务2堆栈大小
#define TASK2_STACK_SIZE 128
// 定义任务2优先级
#define TASK2_PRIORITY 2
// 定义任务2句柄
TaskHandle_t xTask2Handle;
// 任务2函数的原型
void vTask2Func(void *pvParameters);

// // 定义任务3相关的参数 -----------------
// // 定义任务3堆栈大小
// #define TASK3_STACK_SIZE 256
// // 定义任务3优先级
// #define TASK3_PRIORITY 3
// // 定义任务3句柄
// TaskHandle_t xTask3Handle;
// // 任务3函数的原型
// void vTask3Func(void *pvParameters);

// 定义事件组的句柄
EventGroupHandle_t xEventGroup;


/**
 * @brief FreeRTOS 启动函数
 */
void App_FreeRTOS_Start(void)
{
    // 进入临界区
    taskENTER_CRITICAL();

    // 创建任务1
    xTaskCreate(vTask1Func, "task1", TASK1_STACK_SIZE, NULL, TASK1_PRIORITY, &xTask1Handle);
    // 创建任务2
    xTaskCreate(vTask2Func, "task2", TASK2_STACK_SIZE, NULL, TASK2_PRIORITY, &xTask2Handle);
    // // 创建任务3
    // xTaskCreate(vTask3Func, "task3", TASK3_STACK_SIZE, NULL, TASK3_PRIORITY, &xTask3Handle);

    // 创建事件组
    xEventGroup = xEventGroupCreate();
    if (xEventGroup != NULL)
    {
        printf("事件组创建成功\n");
    }


    // 退出临界区
    taskEXIT_CRITICAL();

    // 启动任务调度器
    vTaskStartScheduler();
}

// 任务1函数实现
void vTask1Func(void *pvParameters)
{
    uint8_t key;

    while (1)
    {
        // 获取按键
        key = Int_Key_Detect();

        // 如果按键 SW3 按下
        if (key == KEY_SW3)
        {
            printf("任务1: 按键 SW3 按下, 设置事件标志位BIT0\n");
            // 设置事件标志位BIT0
            xEventGroupSetBits(xEventGroup, EVENT_GROUP_BIT0);
        }
        // 如果按键 SW4 按下
        else if (key == KEY_SW4)
        {
            printf("任务1: 按键 SW4 按下, 设置事件标志位BIT1\n");
            // 设置事件标志位BIT1
            xEventGroupSetBits(xEventGroup, EVENT_GROUP_BIT1);          
        }
        // 如果按键 SW5 按下
        else if (key == KEY_SW5)
        {
            printf("任务1: 按键 SW5 按下, 设置事件标志位BIT2\n");
            // 设置事件标志位BIT2
            xEventGroupSetBits(xEventGroup, EVENT_GROUP_BIT2);
        }

        // LED1 闪烁
        Int_LED_Toggle(LED1_Pin);

        // 阻塞延时
        vTaskDelay(100);
    }
}

// 任务2函数实现
void vTask2Func(void *pvParameters)
{
    // 定义变量作为掩码掩码变量
    EventBits_t uxEventBits;

    while (1)
    {
        printf("任务2: 开始 ---------------\n");
        
        // 等待事件组标志位 BIT0、BIT1、BIT2
        uxEventBits = xEventGroupWaitBits(xEventGroup, EVENT_GROUP_BIT0 | EVENT_GROUP_BIT1 | EVENT_GROUP_BIT2, pdTRUE, pdTRUE, portMAX_DELAY);
        printf("任务2: 等待事件组标志位 BIT0、BIT1、BIT2 成功, 事件掩码变量:%d \n", uxEventBits);

        printf("任务2: 结束----------------\n");
    }
}

// // 任务3函数实现
// void vTask3Func(void *pvParameters)
// {
//     while (1)
//     {
//         printf("\n高优先级任务3: 开始 -------------------------");

//         // 获取信号量
//         xSemaphoreTake(xMutexSemaphore, portMAX_DELAY);
//         printf("\n高优先级任务3: 获取互斥信号量成功");

//         // 延时 1s
//         HAL_Delay(1000);

//         // 释放信号量
//         xSemaphoreGive(xMutexSemaphore);
//         printf("\n高优先级任务3: 释放互斥信号量成功");

//         printf("\n高优先级任务3: 结束 -------------------------");

//         // 阻塞延时
//         vTaskDelay(100);
//     }
// }
