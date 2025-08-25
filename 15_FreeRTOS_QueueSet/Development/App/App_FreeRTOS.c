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

// 定义队列的句柄
QueueHandle_t xQueue;
// 定义二进制信号量的句柄
SemaphoreHandle_t xBinarySemaphore;
// 定义队列集的句柄
QueueSetHandle_t xQueueSet;

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

    // 创建队列
    xQueue = xQueueCreate(1, sizeof(uint8_t));
    // 创建二进制信号量
    xBinarySemaphore = xSemaphoreCreateBinary();

    // 创建队列集
    xQueueSet = xQueueCreateSet(2);
    if (xQueueSet != NULL)
    {
        printf("队列集创建成功\n");

        // 将队列添加到队列集中
        if (xQueueAddToSet(xQueue, xQueueSet) == pdPASS)
        {
            printf("队列添加到队列集成功\n");
        }

        // 将二进制信号量添加到队列集中
        if (xQueueAddToSet(xBinarySemaphore, xQueueSet) == pdPASS)
        {
            printf("二进制信号量添加到队列集成功\n");
        }
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
            printf("任务1: 按键 SW3 按下，向队列发送数据!\n");
            // 发送数据到队列
            xQueueSend(xQueue, &key, portMAX_DELAY);
        }
        // 如果按键 SW4 按下
        else if (key == KEY_SW4)
        {
            printf("任务1: 按键 SW4 按下，释放二进制信号量!\n");
            // 释放二进制信号量
            xSemaphoreGive(xBinarySemaphore);
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
    // 定义变量，表示获取到信息的队列集的成员
    QueueSetMemberHandle_t xMember;
    // 定义变量，作为队列接收缓冲区
    uint8_t queue_value;

    while (1)
    {
        printf("任务2: 开始 ---------------\n");
        // 从队列集中获取数据（任何队列集成员符合要求都可以获取到，获取不到阻塞）
        xMember = xQueueSelectFromSet(xQueueSet, portMAX_DELAY);

        printf("任务2: 从队列集获取数据成功\n");

        // 如果获取到信息的队列
        if (xMember == xQueue)
        {
            // 从队列中接收数据并删除
            xQueueReceive(xQueue, &queue_value, portMAX_DELAY);
            printf("任务2: 从队列获取数据: %d \n", queue_value);
        }
        // 如果获取到信息的是二进制信号量
        else if (xMember == xBinarySemaphore)
        {
            // 获取到二进制信号量
            xSemaphoreTake(xBinarySemaphore, portMAX_DELAY);
            printf("任务2: 从二进制信号量获取数据成功\n");
        }

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
