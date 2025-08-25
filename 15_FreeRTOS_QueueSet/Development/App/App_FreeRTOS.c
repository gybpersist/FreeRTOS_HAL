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

// // ��������3��صĲ��� -----------------
// // ��������3��ջ��С
// #define TASK3_STACK_SIZE 256
// // ��������3���ȼ�
// #define TASK3_PRIORITY 3
// // ��������3���
// TaskHandle_t xTask3Handle;
// // ����3������ԭ��
// void vTask3Func(void *pvParameters);

// ������еľ��
QueueHandle_t xQueue;
// ����������ź����ľ��
SemaphoreHandle_t xBinarySemaphore;
// ������м��ľ��
QueueSetHandle_t xQueueSet;

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
    // // ��������3
    // xTaskCreate(vTask3Func, "task3", TASK3_STACK_SIZE, NULL, TASK3_PRIORITY, &xTask3Handle);

    // ��������
    xQueue = xQueueCreate(1, sizeof(uint8_t));
    // �����������ź���
    xBinarySemaphore = xSemaphoreCreateBinary();

    // �������м�
    xQueueSet = xQueueCreateSet(2);
    if (xQueueSet != NULL)
    {
        printf("���м������ɹ�\n");

        // ��������ӵ����м���
        if (xQueueAddToSet(xQueue, xQueueSet) == pdPASS)
        {
            printf("������ӵ����м��ɹ�\n");
        }

        // ���������ź�����ӵ����м���
        if (xQueueAddToSet(xBinarySemaphore, xQueueSet) == pdPASS)
        {
            printf("�������ź�����ӵ����м��ɹ�\n");
        }
    }

    // �˳��ٽ���
    taskEXIT_CRITICAL();

    // �������������
    vTaskStartScheduler();
}

// ����1����ʵ��
void vTask1Func(void *pvParameters)
{
    uint8_t key;

    while (1)
    {
        // ��ȡ����
        key = Int_Key_Detect();

        // ������� SW3 ����
        if (key == KEY_SW3)
        {
            printf("����1: ���� SW3 ���£�����з�������!\n");
            // �������ݵ�����
            xQueueSend(xQueue, &key, portMAX_DELAY);
        }
        // ������� SW4 ����
        else if (key == KEY_SW4)
        {
            printf("����1: ���� SW4 ���£��ͷŶ������ź���!\n");
            // �ͷŶ������ź���
            xSemaphoreGive(xBinarySemaphore);
        }

        // LED1 ��˸
        Int_LED_Toggle(LED1_Pin);

        // ������ʱ
        vTaskDelay(100);
    }
}

// ����2����ʵ��
void vTask2Func(void *pvParameters)
{
    // �����������ʾ��ȡ����Ϣ�Ķ��м��ĳ�Ա
    QueueSetMemberHandle_t xMember;
    // �����������Ϊ���н��ջ�����
    uint8_t queue_value;

    while (1)
    {
        printf("����2: ��ʼ ---------------\n");
        // �Ӷ��м��л�ȡ���ݣ��κζ��м���Ա����Ҫ�󶼿��Ի�ȡ������ȡ����������
        xMember = xQueueSelectFromSet(xQueueSet, portMAX_DELAY);

        printf("����2: �Ӷ��м���ȡ���ݳɹ�\n");

        // �����ȡ����Ϣ�Ķ���
        if (xMember == xQueue)
        {
            // �Ӷ����н������ݲ�ɾ��
            xQueueReceive(xQueue, &queue_value, portMAX_DELAY);
            printf("����2: �Ӷ��л�ȡ����: %d \n", queue_value);
        }
        // �����ȡ����Ϣ���Ƕ������ź���
        else if (xMember == xBinarySemaphore)
        {
            // ��ȡ���������ź���
            xSemaphoreTake(xBinarySemaphore, portMAX_DELAY);
            printf("����2: �Ӷ������ź�����ȡ���ݳɹ�\n");
        }

        printf("����2: ����----------------\n");
    }
}

// // ����3����ʵ��
// void vTask3Func(void *pvParameters)
// {
//     while (1)
//     {
//         printf("\n�����ȼ�����3: ��ʼ -------------------------");

//         // ��ȡ�ź���
//         xSemaphoreTake(xMutexSemaphore, portMAX_DELAY);
//         printf("\n�����ȼ�����3: ��ȡ�����ź����ɹ�");

//         // ��ʱ 1s
//         HAL_Delay(1000);

//         // �ͷ��ź���
//         xSemaphoreGive(xMutexSemaphore);
//         printf("\n�����ȼ�����3: �ͷŻ����ź����ɹ�");

//         printf("\n�����ȼ�����3: ���� -------------------------");

//         // ������ʱ
//         vTaskDelay(100);
//     }
// }
