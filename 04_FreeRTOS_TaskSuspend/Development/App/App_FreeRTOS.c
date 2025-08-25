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
#define TASK3_STACK_SIZE 512
// ��������3���ȼ�
#define TASK3_PRIORITY 3
// ��������3���
TaskHandle_t xTask3Handle;
// ����3������ԭ��
void vTask3Func(void *pvParameters);

// �����ַ��������ڱ�������״̬��Ϣ
char pcTaskInfo[256];

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
       // printf("����1��������...\n");
        // LED1 ����״̬�л�
        Int_LED_Toggle(LED1_Pin);
        // ��ʱ500ms
        HAL_Delay(500);
    }
}

// ����2����ʵ��
void vTask2Func(void *pvParameters)
{
    printf("����2����...\n");
    while (1)
    {
       // printf("����2��������...\n");
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

    uint8_t key;

    while (1)
    {
      //  printf("����3��������...\n");

        // ��ȡ������⺯������ֵ
        key = Int_Key_Detect();

        // �������SW3
        if (key == KEY_SW3)
        {
            printf("����SW3����, ����1����\n");
            // ��������1
            vTaskSuspend(xTask1Handle);
        }
        // // �������SW4
        // else if (key == KEY_SW4)
        // {
        //     printf("����SW4����, ����1�ָ�\n");
        //     // �ָ�����1
        //     vTaskResume(xTask1Handle);
        // }
        // �������SW5
        else if (key == KEY_SW5)
        {
            printf("����SW5����, ���������\n");
            // ���������
            vTaskSuspendAll();
        }
        // �������SW6
        else if (key == KEY_SW6)
        {
            printf("����SW6����, �ָ�������\n");
            // �ָ�������
            xTaskResumeAll();
        }

        // ��ȡ����״̬��Ϣ
        vTaskList(pcTaskInfo);
        // ��ӡ����״̬��Ϣ
        printf("\n%s\n", pcTaskInfo);


        // ������ʱ
        vTaskDelay(500);
    }
}


// �ض��� EXTI9_5 ������SW4(PF9) ����������õ�������
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    // ����ǰ���SW4����
    if (GPIO_Pin == SW4_Pin)
    {
        // ��ʱ10ms ����
        HAL_Delay(10);
        // �ٴ��ж�SW4�Ƿ񱻰���
        if (HAL_GPIO_ReadPin(SW4_GPIO_Port, SW4_Pin) == GPIO_PIN_RESET)
        {
            printf("����SW4����, ����1�ָ�\n");
            // �ָ�����1
            xTaskResumeFromISR(xTask1Handle);     
        }       
    }
}
