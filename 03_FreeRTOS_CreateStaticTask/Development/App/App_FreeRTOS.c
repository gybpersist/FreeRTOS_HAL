#include "App_FreeRTOS.h"

// 定义任务1相关的参数 -----------------
// 定义任务1堆栈大小
#define TASK1_STACK_SIZE 128
// 定义任务1优先级
#define TASK1_PRIORITY 1
// 定义任务1句柄
TaskHandle_t xTask1Handle;
// 定义数组（存储在全局静态区），作为静态方式创建的任务的栈
StackType_t pxTask1Stack[TASK1_STACK_SIZE];
// 定义任务1的控制块
StaticTask_t xTask1TCB;
// 任务1函数的原型
void vTask1Func(void *pvParameters);

// 定义任务2相关的参数 -----------------
// 定义任务2堆栈大小
#define TASK2_STACK_SIZE 128
// 定义任务2优先级
#define TASK2_PRIORITY 2
// 定义任务2句柄
TaskHandle_t xTask2Handle;
// 定义静态方式创建任务2的栈
StackType_t pxTask2Stack[TASK2_STACK_SIZE];
// 静态方式创建任务2的控制块
StaticTask_t xTask2TCB;
// 任务2函数的原型
void vTask2Func(void *pvParameters);

// 定义任务3相关的参数 -----------------
// 定义任务3堆栈大小
#define TASK3_STACK_SIZE 128
// 定义任务3优先级
#define TASK3_PRIORITY 3
// 定义任务3句柄
TaskHandle_t xTask3Handle;
// 定义静态方式创建任务3的栈
StackType_t pxTask3Stack[TASK3_STACK_SIZE];
// 静态方式创建任务3的控制块
StaticTask_t xTask3TCB;
// 任务3函数的原型
void vTask3Func(void *pvParameters);

/**
 * @brief FreeRTOS 启动函数
 */
void App_FreeRTOS_Start(void)
{
    // 进入临界区
    taskENTER_CRITICAL();

    // 静态方式创建任务1
    xTask1Handle = xTaskCreateStatic(vTask1Func, "Task1", TASK1_STACK_SIZE, NULL, TASK1_PRIORITY, pxTask1Stack, &xTask1TCB);
    // 静态方式创建任务2
    xTask2Handle = xTaskCreateStatic(vTask2Func, "Task2", TASK2_STACK_SIZE, NULL, TASK2_PRIORITY, pxTask2Stack, &xTask2TCB);
    // 静态方式创建任务3
    xTask3Handle = xTaskCreateStatic(vTask3Func, "Task3", TASK3_STACK_SIZE, NULL, TASK3_PRIORITY, pxTask3Stack, &xTask3TCB);

    // 退出临界区
    taskEXIT_CRITICAL();

    // 启动任务调度器
    vTaskStartScheduler();
}

// 任务1函数实现
void vTask1Func(void *pvParameters)
{
    printf("任务1启动...\n");
    while (1)
    {
        // LED1 亮灭状态切换
        Int_LED_Toggle(LED1_Pin);
        // 进入阻塞并500ms之后取消阻塞
        vTaskDelay(500);
    }
}

// 任务2函数实现
void vTask2Func(void *pvParameters)
{
    printf("任务2启动...\n");
    while (1)
    {
        // LED2 亮灭状态切换
        Int_LED_Toggle(LED2_Pin);
        // 进入阻塞并500ms之后取消阻塞
        vTaskDelay(500);
    }
}

// 任务3函数实现
void vTask3Func(void *pvParameters)
{
    printf("任务3启动...\n");

    // 删除自己
    // vTaskDelete(xTask3Handle);

    // while (1)
    // {
    //     // LED3 亮灭状态切换
    //     Int_LED_Toggle(LED3_Pin);
    //     // 进入阻塞并500ms之后取消阻塞
    //     vTaskDelay(500);
    // }

    while (1)
    {
        // 如果检测到SW3按键被按下
        if (Key_SW3_Detect())
        {
            // 删除任务1
            if (xTask1Handle != NULL)
            {
                vTaskDelete(xTask1Handle);
                xTask1Handle = NULL;
            }
        }

        // 进入阻塞并100ms之后取消阻塞
        vTaskDelay(100);
    }
}

// 重定义为空闲任务分配栈内存的函数
void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer,
                                   StackType_t **ppxIdleTaskStackBuffer,
                                   uint32_t *pulIdleTaskStackSize)
{
    // 在静态区创建空闲任务的控制块
    static StaticTask_t pxIdleTaskTCB;
    *ppxIdleTaskTCBBuffer = &pxIdleTaskTCB;

    // 在静态区创建空闲任务使用的栈空间
    static StackType_t pxIdleTaskStack[configMINIMAL_STACK_SIZE];
    *ppxIdleTaskStackBuffer = pxIdleTaskStack;

    // 设置空闲任务的栈大小
    *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
   
}
