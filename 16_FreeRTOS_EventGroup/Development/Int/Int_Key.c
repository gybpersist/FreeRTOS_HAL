#include "Int_Key.h"

// 函数实现: 检测按键是否按下，返回按键编号（3、4、5、6），没有按下返回0；该函数需要被轮询调用
uint8_t Int_Key_Detect(void)
{
    // 如果检测到按键被按下
    if (SW3_STATUS == GPIO_PIN_RESET || SW4_STATUS == GPIO_PIN_RESET || SW5_STATUS == GPIO_PIN_SET || SW6_STATUS == GPIO_PIN_SET)
    {
        // 延时10ms，进行消抖
        HAL_Delay(10);

        // 再次检查按键SW3是否仍然是按下状态
        if (SW3_STATUS == GPIO_PIN_RESET)
        {
            return KEY_SW3;
        }

        // 检测按键SW4是否被按下
        if (SW4_STATUS == GPIO_PIN_RESET)
        {
            return KEY_SW4;
        }

        // 检测按键SW5是否被按下
        if (SW5_STATUS == GPIO_PIN_SET)
        {
            return KEY_SW5;
        }

        // 检测按键SW6是否被按下
        if (SW6_STATUS == GPIO_PIN_SET)
        {
            return KEY_SW6;
        }
    }

    return 0;
}
