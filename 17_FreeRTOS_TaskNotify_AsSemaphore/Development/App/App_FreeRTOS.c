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
#define TASK3_STACK_SIZE 128
// 定义任务3优先级
#define TASK3_PRIORITY 3
// 定义任务3句柄
TaskHandle_t xTask3Handle;
// 任务3函数的原型
void vTask3Func(void *pvParameters);


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
    uint8_t key;

    while (1)
    {
        // 获取按键
        key = Int_Key_Detect();

        // 如果按键 SW3 按下
        if (key == KEY_SW3)
        {
            printf("任务1: 按键 SW3 按下, 向任务2发通知,不带通知值,模拟二进制信号量\n");
            // 向任务2发通知,不带通知值,模拟二进制信号量
            xTaskNotifyGive(xTask2Handle);
        }
        // 如果按键 SW4 按下
        else if (key == KEY_SW4)
        {
            printf("任务1: 按键 SW4 按下, 接收任务3的通知, 通知值-1, 当前通知值: %d\n", ulTaskNotifyTake(pdFALSE, portMAX_DELAY));
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
        
        // 等待接收任务通知
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        printf("任务2: 收到任务通知\n");

        printf("任务2: 结束----------------\n");
    }
}

// 任务3函数实现
void vTask3Func(void *pvParameters)
{
    while (1)
    {
       
        printf("任务3: 向任务1发送通知, 通知值+1, 模拟计数信号量...\n");
        // 向任务1发送通知, 通知值+1, 模拟计数信号量
        xTaskNotifyGive(xTask1Handle);

        // 阻塞延时
        vTaskDelay(2000);
    }
}
