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

/**
 * @brief FreeRTOS ��������
 */
void App_FreeRTOS_Start(void)
{
    // �����ٽ���
    taskENTER_CRITICAL();

    // ��������1
    xTaskCreate(vTask1Func, "task1", TASK1_STACK_SIZE, NULL, TASK1_PRIORITY, &xTask1Handle);

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
        printf("����1����... \n");
        Int_LED_Toggle(LED1_Pin);
        vTaskDelay(1000);
    }
}

// ����ʵ�֣�������TickLessģʽʱ������øú���
void vEnterTicklessExec(uint32_t time)
{
    printf("����TickLessģʽ, ��ǰʱ��Ϊ��%d \n", time);
}

// ����ʵ�֣����˳�TickLessģʽʱ������øú���
void vExitTicklessExec(uint32_t time)
{
    printf("�˳�TickLessģʽ, ��ǰʱ��Ϊ��%d \n", time);
}
