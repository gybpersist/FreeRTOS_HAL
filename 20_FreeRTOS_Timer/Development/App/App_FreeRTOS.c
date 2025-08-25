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


// 定义一次性定时器相关参数 ----------------------------
// 定义一次性定时器句柄
TimerHandle_t xTimer1;
// 定义一次性定时器回调函数的原型
void vTimer1Callback(TimerHandle_t xTimer);

// 定义周期性定时器相关参数 ----------------------------
// 定义周期性定时器句柄
TimerHandle_t xTimer2;
// 定义周期性定时器回调函数的原型
void vTimer2Callback(TimerHandle_t xTimer);



/**
 * @brief FreeRTOS 启动函数
 */
void App_FreeRTOS_Start(void)
{
    // 进入临界区
    taskENTER_CRITICAL();

    // 创建任务1
    xTaskCreate(vTask1Func, "task1", TASK1_STACK_SIZE, NULL, TASK1_PRIORITY, &xTask1Handle);

    // 创建一次性定时器
    xTimer1 = xTimerCreate("Timer1", 5000, pdFALSE, (void *)0, vTimer1Callback);
    if (xTimer1 != NULL)
    {
        printf("一次性定时器创建成功！\n");
    }

    // 创建周期性定时器
    xTimer2 = xTimerCreate("Timer2", 5000, pdTRUE, (void *)1, vTimer2Callback);
    if (xTimer2 != NULL)
    {
        printf("周期性定时器创建成功！\n");
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
            printf("任务1: SW3 按下, 启动一次性定时器 \n");
            // 启动一次性定时器
            xTimerStart(xTimer1, portMAX_DELAY);
        }
        // 如果按键 SW4 按下
        if (key == KEY_SW4)
        {
            printf("任务1: SW4 按下, 启动周期性定时器 \n");
            // 启动周期性定时器
            xTimerStart(xTimer2, portMAX_DELAY);
        }
       
        // LED1 闪烁
        Int_LED_Toggle(LED1_Pin);

        // 阻塞延时
        vTaskDelay(100);
    }
}

// 一次性定时器回调函数实现
void vTimer1Callback(TimerHandle_t xTimer)
{
    static uint16_t count = 0;
    // 打印提示信息
    printf("一次性定时器触发了！调用次数：%d \n", ++count);
}

// 周期性定时器回调函数实现
void vTimer2Callback(TimerHandle_t xTimer)
{
    static uint16_t count = 0;
    // 打印提示信息
    printf("周期性定时器触发了！调用次数：%d \n", ++count);
}
