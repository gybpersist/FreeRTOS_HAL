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

// �����ַ��������ڱ�������״̬��Ϣ
// char pcTaskInfo[256];

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
        printf("\n----------------����1����ִ�� ---------------------\n");
        printf("����1����ִ��...\n");
        // LED1 ��˸
        Int_LED_Toggle(LED1_Pin);
        printf("------------------����1ִ�н��� ---------------------\n");

        // ������ʱ
        vTaskDelay(1000);
    }
}

// ����2����ʵ��
void vTask2Func(void *pvParameters)
{

    printf("����2����...\n");
    while (1)
    {
        printf("\n----------------����2����ִ�� ---------------------\n");

        // ��ȡ���������Ϣ
        printf("ϵͳ�е�����������%d \n", uxTaskGetNumberOfTasks());
        printf("����1�����ȼ�: %d; ����2�����ȼ�: %d \n", uxTaskPriorityGet(xTask1Handle), uxTaskPriorityGet(xTask2Handle));
        printf("����1����ʷ����ջ��Сʣ����: %d; ����2����ʷ����ջ��Сʣ����: %d \n", uxTaskGetStackHighWaterMark(xTask1Handle), uxTaskGetStackHighWaterMark(xTask2Handle));

        printf("------------------����2ִ�н��� ---------------------\n");

        vTaskDelay(1000);
    }
}

// ����3����ʵ��
void vTask3Func(void *pvParameters)
{
    printf("����3����...\n");

    uint8_t key;

    while (1)
    {
        //  printf("����3��������...\n");
        printf("\n----------------����3����ִ�� ---------------------\n");

        printf("����3����ִ��...\n");

        // ��ȡ������⺯������ֵ
        key = Int_Key_Detect();

        // �������SW3
        if (key == KEY_SW3)
        {
            printf("\n����SW3����, �޸�����1�����ȼ�Ϊ4 >>>>>>>>>>> \n");
            // �޸�����1�����ȼ�Ϊ4
            vTaskPrioritySet(xTask1Handle, 4);
        }

        printf("\n----------------����3���ڽ��� ---------------------\n");


        // ������ʱ
        vTaskDelay(500);
    }
}
