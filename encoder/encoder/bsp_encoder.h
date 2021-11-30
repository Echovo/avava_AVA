#ifndef __BSP_ENCOEDER_H
#define	__BSP_ENCOEDER_H

#include "stm32f4xx.h"

/* ��ʱ��ѡ�� */
#define ENCODER2_TIM                            TIM3
#define ENCODER2_TIM_CLK_ENABLE()  				     __HAL_RCC_TIM3_CLK_ENABLE()

/* ��ʱ�����ֵ */		
#define ENCODER2_TIM_PERIOD                     65535
/* ��ʱ��Ԥ��Ƶֵ */
#define ENCODER2_TIM_PRESCALER                  0      

/* ��ʱ���ж� */
#define ENCODER2_TIM_IRQn                       TIM3_IRQn
#define ENCODER2_TIM_IRQHandler                 TIM3_IRQHandler

/* �������ӿ����� */
#define ENCODER2_TIM_CH1_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOC_CLK_ENABLE()
#define ENCODER2_TIM_CH1_GPIO_PORT              GPIOC
#define ENCODER2_TIM_CH1_PIN                    GPIO_PIN_6
#define ENCODER2_TIM_CH1_GPIO_AF                GPIO_AF2_TIM3

#define ENCODER2_TIM_CH2_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOC_CLK_ENABLE()
#define ENCODER2_TIM_CH2_GPIO_PORT              GPIOC
#define ENCODER2_TIM_CH2_PIN                    GPIO_PIN_7
#define ENCODER2_TIM_CH2_GPIO_AF                GPIO_AF2_TIM3

/* �������ӿڱ�Ƶ�� */
#define ENCODER2_MODE                           TIM_ENCODERMODE_TI12

/* �������ӿ����벶��ͨ����λ���� */
#define ENCODER2_IC1_POLARITY                   TIM_ICPOLARITY_RISING
#define ENCODER2_IC2_POLARITY                   TIM_ICPOLARITY_RISING

/* ����������ֱ��� */
#define ENCODER2_RESOLUTION                     11

/* ������Ƶ֮����ֱܷ��� */
#if (ENCODER2_MODE == TIM_ENCODERMODE_TI12)
  #define ENCODER2_TOTAL_RESOLUTION             (ENCODER2_RESOLUTION * 4)  /* 4��Ƶ����ֱܷ��� */
#else
  #define ENCODER2_TOTAL_RESOLUTION             (ENCODER2_RESOLUTION * 2)  /* 2��Ƶ����ֱܷ��� */
#endif

/* ���ٵ�����ٱ� */
#define REDUCTION_RATIO                        50

extern __IO int16_t Encoder2_Overflow_Count;
extern TIM_HandleTypeDef TIM_EncoderHandle;

void Encoder_Init(void);

#endif   /* __BSP_ENCODER_H */

