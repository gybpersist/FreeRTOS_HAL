#include "Int_LED.h"

// ����ʵ�֣�����ָ����LED
void Int_LED_On(uint16_t GPIO_Pin)
{
    HAL_GPIO_WritePin(GPIOA, GPIO_Pin, GPIO_PIN_RESET);
}

// ����ԭ�ͣ�Ϩ��ָ����LED
void Int_LED_Off(uint16_t GPIO_Pin)
{
    HAL_GPIO_WritePin(GPIOA, GPIO_Pin, GPIO_PIN_SET);
}

// ����ʵ�֣��л�ָ����LED
void Int_LED_Toggle(uint16_t GPIO_Pin)
{
    HAL_GPIO_TogglePin(GPIOA, GPIO_Pin);
}
