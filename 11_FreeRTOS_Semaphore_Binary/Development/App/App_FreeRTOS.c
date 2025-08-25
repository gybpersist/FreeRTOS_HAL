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
    // // ��������3
    // xTaskCreate(vTask3Func, "task3", TASK3_STACK_SIZE, NULL, TASK3_PRIORITY, &xTask3Handle);

    // �����������ź���
    xBinarySemaphore = xSemaphoreCreateBinary();
    if (xBinarySemaphore != NULL)
    {
        printf("�����������ź����ɹ���\n");
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

        // ������� SW3 ����
        if (key == KEY_SW3)
        {
            printf("\n����1: ׼���ͷŶ������ź���\n");

            // �ͷŶ������ź���
            if (xSemaphoreGive(xBinarySemaphore) == pdTRUE)
            {
                printf("\n����1: �ͷŶ������ź����ɹ�\n");
            }
        }

        // ����LED1��˸
        Int_LED_Toggle(LED1_Pin);

        // ������ʱ
        vTaskDelay(500);
    }
}

// ����2����ʵ��
void vTask2Func(void *pvParameters)
{
    printf("����2����...\n");

    while (1)
    {
        printf("\n����2: ��ʼ-----------------------------");
        
        printf("\n����2: ׼����ȡ�������ź���\n");
        // ��ȡ�������ź���
        xSemaphoreTake(xBinarySemaphore, portMAX_DELAY);
        printf("\n����2: ��ȡ�������ź����ɹ�\n");
        
        printf("\n����2: ����-----------------------------");
    }
}

// // ����3����ʵ��
// void vTask3Func(void *pvParameters)
// {
//     printf("����3����...\n");

//     // �������飬��Ϊ���ջ�����
//     char *rx_buffer = NULL;
//     // memset(rx_buffer, 0, 27);

//     while (1)
//     {
//         if (xQueueReceive(xQueue2, &rx_buffer, portMAX_DELAY) == pdTRUE)
//         {
//             printf("\n����3��: ���յ�����2�е�����: %s \n", rx_buffer);
//         }
//         else
//         {
//             printf("\n����3��: ���ն���2����ʧ��! \n");
//         }    

//     }
// }
