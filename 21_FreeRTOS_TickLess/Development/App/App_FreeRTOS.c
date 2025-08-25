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

/**
 * @brief FreeRTOS 启动函数
 */
void App_FreeRTOS_Start(void)
{
    // 进入临界区
    taskENTER_CRITICAL();

    // 创建任务1
    xTaskCreate(vTask1Func, "task1", TASK1_STACK_SIZE, NULL, TASK1_PRIORITY, &xTask1Handle);

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
        printf("任务1运行... \n");
        Int_LED_Toggle(LED1_Pin);
        vTaskDelay(1000);
    }
}

// 函数实现：当进入TickLess模式时，会调用该函数
void vEnterTicklessExec(uint32_t time)
{
    printf("进入TickLess模式, 当前时间为：%d \n", time);
}

// 函数实现：当退出TickLess模式时，会调用该函数
void vExitTicklessExec(uint32_t time)
{
    printf("退出TickLess模式, 当前时间为：%d \n", time);
}
