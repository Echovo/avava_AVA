#ifndef __BSP_ENCOEDER_H
#define	__BSP_ENCOEDER_H

#include "stm32f4xx.h"

/* 定时器选择 */
#define ENCODER2_TIM                            TIM3
#define ENCODER2_TIM_CLK_ENABLE()  				     __HAL_RCC_TIM3_CLK_ENABLE()

/* 定时器溢出值 */		
#define ENCODER2_TIM_PERIOD                     65535
/* 定时器预分频值 */
#define ENCODER2_TIM_PRESCALER                  0      

/* 定时器中断 */
#define ENCODER2_TIM_IRQn                       TIM3_IRQn
#define ENCODER2_TIM_IRQHandler                 TIM3_IRQHandler

/* 编码器接口引脚 */
#define ENCODER2_TIM_CH1_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOC_CLK_ENABLE()
#define ENCODER2_TIM_CH1_GPIO_PORT              GPIOC
#define ENCODER2_TIM_CH1_PIN                    GPIO_PIN_6
#define ENCODER2_TIM_CH1_GPIO_AF                GPIO_AF2_TIM3

#define ENCODER2_TIM_CH2_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOC_CLK_ENABLE()
#define ENCODER2_TIM_CH2_GPIO_PORT              GPIOC
#define ENCODER2_TIM_CH2_PIN                    GPIO_PIN_7
#define ENCODER2_TIM_CH2_GPIO_AF                GPIO_AF2_TIM3

/* 编码器接口倍频数 */
#define ENCODER2_MODE                           TIM_ENCODERMODE_TI12

/* 编码器接口输入捕获通道相位设置 */
#define ENCODER2_IC1_POLARITY                   TIM_ICPOLARITY_RISING
#define ENCODER2_IC2_POLARITY                   TIM_ICPOLARITY_RISING

/* 编码器物理分辨率 */
#define ENCODER2_RESOLUTION                     11

/* 经过倍频之后的总分辨率 */
#if (ENCODER2_MODE == TIM_ENCODERMODE_TI12)
  #define ENCODER2_TOTAL_RESOLUTION             (ENCODER2_RESOLUTION * 4)  /* 4倍频后的总分辨率 */
#else
  #define ENCODER2_TOTAL_RESOLUTION             (ENCODER2_RESOLUTION * 2)  /* 2倍频后的总分辨率 */
#endif

/* 减速电机减速比 */
#define REDUCTION_RATIO                        50

extern __IO int16_t Encoder2_Overflow_Count;
extern TIM_HandleTypeDef TIM_EncoderHandle;

void Encoder_Init(void);

#endif   /* __BSP_ENCODER_H */

