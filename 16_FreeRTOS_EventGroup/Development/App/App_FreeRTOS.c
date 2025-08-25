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

// �����¼���ľ��
EventGroupHandle_t xEventGroup;


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

    // �����¼���
    xEventGroup = xEventGroupCreate();
    if (xEventGroup != NULL)
    {
        printf("�¼��鴴���ɹ�\n");
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
            printf("����1: ���� SW3 ����, �����¼���־λBIT0\n");
            // �����¼���־λBIT0
            xEventGroupSetBits(xEventGroup, EVENT_GROUP_BIT0);
        }
        // ������� SW4 ����
        else if (key == KEY_SW4)
        {
            printf("����1: ���� SW4 ����, �����¼���־λBIT1\n");
            // �����¼���־λBIT1
            xEventGroupSetBits(xEventGroup, EVENT_GROUP_BIT1);          
        }
        // ������� SW5 ����
        else if (key == KEY_SW5)
        {
            printf("����1: ���� SW5 ����, �����¼���־λBIT2\n");
            // �����¼���־λBIT2
            xEventGroupSetBits(xEventGroup, EVENT_GROUP_BIT2);
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
    // ���������Ϊ�����������
    EventBits_t uxEventBits;

    while (1)
    {
        printf("����2: ��ʼ ---------------\n");
        
        // �ȴ��¼����־λ BIT0��BIT1��BIT2
        uxEventBits = xEventGroupWaitBits(xEventGroup, EVENT_GROUP_BIT0 | EVENT_GROUP_BIT1 | EVENT_GROUP_BIT2, pdTRUE, pdTRUE, portMAX_DELAY);
        printf("����2: �ȴ��¼����־λ BIT0��BIT1��BIT2 �ɹ�, �¼��������:%d \n", uxEventBits);

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
