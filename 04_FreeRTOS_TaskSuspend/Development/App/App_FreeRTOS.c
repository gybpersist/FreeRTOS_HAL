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
#define TASK3_STACK_SIZE 512
// 定义任务3优先级
#define TASK3_PRIORITY 3
// 定义任务3句柄
TaskHandle_t xTask3Handle;
// 任务3函数的原型
void vTask3Func(void *pvParameters);

// 定义字符串，用于保存任务状态信息
char pcTaskInfo[256];

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
       // printf("任务1正在运行...\n");
        // LED1 亮灭状态切换
        Int_LED_Toggle(LED1_Pin);
        // 延时500ms
        HAL_Delay(500);
    }
}

// 任务2函数实现
void vTask2Func(void *pvParameters)
{
    printf("任务2启动...\n");
    while (1)
    {
       // printf("任务2正在运行...\n");
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

    uint8_t key;

    while (1)
    {
      //  printf("任务3正在运行...\n");

        // 获取按键检测函数返回值
        key = Int_Key_Detect();

        // 如果按键SW3
        if (key == KEY_SW3)
        {
            printf("按键SW3按下, 任务1挂起\n");
            // 挂起任务1
            vTaskSuspend(xTask1Handle);
        }
        // // 如果按键SW4
        // else if (key == KEY_SW4)
        // {
        //     printf("按键SW4按下, 任务1恢复\n");
        //     // 恢复任务1
        //     vTaskResume(xTask1Handle);
        // }
        // 如果按键SW5
        else if (key == KEY_SW5)
        {
            printf("按键SW5按下, 挂起调度器\n");
            // 挂起调度器
            vTaskSuspendAll();
        }
        // 如果按键SW6
        else if (key == KEY_SW6)
        {
            printf("按键SW6按下, 恢复调度器\n");
            // 恢复调度器
            xTaskResumeAll();
        }

        // 获取任务状态信息
        vTaskList(pcTaskInfo);
        // 打印任务状态信息
        printf("\n%s\n", pcTaskInfo);


        // 阻塞延时
        vTaskDelay(500);
    }
}


// 重定义 EXTI9_5 （按键SW4(PF9) ）触发后调用的弱函数
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    // 如果是按键SW4触发
    if (GPIO_Pin == SW4_Pin)
    {
        // 延时10ms 消抖
        HAL_Delay(10);
        // 再次判断SW4是否被按下
        if (HAL_GPIO_ReadPin(SW4_GPIO_Port, SW4_Pin) == GPIO_PIN_RESET)
        {
            printf("按键SW4按下, 任务1恢复\n");
            // 恢复任务1
            xTaskResumeFromISR(xTask1Handle);     
        }       
    }
}
