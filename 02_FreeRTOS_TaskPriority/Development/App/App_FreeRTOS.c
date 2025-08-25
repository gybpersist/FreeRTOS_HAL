#include "App_FreeRTOS.h"

// ��������1��صĲ��� -----------------
// ��������1��ջ��С
#define TASK1_STACK_SIZE 128
// ��������1���ȼ�
#define TASK1_PRIORITY 1
// ��������1���
TaskHandle_t xTask1Handle;
// ����1������ԭ��
void vTask1Func(void *pvParameters);

// ��������2��صĲ��� -----------------
// ��������2��ջ��С
#define TASK2_STACK_SIZE 128
// ��������2���ȼ�
#define TASK2_PRIORITY 2
// ��������2���
TaskHandle_t xTask2Handle;
// ����2������ԭ��
void vTask2Func(void *pvParameters);

// ��������3��صĲ��� -----------------
// ��������3��ջ��С
#define TASK3_STACK_SIZE 128
// ��������3���ȼ�
#define TASK3_PRIORITY 3
// ��������3���
TaskHandle_t xTask3Handle;
// ����3������ԭ��
void vTask3Func(void *pvParameters);

/**
 * @brief FreeRTOS ��������
 */
void App_FreeRTOS_Start(void)
{
    // �����ٽ���
    taskENTER_CRITICAL();

    // ��������1
    xTaskCreate(vTask1Func, "task1", TASK1_STACK_SIZE, NULL, TASK1_PRIORITY, &xTask1Handle);
    // ��������2
    xTaskCreate(vTask2Func, "task2", TASK2_STACK_SIZE, NULL, TASK2_PRIORITY, &xTask2Handle);
    // ��������3
    xTaskCreate(vTask3Func, "task3", TASK3_STACK_SIZE, NULL, TASK3_PRIORITY, &xTask3Handle);

    // �˳��ٽ���
    taskEXIT_CRITICAL();

    // �������������
    vTaskStartScheduler();
}

// ����1����ʵ��
void vTask1Func(void *pvParameters)
{
    printf("����1����...\n");
    while (1)
    {
        // LED1 ����״̬�л�
        Int_LED_Toggle(LED1_Pin);
        // ��ʱ500ms
        HAL_Delay(500);
    }
}

// ����2����ʵ��
void vTask2Func(void *pvParameters)
{
    printf("����2����...\n");
    while (1)
    {
        // LED2 ����״̬�л�
        Int_LED_Toggle(LED2_Pin);
        // ����������500ms֮��ȡ������
        vTaskDelay(500);
    }
}

// ����3����ʵ��
void vTask3Func(void *pvParameters)
{
    printf("����3����...\n");

    // ɾ���Լ�
    // vTaskDelete(xTask3Handle);

    while (1)
    {
        // LED3 ����״̬�л�
        Int_LED_Toggle(LED3_Pin);
        // ����������500ms֮��ȡ������
        vTaskDelay(500);
    }

    // while (1)
    // {
    //     // �����⵽SW3����������
    //     if (Key_SW3_Detect())
    //     {
    //         // ɾ������1
    //         if (xTask1Handle != NULL)
    //         {
    //             vTaskDelete(xTask1Handle);
    //             xTask1Handle = NULL;
    //         }
    //     }
    // }
}
