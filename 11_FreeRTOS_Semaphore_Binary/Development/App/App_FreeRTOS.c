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

// 定义二进制信号量句柄
SemaphoreHandle_t xBinarySemaphore;


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

    // 创建二进制信号量
    xBinarySemaphore = xSemaphoreCreateBinary();
    if (xBinarySemaphore != NULL)
    {
        printf("创建二进制信号量成功！\n");
    }

    // 退出临界区
    taskEXIT_CRITICAL();

    // 启动任务调度器
    vTaskStartScheduler();
}

// 任务1函数实现
void vTask1Func(void *pvParameters)
{
    printf("任务1启动...\n");
    uint8_t key;

    while (1)
    {
    
        // 获取按键检测函数返回值
        key = Int_Key_Detect();

        // 如果按键 SW3 按下
        if (key == KEY_SW3)
        {
            printf("\n任务1: 准备释放二进制信号量\n");

            // 释放二进制信号量
            if (xSemaphoreGive(xBinarySemaphore) == pdTRUE)
            {
                printf("\n任务1: 释放二进制信号量成功\n");
            }
        }

        // 控制LED1闪烁
        Int_LED_Toggle(LED1_Pin);

        // 阻塞延时
        vTaskDelay(500);
    }
}

// 任务2函数实现
void vTask2Func(void *pvParameters)
{
    printf("任务2启动...\n");

    while (1)
    {
        printf("\n任务2: 开始-----------------------------");
        
        printf("\n任务2: 准备获取二进制信号量\n");
        // 获取二进制信号量
        xSemaphoreTake(xBinarySemaphore, portMAX_DELAY);
        printf("\n任务2: 获取二进制信号量成功\n");
        
        printf("\n任务2: 结束-----------------------------");
    }
}

// // 任务3函数实现
// void vTask3Func(void *pvParameters)
// {
//     printf("任务3启动...\n");

//     // 定义数组，作为接收缓冲区
//     char *rx_buffer = NULL;
//     // memset(rx_buffer, 0, 27);

//     while (1)
//     {
//         if (xQueueReceive(xQueue2, &rx_buffer, portMAX_DELAY) == pdTRUE)
//         {
//             printf("\n任务3中: 接收到队列2中的数据: %s \n", rx_buffer);
//         }
//         else
//         {
//             printf("\n任务3中: 接收队列2数据失败! \n");
//         }    

//     }
// }
