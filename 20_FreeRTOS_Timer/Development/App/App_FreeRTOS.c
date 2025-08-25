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


// ����һ���Զ�ʱ����ز��� ----------------------------
// ����һ���Զ�ʱ�����
TimerHandle_t xTimer1;
// ����һ���Զ�ʱ���ص�������ԭ��
void vTimer1Callback(TimerHandle_t xTimer);

// ���������Զ�ʱ����ز��� ----------------------------
// ���������Զ�ʱ�����
TimerHandle_t xTimer2;
// ���������Զ�ʱ���ص�������ԭ��
void vTimer2Callback(TimerHandle_t xTimer);



/**
 * @brief FreeRTOS ��������
 */
void App_FreeRTOS_Start(void)
{
    // �����ٽ���
    taskENTER_CRITICAL();

    // ��������1
    xTaskCreate(vTask1Func, "task1", TASK1_STACK_SIZE, NULL, TASK1_PRIORITY, &xTask1Handle);

    // ����һ���Զ�ʱ��
    xTimer1 = xTimerCreate("Timer1", 5000, pdFALSE, (void *)0, vTimer1Callback);
    if (xTimer1 != NULL)
    {
        printf("һ���Զ�ʱ�������ɹ���\n");
    }

    // ���������Զ�ʱ��
    xTimer2 = xTimerCreate("Timer2", 5000, pdTRUE, (void *)1, vTimer2Callback);
    if (xTimer2 != NULL)
    {
        printf("�����Զ�ʱ�������ɹ���\n");
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
            printf("����1: SW3 ����, ����һ���Զ�ʱ�� \n");
            // ����һ���Զ�ʱ��
            xTimerStart(xTimer1, portMAX_DELAY);
        }
        // ������� SW4 ����
        if (key == KEY_SW4)
        {
            printf("����1: SW4 ����, ���������Զ�ʱ�� \n");
            // ���������Զ�ʱ��
            xTimerStart(xTimer2, portMAX_DELAY);
        }
       
        // LED1 ��˸
        Int_LED_Toggle(LED1_Pin);

        // ������ʱ
        vTaskDelay(100);
    }
}

// һ���Զ�ʱ���ص�����ʵ��
void vTimer1Callback(TimerHandle_t xTimer)
{
    static uint16_t count = 0;
    // ��ӡ��ʾ��Ϣ
    printf("һ���Զ�ʱ�������ˣ����ô�����%d \n", ++count);
}

// �����Զ�ʱ���ص�����ʵ��
void vTimer2Callback(TimerHandle_t xTimer)
{
    static uint16_t count = 0;
    // ��ӡ��ʾ��Ϣ
    printf("�����Զ�ʱ�������ˣ����ô�����%d \n", ++count);
}
