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

// 定义任务3相关的参数 -----------------
// 定义任务3堆栈大小
#define TASK3_STACK_SIZE 256
// 定义任务3优先级
#define TASK3_PRIORITY 3
// 定义任务3句柄
TaskHandle_t xTask3Handle;
// 任务3函数的原型
void vTask3Func(void *pvParameters);

// 定义字符串，用于保存任务状态信息
// char pcTaskInfo[256];

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
    // 创建任务3
    xTaskCreate(vTask3Func, "task3", TASK3_STACK_SIZE, NULL, TASK3_PRIORITY, &xTask3Handle);

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
        printf("\n----------------任务1正在执行 ---------------------\n");
        printf("任务1正在执行...\n");
        // LED1 闪烁
        Int_LED_Toggle(LED1_Pin);
        printf("------------------任务1执行结束 ---------------------\n");

        // 阻塞延时
        vTaskDelay(1000);
    }
}

// 任务2函数实现
void vTask2Func(void *pvParameters)
{

    printf("任务2启动...\n");
    while (1)
    {
        printf("\n----------------任务2正在执行 ---------------------\n");

        // 获取任务相关信息
        printf("系统中的任务数量：%d \n", uxTaskGetNumberOfTasks());
        printf("任务1的优先级: %d; 任务2的优先级: %d \n", uxTaskPriorityGet(xTask1Handle), uxTaskPriorityGet(xTask2Handle));
        printf("任务1的历史任务栈最小剩余量: %d; 任务2的历史任务栈最小剩余量: %d \n", uxTaskGetStackHighWaterMark(xTask1Handle), uxTaskGetStackHighWaterMark(xTask2Handle));

        printf("------------------任务2执行结束 ---------------------\n");

        vTaskDelay(1000);
    }
}

// 任务3函数实现
void vTask3Func(void *pvParameters)
{
    printf("任务3启动...\n");

    uint8_t key;

    while (1)
    {
        //  printf("任务3正在运行...\n");
        printf("\n----------------任务3正在执行 ---------------------\n");

        printf("任务3正在执行...\n");

        // 获取按键检测函数返回值
        key = Int_Key_Detect();

        // 如果按键SW3
        if (key == KEY_SW3)
        {
            printf("\n按键SW3按下, 修改任务1的优先级为4 >>>>>>>>>>> \n");
            // 修改任务1的优先级为4
            vTaskPrioritySet(xTask1Handle, 4);
        }

        printf("\n----------------任务3正在结束 ---------------------\n");


        // 阻塞延时
        vTaskDelay(500);
    }
}
