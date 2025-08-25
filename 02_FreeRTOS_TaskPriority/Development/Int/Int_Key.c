#include "Int_Key.h"

// ����ԭ��: ��ⰴ��SW3�Ƿ񱻰���  �����·��� 1�����򷵻� 0�� �ú�����Ҫ����ѯ����
uint8_t Key_SW3_Detect(void)
{
    // �����⵽�͵�ƽ
    if (HAL_GPIO_ReadPin(SW3_GPIO_Port, SW3_Pin) == GPIO_PIN_RESET)
    {
        // ��ʱ10ms����������
        HAL_Delay(10);
        // �ٴμ���Ƿ��ǵ͵�ƽ
        if (HAL_GPIO_ReadPin(SW3_GPIO_Port, SW3_Pin) == GPIO_PIN_RESET)
        {
             return 1;
        }

    }

    return 0;
}
