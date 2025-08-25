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
// #define TASK3_STACK_SIZE 128
// // 定义任务3优先级
// #define TASK3_PRIORITY 3
// // 定义任务3句柄
// TaskHandle_t xTask3Handle;
// // 任务3函数的原型
// void vTask3Func(void *pvParameters);

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
            printf("任务1: 按键 SW3 按下, 将标志位BIT0置1\n");
            // 向任务2发通知并设置通知值
            xTaskNotify(xTask2Handle, EVENT_GROUP_BIT0, eSetBits);
        }
        // 如果按键 SW4 按下
        if (key == KEY_SW4)
        {
            printf("任务1: 按键 SW4 按下, 将标志位BIT1置1\n");
            // 向任务2发通知并设置通知值
            xTaskNotify(xTask2Handle, EVENT_GROUP_BIT1, eSetBits);
        }
        // 如果按键 SW5 按下
        if (key == KEY_SW5)
        {
            printf("任务1: 按键 SW5 按下, 将标志位BIT2置1\n");
            // 向任务2发通知并设置通知值
            xTaskNotify(xTask2Handle, EVENT_GROUP_BIT2, eSetBits);
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
    // 定义变量，用于 接收任务通知值
    uint32_t ulReceivedValue = 0;
    // 定义变量，作为时间标志组
    uint32_t ulEventGroup = 0;

    while (1)
    {
        printf("任务2: 开始 ---------------\n");

        // 等待接收任务通知,并获取通知值
        xTaskNotifyWait(0xFFFFFFFF, 0xFFFFFFFF, &ulReceivedValue, portMAX_DELAY);
        // printf("任务2: 收到任务通知, 通知值：%d \n", ulReceivedValue);

        // 处理任务通知值
        if (ulReceivedValue & EVENT_GROUP_BIT0)
        {
            // 给事件组标志位BIT0置1
            ulEventGroup |= EVENT_GROUP_BIT0;
        }
        if (ulReceivedValue & EVENT_GROUP_BIT1)
        {
            // 给事件组标志位BIT1置1
            ulEventGroup |= EVENT_GROUP_BIT1;
        }
        if (ulReceivedValue & EVENT_GROUP_BIT2)
        {
            // 给事件组标志位BIT2置1
            ulEventGroup |= EVENT_GROUP_BIT2;
        }

        // 如果EventGroup 中的BIT0、BIT1、BIT2 都置1
        if (ulEventGroup == (EVENT_GROUP_BIT0 | EVENT_GROUP_BIT1 | EVENT_GROUP_BIT2))
        {
            printf("任务2: 事件组标志位BIT0、BIT1、BIT2 都置1, 事件组标志: %d \n", ulEventGroup);
            // ulEventGroup 复位
            ulEventGroup = 0;
        }


        printf("任务2: 结束----------------\n");
    }
}

// // 任务3函数实现
// void vTask3Func(void *pvParameters)
// {
//     while (1)
//     {

//         printf("任务3: 向任务1发送通知, 通知值+1, 模拟计数信号量...\n");
//         // 向任务1发送通知, 通知值+1, 模拟计数信号量
//         xTaskNotifyGive(xTask1Handle);

//         // 阻塞延时
//         vTaskDelay(2000);
//     }
// }
