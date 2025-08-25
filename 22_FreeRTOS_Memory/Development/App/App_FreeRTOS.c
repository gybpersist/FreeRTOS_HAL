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
    // 定义变量，记录分配的内存的地址
    void *pvMemoryAddr = NULL;

    uint8_t key;

    while (1)
    {
        key = Int_Key_Detect();

        // 如果按键 SW3 按下
        if (key == KEY_SW3)
        {
            printf("按键 SW3 按下，分配内存空间... \n");
            // 分配内存空间
            pvMemoryAddr = pvPortMalloc(100);
            if (pvMemoryAddr != NULL)
            {
                printf("内存分配成功，地址为: %p \n", pvMemoryAddr);
            }
            else
            {
                printf("内存分配失败... \n");
            }
        }
        // 如果按键 SW4 按下
        else if (key == KEY_SW4)
        {
            printf("按键 SW4 按下，释放内存空间... \n");
            if (pvMemoryAddr != NULL)
            {
                vPortFree(pvMemoryAddr);
                pvMemoryAddr = NULL;
                printf("内存释放成功... \n");
            }
        }

        printf("剩余堆内存空间: %d 字节... \n", xPortGetFreeHeapSize());

        Int_LED_Toggle(LED1_Pin);

        vTaskDelay(1000);
    }
}
