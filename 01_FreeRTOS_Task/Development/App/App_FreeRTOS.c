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
#define TASK2_PRIORITY 1
// 定义任务2句柄
TaskHandle_t xTask2Handle;
// 任务2函数的原型
void vTask2Func(void *pvParameters);

// 定义任务3相关的参数 -----------------
// 定义任务3堆栈大小
#define TASK3_STACK_SIZE 128
// 定义任务3优先级
#define TASK3_PRIORITY 1
// 定义任务3句柄
TaskHandle_t xTask3Handle;
// 任务3函数的原型
void vTask3Func(void *pvParameters);

/**
 * @brief FreeRTOS 启动函数
 */
void App_FreeRTOS_Start(void)
{

    // 创建任务1
    xTaskCreate(vTask1Func, "task1", TASK1_STACK_SIZE, NULL, TASK1_PRIORITY, &xTask1Handle);
    // 创建任务2
    xTaskCreate(vTask2Func, "task2", TASK2_STACK_SIZE, NULL, TASK2_PRIORITY, &xTask2Handle);
    // 创建任务3
    xTaskCreate(vTask3Func, "task3", TASK3_STACK_SIZE, NULL, TASK3_PRIORITY, &xTask3Handle);

    // 启动任务调度器
    vTaskStartScheduler();
}

// 任务1函数实现
void vTask1Func(void *pvParameters)
{
    while (1)
    {
        // LED1 亮灭状态切换
        Int_LED_Toggle(LED1_Pin);
        // 延时500ms
        HAL_Delay(500);
    }
}

// 任务2函数实现
void vTask2Func(void *pvParameters)
{
    while (1)
    {
        // LED2 亮灭状态切换
        Int_LED_Toggle(LED2_Pin);
        // 延时500ms
        HAL_Delay(500);
    }
}

// 任务3函数实现
void vTask3Func(void *pvParameters)
{
    while (1)
    {
        // 如果检测到SW3按键被按下
        if (Key_SW3_Detect())
        {
            // 如果任务1存在
            if (xTask1Handle != NULL)
            {
                // 删除任务1
                vTaskDelete(xTask1Handle);
                xTask1Handle = NULL;
            }
        }
    }
}
