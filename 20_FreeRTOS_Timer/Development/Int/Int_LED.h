#ifndef __INT_LED_H__
#define __INT_LED_H__

#include "gpio.h"

// 函数原型：点亮指定的LED
void Int_LED_On(uint16_t GPIO_Pin);

// 函数原型：熄灭指定的LED
void Int_LED_Off(uint16_t GPIO_Pin);

// 函数原型：切换指定的LED
void Int_LED_Toggle(uint16_t GPIO_Pin);


#endif /* __INT_LED_H__ */
