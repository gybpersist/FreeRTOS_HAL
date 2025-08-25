#include "App_FreeRTOS.h"

// ��������1��صĲ��� -----------------
// ��������1��ջ��С
#define TASK1_STACK_SIZE 128
// ��������1���ȼ�
#define TASK1_PRIORITY 1
// ��������1���
TaskHandle_t xTask1Handle;
// �������飨�洢��ȫ�־�̬��������Ϊ��̬��ʽ�����������ջ
StackType_t pxTask1Stack[TASK1_STACK_SIZE];
// ��������1�Ŀ��ƿ�
StaticTask_t xTask1TCB;
// ����1������ԭ��
void vTask1Func(void *pvParameters);

// ��������2��صĲ��� -----------------
// ��������2��ջ��С
#define TASK2_STACK_SIZE 128
// ��������2���ȼ�
#define TASK2_PRIORITY 2
// ��������2���
TaskHandle_t xTask2Handle;
// ���徲̬��ʽ��������2��ջ
StackType_t pxTask2Stack[TASK2_STACK_SIZE];
// ��̬��ʽ��������2�Ŀ��ƿ�
StaticTask_t xTask2TCB;
// ����2������ԭ��
void vTask2Func(void *pvParameters);

// ��������3��صĲ��� -----------------
// ��������3��ջ��С
#define TASK3_STACK_SIZE 128
// ��������3���ȼ�
#define TASK3_PRIORITY 3
// ��������3���
TaskHandle_t xTask3Handle;
// ���徲̬��ʽ��������3��ջ
StackType_t pxTask3Stack[TASK3_STACK_SIZE];
// ��̬��ʽ��������3�Ŀ��ƿ�
StaticTask_t xTask3TCB;
// ����3������ԭ��
void vTask3Func(void *pvParameters);

/**
 * @brief FreeRTOS ��������
 */
void App_FreeRTOS_Start(void)
{
    // �����ٽ���
    taskENTER_CRITICAL();

    // ��̬��ʽ��������1
    xTask1Handle = xTaskCreateStatic(vTask1Func, "Task1", TASK1_STACK_SIZE, NULL, TASK1_PRIORITY, pxTask1Stack, &xTask1TCB);
    // ��̬��ʽ��������2
    xTask2Handle = xTaskCreateStatic(vTask2Func, "Task2", TASK2_STACK_SIZE, NULL, TASK2_PRIORITY, pxTask2Stack, &xTask2TCB);
    // ��̬��ʽ��������3
    xTask3Handle = xTaskCreateStatic(vTask3Func, "Task3", TASK3_STACK_SIZE, NULL, TASK3_PRIORITY, pxTask3Stack, &xTask3TCB);

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
        // ����������500ms֮��ȡ������
        vTaskDelay(500);
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

    // while (1)
    // {
    //     // LED3 ����״̬�л�
    //     Int_LED_Toggle(LED3_Pin);
    //     // ����������500ms֮��ȡ������
    //     vTaskDelay(500);
    // }

    while (1)
    {
        // �����⵽SW3����������
        if (Key_SW3_Detect())
        {
            // ɾ������1
            if (xTask1Handle != NULL)
            {
                vTaskDelete(xTask1Handle);
                xTask1Handle = NULL;
            }
        }

        // ����������100ms֮��ȡ������
        vTaskDelay(100);
    }
}

// �ض���Ϊ�����������ջ�ڴ�ĺ���
void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer,
                                   StackType_t **ppxIdleTaskStackBuffer,
                                   uint32_t *pulIdleTaskStackSize)
{
    // �ھ�̬��������������Ŀ��ƿ�
    static StaticTask_t pxIdleTaskTCB;
    *ppxIdleTaskTCBBuffer = &pxIdleTaskTCB;

    // �ھ�̬��������������ʹ�õ�ջ�ռ�
    static StackType_t pxIdleTaskStack[configMINIMAL_STACK_SIZE];
    *ppxIdleTaskStackBuffer = pxIdleTaskStack;

    // ���ÿ��������ջ��С
    *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
   
}
