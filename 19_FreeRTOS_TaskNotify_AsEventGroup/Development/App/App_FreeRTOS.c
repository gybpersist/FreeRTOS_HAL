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
// #define TASK3_STACK_SIZE 128
// // ��������3���ȼ�
// #define TASK3_PRIORITY 3
// // ��������3���
// TaskHandle_t xTask3Handle;
// // ����3������ԭ��
// void vTask3Func(void *pvParameters);

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
            printf("����1: ���� SW3 ����, ����־λBIT0��1\n");
            // ������2��֪ͨ������ֵ֪ͨ
            xTaskNotify(xTask2Handle, EVENT_GROUP_BIT0, eSetBits);
        }
        // ������� SW4 ����
        if (key == KEY_SW4)
        {
            printf("����1: ���� SW4 ����, ����־λBIT1��1\n");
            // ������2��֪ͨ������ֵ֪ͨ
            xTaskNotify(xTask2Handle, EVENT_GROUP_BIT1, eSetBits);
        }
        // ������� SW5 ����
        if (key == KEY_SW5)
        {
            printf("����1: ���� SW5 ����, ����־λBIT2��1\n");
            // ������2��֪ͨ������ֵ֪ͨ
            xTaskNotify(xTask2Handle, EVENT_GROUP_BIT2, eSetBits);
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
    // ������������� ��������ֵ֪ͨ
    uint32_t ulReceivedValue = 0;
    // �����������Ϊʱ���־��
    uint32_t ulEventGroup = 0;

    while (1)
    {
        printf("����2: ��ʼ ---------------\n");

        // �ȴ���������֪ͨ,����ȡֵ֪ͨ
        xTaskNotifyWait(0xFFFFFFFF, 0xFFFFFFFF, &ulReceivedValue, portMAX_DELAY);
        // printf("����2: �յ�����֪ͨ, ֵ֪ͨ��%d \n", ulReceivedValue);

        // ��������ֵ֪ͨ
        if (ulReceivedValue & EVENT_GROUP_BIT0)
        {
            // ���¼����־λBIT0��1
            ulEventGroup |= EVENT_GROUP_BIT0;
        }
        if (ulReceivedValue & EVENT_GROUP_BIT1)
        {
            // ���¼����־λBIT1��1
            ulEventGroup |= EVENT_GROUP_BIT1;
        }
        if (ulReceivedValue & EVENT_GROUP_BIT2)
        {
            // ���¼����־λBIT2��1
            ulEventGroup |= EVENT_GROUP_BIT2;
        }

        // ���EventGroup �е�BIT0��BIT1��BIT2 ����1
        if (ulEventGroup == (EVENT_GROUP_BIT0 | EVENT_GROUP_BIT1 | EVENT_GROUP_BIT2))
        {
            printf("����2: �¼����־λBIT0��BIT1��BIT2 ����1, �¼����־: %d \n", ulEventGroup);
            // ulEventGroup ��λ
            ulEventGroup = 0;
        }


        printf("����2: ����----------------\n");
    }
}

// // ����3����ʵ��
// void vTask3Func(void *pvParameters)
// {
//     while (1)
//     {

//         printf("����3: ������1����֪ͨ, ֵ֪ͨ+1, ģ������ź���...\n");
//         // ������1����֪ͨ, ֵ֪ͨ+1, ģ������ź���
//         xTaskNotifyGive(xTask1Handle);

//         // ������ʱ
//         vTaskDelay(2000);
//     }
// }
