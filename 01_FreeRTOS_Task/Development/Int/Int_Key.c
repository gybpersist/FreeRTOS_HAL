#include "Int_Key.h"

// 函数原型: 检测按键SW3是否被按下  被按下返回 1，否则返回 0， 该函数需要被轮询调用
uint8_t Key_SW3_Detect(void)
{
    // 如果检测到低电平
    if (HAL_GPIO_ReadPin(SW3_GPIO_Port, SW3_Pin) == GPIO_PIN_RESET)
    {
        // 延时10ms，用于消抖
        HAL_Delay(10);
        // 再次检测是否还是低电平
        if (HAL_GPIO_ReadPin(SW3_GPIO_Port, SW3_Pin) == GPIO_PIN_RESET)
        {
             return 1;
        }

    }

    return 0;
}
