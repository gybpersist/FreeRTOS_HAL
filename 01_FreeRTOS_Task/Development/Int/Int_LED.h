#ifndef __INT_LED_H__
#define __INT_LED_H__

#include "gpio.h"

// ����ԭ�ͣ�����ָ����LED
void Int_LED_On(uint16_t GPIO_Pin);

// ����ԭ�ͣ�Ϩ��ָ����LED
void Int_LED_Off(uint16_t GPIO_Pin);

// ����ԭ�ͣ��л�ָ����LED
void Int_LED_Toggle(uint16_t GPIO_Pin);


#endif /* __INT_LED_H__ */
