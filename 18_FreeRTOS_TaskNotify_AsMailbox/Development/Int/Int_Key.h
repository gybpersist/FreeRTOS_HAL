#ifndef __INT_KEY_H__
#define __INT_KEY_H__

#include "gpio.h"

// �궨�� �������
#define KEY_SW3 3
#define KEY_SW4 4
#define KEY_SW5 5
#define KEY_SW6 6

// �궨�� ����״̬
#define SW3_STATUS HAL_GPIO_ReadPin(SW3_GPIO_Port, SW3_Pin)
#define SW4_STATUS HAL_GPIO_ReadPin(SW4_GPIO_Port, SW4_Pin)
#define SW5_STATUS HAL_GPIO_ReadPin(SW5_GPIO_Port, SW5_Pin)
#define SW6_STATUS HAL_GPIO_ReadPin(SW6_GPIO_Port, SW6_Pin)


// ����ԭ��: ��ⰴ���Ƿ��£����ذ�����ţ�3��4��5��6����û�а��·���0���ú�����Ҫ����ѯ����
uint8_t Int_Key_Detect(void);

#endif /* __INT_KEY_H__ */
