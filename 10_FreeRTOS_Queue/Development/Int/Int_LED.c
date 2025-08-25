#include "Int_LED.h"

// 函数实现：点亮指定的LED
void Int_LED_On(uint16_t GPIO_Pin)
{
    HAL_GPIO_WritePin(GPIOA, GPIO_Pin, GPIO_PIN_RESET);
}

// 函数原型：熄灭指定的LED
void Int_LED_Off(uint16_t GPIO_Pin)
{
    HAL_GPIO_WritePin(GPIOA, GPIO_Pin, GPIO_PIN_SET);
}

// 函数实现：切换指定的LED
void Int_LED_Toggle(uint16_t GPIO_Pin)
{
    HAL_GPIO_TogglePin(GPIOA, GPIO_Pin);
}
