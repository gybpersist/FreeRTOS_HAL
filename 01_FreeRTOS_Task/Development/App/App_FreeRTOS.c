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
#define TASK2_PRIORITY 1
// ��������2���
TaskHandle_t xTask2Handle;
// ����2������ԭ��
void vTask2Func(void *pvParameters);

// ��������3��صĲ��� -----------------
// ��������3��ջ��С
#define TASK3_STACK_SIZE 128
// ��������3���ȼ�
#define TASK3_PRIORITY 1
// ��������3���
TaskHandle_t xTask3Handle;
// ����3������ԭ��
void vTask3Func(void *pvParameters);

/**
 * @brief FreeRTOS ��������
 */
void App_FreeRTOS_Start(void)
{

    // ��������1
    xTaskCreate(vTask1Func, "task1", TASK1_STACK_SIZE, NULL, TASK1_PRIORITY, &xTask1Handle);
    // ��������2
    xTaskCreate(vTask2Func, "task2", TASK2_STACK_SIZE, NULL, TASK2_PRIORITY, &xTask2Handle);
    // ��������3
    xTaskCreate(vTask3Func, "task3", TASK3_STACK_SIZE, NULL, TASK3_PRIORITY, &xTask3Handle);

    // �������������
    vTaskStartScheduler();
}

// ����1����ʵ��
void vTask1Func(void *pvParameters)
{
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
    while (1)
    {
        // LED2 ����״̬�л�
        Int_LED_Toggle(LED2_Pin);
        // ��ʱ500ms
        HAL_Delay(500);
    }
}

// ����3����ʵ��
void vTask3Func(void *pvParameters)
{
    while (1)
    {
        // �����⵽SW3����������
        if (Key_SW3_Detect())
        {
            // �������1����
            if (xTask1Handle != NULL)
            {
                // ɾ������1
                vTaskDelete(xTask1Handle);
                xTask1Handle = NULL;
            }
        }
    }
}
