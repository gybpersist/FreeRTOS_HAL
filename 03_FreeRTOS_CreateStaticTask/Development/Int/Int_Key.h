#ifndef __INT_KEY_H__
#define __INT_KEY_H__

#include "gpio.h"

// 函数原型: 检测按键SW3是否被按下  被按下返回 1，否则返回 0， 该函数需要被轮询调用
uint8_t Key_SW3_Detect(void);

#endif /* __INT_KEY_H__ */
