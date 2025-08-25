#include "Int_Key.h"

// ����ʵ��: ��ⰴ���Ƿ��£����ذ�����ţ�3��4��5��6����û�а��·���0���ú�����Ҫ����ѯ����
uint8_t Int_Key_Detect(void)
{
    // �����⵽����������
    if (SW3_STATUS == GPIO_PIN_RESET || SW4_STATUS == GPIO_PIN_RESET || SW5_STATUS == GPIO_PIN_SET || SW6_STATUS == GPIO_PIN_SET)
    {
        // ��ʱ10ms����������
        HAL_Delay(10);

        // �ٴμ�鰴��SW3�Ƿ���Ȼ�ǰ���״̬
        if (SW3_STATUS == GPIO_PIN_RESET)
        {
            return KEY_SW3;
        }

        // ��ⰴ��SW4�Ƿ񱻰���
        if (SW4_STATUS == GPIO_PIN_RESET)
        {
            return KEY_SW4;
        }

        // ��ⰴ��SW5�Ƿ񱻰���
        if (SW5_STATUS == GPIO_PIN_SET)
        {
            return KEY_SW5;
        }

        // ��ⰴ��SW6�Ƿ񱻰���
        if (SW6_STATUS == GPIO_PIN_SET)
        {
            return KEY_SW6;
        }
    }

    return 0;
}
