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
    // �����������¼������ڴ�ĵ�ַ
    void *pvMemoryAddr = NULL;

    uint8_t key;

    while (1)
    {
        key = Int_Key_Detect();

        // ������� SW3 ����
        if (key == KEY_SW3)
        {
            printf("���� SW3 ���£������ڴ�ռ�... \n");
            // �����ڴ�ռ�
            pvMemoryAddr = pvPortMalloc(100);
            if (pvMemoryAddr != NULL)
            {
                printf("�ڴ����ɹ�����ַΪ: %p \n", pvMemoryAddr);
            }
            else
            {
                printf("�ڴ����ʧ��... \n");
            }
        }
        // ������� SW4 ����
        else if (key == KEY_SW4)
        {
            printf("���� SW4 ���£��ͷ��ڴ�ռ�... \n");
            if (pvMemoryAddr != NULL)
            {
                vPortFree(pvMemoryAddr);
                pvMemoryAddr = NULL;
                printf("�ڴ��ͷųɹ�... \n");
            }
        }

        printf("ʣ����ڴ�ռ�: %d �ֽ�... \n", xPortGetFreeHeapSize());

        Int_LED_Toggle(LED1_Pin);

        vTaskDelay(1000);
    }
}
