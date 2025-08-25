#include "App_FreeRTOS.h"

// 定义任务1相关的参数 -----------------
// 定义任务1堆栈大小
#define TASK1_STACK_SIZE 128
// 定义任务1优先级
#define TASK1_PRIORITY 4
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

// 定义队列的句柄
QueueHandle_t xQueue1;
QueueHandle_t xQueue2;

// 定义字符串，作为向队列2发送的数据
// char *tx_msg = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
char tx_msg[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

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

    // 创建队列1，两个长度，每个项目1字节
    xQueue1 = xQueueCreate(2, sizeof(uint8_t));
    if (xQueue1 != NULL)
    {
        printf("队列1创建成功\n");
    }

    // 创建队列2,1个长度，存放字符串地址
    xQueue2 = xQueueCreate(1, sizeof(char *));
    if (xQueue2 != NULL)
    {
        printf("队列2创建成功\n");
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

        // 如果按键SW3或者按键SW4
        if (key == KEY_SW3 || key == KEY_SW4)
        {
            // 向队列1发送消息，发送按键值3
            if (xQueueSend(xQueue1, &key, portMAX_DELAY) == pdTRUE)
            {
                printf("\n任务1:: 向队列1发送消息成功, 发送数据为: %d \n", key);
            }
            else
            {
                printf("\n任务1:: 向队列发送数据失败！\n");
            }
        }

        // 如果按键SW5
        else if (key == KEY_SW5)
        {
            // 向队列2发送消息，发送tx_msg
            if (xQueueSend(xQueue2, &tx_msg, portMAX_DELAY) == pdTRUE)
            {
                printf("\n任务1:: 向队列2发送消息成功,发送的是字符串的地址:%p \n", tx_msg);
            }
            else
            {
                printf("\n任务1:: 向队列2发送数据失败！\n");
            }

        }

        // 阻塞延时
        vTaskDelay(500);
    }
}

// 任务2函数实现
void vTask2Func(void *pvParameters)
{

    // 定义变量，作为队列1的接收缓冲区
    uint8_t rx_value;

    printf("任务2启动...\n");

    while (1)
    {
        if (xQueueReceive(xQueue1, &rx_value, portMAX_DELAY) == pdTRUE)
        {
            printf("\n任务2中: 接收到队列1中的数据: %d \n", rx_value);
        }
        else
        {
            printf("\n任务2中: 接收队列1数据失败! \n");
        }
    }
}

// 任务3函数实现
void vTask3Func(void *pvParameters)
{
    printf("任务3启动...\n");

    // 定义数组，作为接收缓冲区
    char *rx_buffer = NULL;
    // memset(rx_buffer, 0, 27);

    while (1)
    {
        if (xQueueReceive(xQueue2, &rx_buffer, portMAX_DELAY) == pdTRUE)
        {
            printf("\n任务3中: 接收到队列2中的数据: %p \n", rx_buffer);
        }
        else
        {
            printf("\n任务3中: 接收队列2数据失败! \n");
        }    

    }
}
