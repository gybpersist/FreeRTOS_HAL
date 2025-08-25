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
#define TASK3_STACK_SIZE 256
// ��������3���ȼ�
#define TASK3_PRIORITY 3
// ��������3���
TaskHandle_t xTask3Handle;
// ����3������ԭ��
void vTask3Func(void *pvParameters);

// ����������ź������
SemaphoreHandle_t xBinarySemaphore;

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

    // �����������ź���
    xBinarySemaphore = xSemaphoreCreateBinary();
    if (xBinarySemaphore != NULL)
    {
        printf("�����������ź����ɹ���\n");

        // �����ͷŶ������ź���
        xSemaphoreGive(xBinarySemaphore);
        printf("�����ͷŶ������ź����ɹ���\n");
    }

    // �˳��ٽ���
    taskEXIT_CRITICAL();

    // �������������
    vTaskStartScheduler();
}

// ����1����ʵ��
void vTask1Func(void *pvParameters)
{
    while (1)
    {
        printf("\n�����ȼ�����1: ��ʼ -------------------------");

        // ��ȡ�������ź���
        xSemaphoreTake(xBinarySemaphore, portMAX_DELAY);
        printf("\n�����ȼ�����1: ��ȡ�������ź����ɹ�");

        // ��ʱ 3s
        HAL_Delay(3000);

        // �ͷŶ������ź���
        printf("\n�����ȼ�����1: �ͷŶ������ź���...");
        xSemaphoreGive(xBinarySemaphore);

        printf("\n�����ȼ�����1: ���� -------------------------");
    }
}

// ����2����ʵ��
void vTask2Func(void *pvParameters)
{
    while (1)
    {
        printf("\n�����ȼ�����2: ��ʼ -------------------------");

        // ��ʱ 1.5s
        HAL_Delay(1500);

        printf("\n�����ȼ�����2: ���� -------------------------");

        // ������ʱ
        vTaskDelay(100);
    }
}

// ����3����ʵ��
void vTask3Func(void *pvParameters)
{
    while (1)
    {
        printf("\n�����ȼ�����3: ��ʼ -------------------------");

        // ��ȡ�ź���
        xSemaphoreTake(xBinarySemaphore, portMAX_DELAY);
        printf("\n�����ȼ�����3: ��ȡ�������ź����ɹ�");

        // ��ʱ 1s
        HAL_Delay(1000);

        // �ͷ��ź���
        xSemaphoreGive(xBinarySemaphore);
        printf("\n�����ȼ�����3: �ͷŶ������ź����ɹ�");

        printf("\n�����ȼ�����3: ���� -------------------------");

        // ������ʱ
        vTaskDelay(100);
    }
}
