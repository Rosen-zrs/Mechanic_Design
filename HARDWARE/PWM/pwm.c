#include "pwm.h"
#include "led.h"
//PWM �����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��

void MOTOR_GPIO_init(void)
{
	GPIO_InitTypeDef  GPIOB_InitStructure;
	GPIO_InitTypeDef  GPIOC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //ʹ��PB�˿�ʱ��	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	 //ʹ��PC�˿�ʱ��

	GPIOB_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8;				 // �˿�����
	GPIOB_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIOB_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	
	GPIOC_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2;				 //�˿�����
	GPIOC_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIOC_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	
	GPIO_Init(GPIOB, &GPIOB_InitStructure);					 //�����趨������ʼ��
	GPIO_Init(GPIOC, &GPIOC_InitStructure);
	
	GPIO_SetBits(GPIOB,GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8);				//����ߵ�ƽ		 
	GPIO_SetBits(GPIOC,GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2);	//��ʼ����Ϊ�ߵ�ƽ
	
}

void TIM3_DIANJI_PWM_Init(u16 arr,u16 psc)
{
		GPIO_InitTypeDef GPIOA_InitStructure;
	  GPIO_InitTypeDef GPIOB_InitStructure;
	
		TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
		TIM_OCInitTypeDef TIM_OCInitStructure;
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);// ��ʹ�� TIM3 ʱ��
	
	  //��ʹ�� GPIO ����ʱ��ʹ��
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);
   	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);
	
		
		//���ø�����Ϊ�����������,��� TIM3 CH2 �� PWM ���岨��
		GPIOA_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7; //TIM_CH1��ch2
		GPIOA_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //�����������
		GPIOA_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
		GPIOB_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1; //TIM_CH3��ch4
		GPIOB_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //�����������
		GPIOB_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	  GPIO_Init(GPIOA, &GPIOA_InitStructure);
		GPIO_Init(GPIOB, &GPIOB_InitStructure);
		
		TIM_TimeBaseStructure.TIM_Period = arr;
		//��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ 80K
		TIM_TimeBaseStructure.TIM_Prescaler =psc;
		//����������Ϊ TIMx ʱ��Ƶ�ʳ�����Ԥ��Ƶֵ ����Ƶ
		TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
		
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //���ϼ���
		TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //�ڳ�ʼ�� TIMx
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //�������ģʽ 2
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
		TIM_OCInitStructure.TIM_Pulse = 0; //���ô�װ�벶��ȽϼĴ���������ֵ
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //������Ը�
		
		TIM_OC1Init(TIM3, &TIM_OCInitStructure); //�۳�ʼ������ TIMxͨ��1
		TIM_OC2Init(TIM3, &TIM_OCInitStructure); //�۳�ʼ������ TIMxͨ��2
		TIM_OC3Init(TIM3, &TIM_OCInitStructure); //�۳�ʼ������ TIMxͨ��3
		TIM_OC4Init(TIM3, &TIM_OCInitStructure); //�۳�ʼ������ TIMxͨ��4
		
		TIM_CtrlPWMOutputs(TIM3,ENABLE); //��MOE �����ʹ��
		
		TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable); //CH1 Ԥװ��ʹ��
		TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable); //CH2 Ԥװ��ʹ��
		TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable); //CH3 Ԥװ��ʹ��
		TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable); //CH4 Ԥװ��ʹ��
		
		TIM_ARRPreloadConfig(TIM3, ENABLE); //ʹ�� TIMx �� ARR �ϵ�Ԥװ�ؼĴ���
		TIM_Cmd(TIM3, ENABLE); //��ʹ�� TIM3
	
}

//ȡ����ֵ����
int GFP_abs(int p)
{
  int q;
	
	if(p>0) q=p;
	else    q=-p;
	
	return q;
}

//���õ����PWM�Լ�ת��
void Set_qian_motor(int motor_01, int motor_02)
{
  if(motor_01>0)
	{
	  qian_AIN1=1;//��ת
		qian_AIN2=0;
	}
	else
	{
	  qian_AIN1=0;//��ת
		qian_AIN2=1;
	}
	//�о�pwmֵ
	TIM_SetCompare1(TIM3,GFP_abs(motor_01));//PA6
	
	
	if(motor_02>0)
	{
	  qian_BIN1=1;//��ת
		qian_BIN2=0;
	}
	else
	{
	  qian_BIN1=0;//��ת
		qian_BIN2=1;
	}
	//�о�pwmֵ
	TIM_SetCompare2(TIM3,GFP_abs(motor_02));//PA7
	
}

void Set_hou_motor(int motor_03, int motor_04)
{
  if(motor_03>0)
	{
	  hou_AIN1=1;//��ת
		hou_AIN2=0;
	}
	else
	{
	  hou_AIN1=0;//��ת
		hou_AIN2=1;
	}
	//�о�pwmֵ
	TIM_SetCompare3(TIM3,GFP_abs(motor_03));//PB0
	
	
	if(motor_04>0)
	{
	  hou_BIN1=1;//��ת
		hou_BIN2=0;
	}
	else
	{
	  hou_BIN1=0;//��ת
		hou_BIN2=1;
	}
	//�о�pwmֵ
	TIM_SetCompare4(TIM3,GFP_abs(motor_04));//PB1
	
}

void Set_chouji_motor(int motor_00)
{
  if(motor_00>0)
	{
	  yuan_AIN1=1;//��ת
		yuan_AIN2=0;
	}
	else
	{
	  yuan_AIN1=0;//��ת
		yuan_AIN2=1;
	}
	//�о�pwmֵ
	TIM_SetCompare4(TIM1,GFP_abs(motor_00));//PB0
	
	
	
	
}

//�����pwm,PA0,A1,A2,A3->ch1,ch2,ch3,ch4,CH1�ݲ���
void TIM2_DUOJI_PWM_Init(u16 arr,u16 psc)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
		TIM_OCInitTypeDef TIM_OCInitStructure;
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);// ��ʹ�� TIM2 ʱ��
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);
		//��ʹ�� GPIO ����ʱ��ʹ��
		//���ø�����Ϊ�����������,��� TIM2 CH2 �� PWM ���岨��
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3; 
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //�����������
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		
		TIM_TimeBaseStructure.TIM_Period = arr;
		//��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ 80K
		TIM_TimeBaseStructure.TIM_Prescaler =psc;
		//����������Ϊ TIMx ʱ��Ƶ�ʳ�����Ԥ��Ƶֵ ����Ƶ
		TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	  GPIO_Init(GPIOA, &GPIO_InitStructure);
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //���ϼ���
		TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //�ڳ�ʼ�� TIMx
	
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //�������ģʽ 2
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
		TIM_OCInitStructure.TIM_Pulse = 0; //���ô�װ�벶��ȽϼĴ���������ֵ
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //������Ը�
		
		
		TIM_OC2Init(TIM2, &TIM_OCInitStructure); //�۳�ʼ������ TIMx
		TIM_OC3Init(TIM2, &TIM_OCInitStructure); //�۳�ʼ������ TIMx
		TIM_OC4Init(TIM2, &TIM_OCInitStructure); //�۳�ʼ������ TIMx
		
		TIM_CtrlPWMOutputs(TIM2,ENABLE); //��MOE �����ʹ��
		
		
		TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable); //CH2 Ԥװ��ʹ��//PA1
		TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable); //CH3 Ԥװ��ʹ��//PA2
		TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable); //CH4 Ԥװ��ʹ��//PA3
		
		TIM_ARRPreloadConfig(TIM2, ENABLE); //ʹ�� TIMx �� ARR �ϵ�Ԥװ�ؼĴ���
		TIM_Cmd(TIM2, ENABLE); //��ʹ�� TIM2
	
	
	
}

//ԲͲ���ſ���PA11��ͨ��4������ĳ��룺PA8��ͨ��1
void TIM1_YUANTONG_PWM_Init(u16 arr,u16 psc)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
		TIM_OCInitTypeDef TIM_OCInitStructure;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);// ��ʹ�� TIM1 ʱ��
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);
		//��ʹ�� GPIO ����ʱ��ʹ��
		//���ø�����Ϊ�����������,��� TIM1 CH2 �� PWM ���岨��
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_11; //TIM_CH1
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //�����������
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		
		TIM_TimeBaseStructure.TIM_Period = arr;
		//��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ 80K
		TIM_TimeBaseStructure.TIM_Prescaler =psc;
		//����������Ϊ TIMx ʱ��Ƶ�ʳ�����Ԥ��Ƶֵ ����Ƶ
		TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	  GPIO_Init(GPIOA, &GPIO_InitStructure);
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //���ϼ���
		TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //�ڳ�ʼ�� TIMx
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //�������ģʽ 2
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
		TIM_OCInitStructure.TIM_Pulse = 0; //���ô�װ�벶��ȽϼĴ���������ֵ
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //������Ը�
		
		TIM_OC1Init(TIM1, &TIM_OCInitStructure); //�۳�ʼ������ TIMx
		TIM_OC4Init(TIM1, &TIM_OCInitStructure); //�۳�ʼ������ TIMx
		
		TIM_CtrlPWMOutputs(TIM1,ENABLE); //��MOE �����ʹ��
		
		TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable); //CH2 Ԥװ��ʹ��
		TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable); //CH2 Ԥװ��ʹ��
		
		TIM_ARRPreloadConfig(TIM1, ENABLE); //ʹ�� TIMx �� ARR �ϵ�Ԥװ�ؼĴ���
		TIM_Cmd(TIM1, ENABLE); //��ʹ�� TIM1
	
	
	
}
//
void TIM4_CHUCUN_PWM_Init(u16 arr,u16 psc)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
		TIM_OCInitTypeDef TIM_OCInitStructure;
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);// ��ʹ�� TIM2 ʱ��
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);
		//��ʹ�� GPIO ����ʱ��ʹ��
		//���ø�����Ϊ�����������,��� TIM4 CH4 �� PWM ���岨��
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; 
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //�����������
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		
		TIM_TimeBaseStructure.TIM_Period = arr;
		//��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ 80K
		TIM_TimeBaseStructure.TIM_Prescaler =psc;
		//����������Ϊ TIMx ʱ��Ƶ�ʳ�����Ԥ��Ƶֵ ����Ƶ
		TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	  GPIO_Init(GPIOB, &GPIO_InitStructure);
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //���ϼ���
		TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //�ڳ�ʼ�� TIMx
	
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //�������ģʽ 2
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
		TIM_OCInitStructure.TIM_Pulse = 0; //���ô�װ�벶��ȽϼĴ���������ֵ
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //������Ը�
		
		
		
		TIM_OC4Init(TIM4, &TIM_OCInitStructure); //�۳�ʼ������ TIMx
		
		TIM_CtrlPWMOutputs(TIM4,ENABLE); //��MOE �����ʹ��
		
		
		
		TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable); //CH4 Ԥװ��ʹ��//PB9
		
		TIM_ARRPreloadConfig(TIM4, ENABLE); //ʹ�� TIMx �� ARR �ϵ�Ԥװ�ؼĴ���
		TIM_Cmd(TIM4, ENABLE); //��ʹ�� TIM2
	
	
	
}


