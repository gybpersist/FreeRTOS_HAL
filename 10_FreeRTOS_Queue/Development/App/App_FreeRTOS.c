#include "App_FreeRTOS.h"

// ��������1��صĲ��� -----------------
// ��������1��ջ��С
#define TASK1_STACK_SIZE 128
// ��������1���ȼ�
#define TASK1_PRIORITY 4
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

// ������еľ��
QueueHandle_t xQueue1;
QueueHandle_t xQueue2;

// �����ַ�������Ϊ�����2���͵�����
// char *tx_msg = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
char tx_msg[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

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

    // ��������1���������ȣ�ÿ����Ŀ1�ֽ�
    xQueue1 = xQueueCreate(2, sizeof(uint8_t));
    if (xQueue1 != NULL)
    {
        printf("����1�����ɹ�\n");
    }

    // ��������2,1�����ȣ�����ַ�����ַ
    xQueue2 = xQueueCreate(1, sizeof(char *));
    if (xQueue2 != NULL)
    {
        printf("����2�����ɹ�\n");
    }

    // �˳��ٽ���
    taskEXIT_CRITICAL();

    // �������������
    vTaskStartScheduler();
}

// ����1����ʵ��
void vTask1Func(void *pvParameters)
{
    printf("����1����...\n");
    uint8_t key;

    while (1)
    {
    
        // ��ȡ������⺯������ֵ
        key = Int_Key_Detect();

        // �������SW3���߰���SW4
        if (key == KEY_SW3 || key == KEY_SW4)
        {
            // �����1������Ϣ�����Ͱ���ֵ3
            if (xQueueSend(xQueue1, &key, portMAX_DELAY) == pdTRUE)
            {
                printf("\n����1:: �����1������Ϣ�ɹ�, ��������Ϊ: %d \n", key);
            }
            else
            {
                printf("\n����1:: ����з�������ʧ�ܣ�\n");
            }
        }

        // �������SW5
        else if (key == KEY_SW5)
        {
            // �����2������Ϣ������tx_msg
            if (xQueueSend(xQueue2, &tx_msg, portMAX_DELAY) == pdTRUE)
            {
                printf("\n����1:: �����2������Ϣ�ɹ�,���͵����ַ����ĵ�ַ:%p \n", tx_msg);
            }
            else
            {
                printf("\n����1:: �����2��������ʧ�ܣ�\n");
            }

        }

        // ������ʱ
        vTaskDelay(500);
    }
}

// ����2����ʵ��
void vTask2Func(void *pvParameters)
{

    // �����������Ϊ����1�Ľ��ջ�����
    uint8_t rx_value;

    printf("����2����...\n");

    while (1)
    {
        if (xQueueReceive(xQueue1, &rx_value, portMAX_DELAY) == pdTRUE)
        {
            printf("\n����2��: ���յ�����1�е�����: %d \n", rx_value);
        }
        else
        {
            printf("\n����2��: ���ն���1����ʧ��! \n");
        }
    }
}

// ����3����ʵ��
void vTask3Func(void *pvParameters)
{
    printf("����3����...\n");

    // �������飬��Ϊ���ջ�����
    char *rx_buffer = NULL;
    // memset(rx_buffer, 0, 27);

    while (1)
    {
        if (xQueueReceive(xQueue2, &rx_buffer, portMAX_DELAY) == pdTRUE)
        {
            printf("\n����3��: ���յ�����2�е�����: %p \n", rx_buffer);
        }
        else
        {
            printf("\n����3��: ���ն���2����ʧ��! \n");
        }    

    }
}
