/**
  ******************************************************************************
  * @file    bsp_motor_control.c
  * @author  fire
  * @version V1.0
  * @date    2019-xx-xx
  * @brief   �������ӿ�
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ��  STM32 F407 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */ 

#include "./Encoder/bsp_encoder.h"

/* ��ʱ��������� */
__IO int16_t Encoder2_Overflow_Count = 0;

TIM_HandleTypeDef TIM_EncoderHandle;

/**
  * @brief  �������ӿ����ų�ʼ��
  * @param  ��
  * @retval ��
  */
static void Encoder2_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  
  /* ��ʱ��ͨ�����Ŷ˿�ʱ��ʹ�� */
  ENCODER2_TIM_CH1_GPIO_CLK_ENABLE();
  ENCODER2_TIM_CH2_GPIO_CLK_ENABLE();
  
  /**TIM3 GPIO Configuration    
  PC6     ------> TIM3_CH1
  PC7     ------> TIM3_CH2 
  */
  /* ������������ */
  GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
  /* �������� */
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  /* ������������ */
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  
  /* ѡ��Ҫ���Ƶ�GPIO���� */	
  GPIO_InitStruct.Pin = ENCODER2_TIM_CH1_PIN;
  /* ���ø��� */
  GPIO_InitStruct.Alternate = ENCODER2_TIM_CH1_GPIO_AF;
  /* ���ÿ⺯����ʹ���������õ�GPIO_InitStructure��ʼ��GPIO */
  HAL_GPIO_Init(ENCODER2_TIM_CH1_GPIO_PORT, &GPIO_InitStruct);
  
  /* ѡ��Ҫ���Ƶ�GPIO���� */	
  GPIO_InitStruct.Pin = ENCODER2_TIM_CH2_PIN;
  /* ���ø��� */
  GPIO_InitStruct.Alternate = ENCODER2_TIM_CH2_GPIO_AF;
  /* ���ÿ⺯����ʹ���������õ�GPIO_InitStructure��ʼ��GPIO */
  HAL_GPIO_Init(ENCODER2_TIM_CH2_GPIO_PORT, &GPIO_InitStruct);
}

/**
  * @brief  ����TIMx������ģʽ
  * @param  ��
  * @retval ��
  */
static void TIM_Encoder2_Init(void)
{ 
  TIM_Encoder_InitTypeDef Encoder_ConfigStructure;
  
  /* ʹ�ܱ������ӿ�ʱ�� */
  ENCODER2_TIM_CLK_ENABLE();
  
  /* ��ʱ����ʼ������ */
  TIM_EncoderHandle.Instance = ENCODER2_TIM;
  TIM_EncoderHandle.Init.Prescaler = ENCODER2_TIM_PRESCALER;
  TIM_EncoderHandle.Init.CounterMode = TIM_COUNTERMODE_UP;
  TIM_EncoderHandle.Init.Period = ENCODER2_TIM_PERIOD;
  TIM_EncoderHandle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  TIM_EncoderHandle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  
  /* ���ñ�������Ƶ�� */
  Encoder_ConfigStructure.EncoderMode = ENCODER2_MODE;
  /* �������ӿ�ͨ��1���� */
  Encoder_ConfigStructure.IC1Polarity = ENCODER2_IC1_POLARITY;
  Encoder_ConfigStructure.IC1Selection = TIM_ICSELECTION_DIRECTTI;
  Encoder_ConfigStructure.IC1Prescaler = TIM_ICPSC_DIV1;
  Encoder_ConfigStructure.IC1Filter = 0;
  /* �������ӿ�ͨ��2���� */
  Encoder_ConfigStructure.IC2Polarity = ENCODER2_IC2_POLARITY;
  Encoder_ConfigStructure.IC2Selection = TIM_ICSELECTION_DIRECTTI;
  Encoder_ConfigStructure.IC2Prescaler = TIM_ICPSC_DIV1;
  Encoder_ConfigStructure.IC2Filter = 0;
  /* ��ʼ���������ӿ� */
  HAL_TIM_Encoder_Init(&TIM_EncoderHandle, &Encoder_ConfigStructure);
  
  /* ��������� */
  __HAL_TIM_SET_COUNTER(&TIM_EncoderHandle, 0);
  
  /* �����жϱ�־λ */
  __HAL_TIM_CLEAR_IT(&TIM_EncoderHandle,TIM_IT_UPDATE);
  /* ʹ�ܶ�ʱ���ĸ����¼��ж� */
  __HAL_TIM_ENABLE_IT(&TIM_EncoderHandle,TIM_IT_UPDATE);
  /* ���ø����¼�����ԴΪ����������� */
  __HAL_TIM_URS_ENABLE(&TIM_EncoderHandle);
  
  /* �����ж����ȼ� */
  HAL_NVIC_SetPriority(ENCODER2_TIM_IRQn, 0, 1);
  /* ʹ�ܶ�ʱ���ж� */
  HAL_NVIC_EnableIRQ(ENCODER2_TIM_IRQn);
  
  /* ʹ�ܱ������ӿ� */
  HAL_TIM_Encoder_Start(&TIM_EncoderHandle, TIM_CHANNEL_ALL);
}

/**
  * @brief  �������ӿڳ�ʼ��
  * @param  ��
  * @retval ��
  */
void Encoder_Init(void)
{
  Encoder2_GPIO_Init();    /* ���ų�ʼ�� */
  TIM_Encoder2_Init();     /* ���ñ������ӿ� */
}

///**
//  * @brief  ��ʱ�������¼��ص�����
//  * @param  ��
//  * @retval ��
//  */
//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
//{
//  /* �жϵ�ǰ�������������� */
//  if(__HAL_TIM_IS_TIM_COUNTING_DOWN(&TIM_EncoderHandle))
//    /* ���� */
//    Encoder_Overflow_Count--;
//  else
//    /* ���� */
//    Encoder_Overflow_Count++;
//}

/*********************************************END OF FILE**********************/
