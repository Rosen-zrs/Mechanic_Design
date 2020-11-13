#include "sys.h"
#include "math.h"
#include "stdlib.h"

#define OUTPUT

 int main(void)
 {	
	 u8 key; 
	 int i;
	 int claw_angle=1850;//צ�Ӷ���ĽǶ�
	 
	 s16 speed,speed1,speed2; 
	 s16 swerve;           //ת����	 
	 
	 int first_angle = 1930;
	 int second_angle = 1905;
	 
	
	 delay_init(); //��ʱ������ʼ��
	 
	 delay_ms(100);
	 
	 Stm32_Clock_Init(9); //ϵͳʱ������
	 
	 LED_Init();
	 
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //���� NVIC �жϷ��� 2:2 λ
	 uart_init(9600);
	 
	 MOTOR_GPIO_init();
	 TIM3_DIANJI_PWM_Init(1999,719);//����Ƶ��  //PWMƵ��=72000000/(719+1)/(1999+1)=50hz=20mS
	 TIM2_DUOJI_PWM_Init(1999,719);
	 
	 PS2_Init();	

	 PS2_SetInit();		 //�����ó�ʼ��,���á����̵�ģʽ������ѡ���Ƿ�����޸�
	 
	 TIM_SetCompare2(TIM2,first_angle);
	 TIM_SetCompare3(TIM2,second_angle);
	 
	 
	 while(1)
	 {
		 if( !PS2_RedLight())
		 {
			 
			 delay_ms(50);	 //��ʱ����Ҫ����ȥ
			 
			 key = PS2_DataKey();	 //�ֱ�����������
				
			 speed = -(PS2_AnologData(PSS_LY)-127) * 10;	   
			 if(speed != 0)
			 {
				 swerve = (PS2_AnologData(PSS_RX)-128)* 5 *((float)abs(speed)/1270); //	speedȡ����ֵ��	�������㣬�õ�ת������
			 }
			 else swerve = (PS2_AnologData(PSS_RX)-128)* 8;
			 if(speed >= 0) //��ǰ
			 {
				 if(swerve < 0)//��ת�� 
				 {
					 speed1 = speed + swerve;
					 speed2 = speed - swerve;
				 }
				 else          //��ת��
				 {
					 speed1 = speed + swerve; 
					 speed2 = speed - swerve;;
				 }
			 }
			 else if(speed < 0)//���
			 {
				 if(swerve < 0)//��ת��
				 {
					 speed1 = speed - swerve;
					 speed2 = speed + swerve;
				 }
				 else//��ת��
				 {
					 speed1 = speed - swerve; 
					 speed2 = speed + swerve;;
				 }
			 }
			 Set_qian_motor(speed1, speed2);
			 Set_hou_motor(speed1, speed2);
			 
			 if(key)
			 {
				 switch(key)
				 {
					 //��е��һ���ؽ�
					 case PSB_L1:
					 {
						 delay_ms(20);
						 if(key == PSB_L1)
						 {
							 TIM_SetCompare2(TIM2,1880);//PA1��ֵ���޸�
							 delay_ms(10);
							 TIM_SetCompare2(TIM2,1890);//PA1��ֵ���޸�
							 delay_ms(10);
							 TIM_SetCompare2(TIM2,1900);//PA1��ֵ���޸�
							 delay_ms(10);
							 TIM_SetCompare2(TIM2,1910);//PA1��ֵ���޸�
							 delay_ms(30);
							 TIM_SetCompare2(TIM2,1920);//PA1��ֵ���޸�
							 delay_ms(30);
							 TIM_SetCompare2(TIM2,1930);//PA1��ֵ���޸�
							 delay_ms(30);
					  }
						 break;
					 }
					 case PSB_L2:
					 {
						 delay_ms(20);
						 if(key == PSB_L2)
						 {
							TIM_SetCompare2(TIM2,1830);//PA1,ֵ���޸�
							delay_ms(10);
						 }
						 break;
					 }	
				
					 //��е�۶����ؽ�
					 case PSB_R1:
					 {
						 delay_ms(20);
						 if(key == PSB_R1)
						 {
							TIM_SetCompare3(TIM2,1905);//PA2��ֵ���޸�
							delay_ms(10);
					 }
						 break;
					 }
					 case PSB_R2:
						{
							delay_ms(10);
							if(key == PSB_R2)
							{
								TIM_SetCompare3(TIM2,1950);//PA2,ֵ���޸�
								delay_ms(10);
							}
							break;
						}
						 
					 //ץȡ
					 case PSB_GREEN:
					 {
						 delay_ms(10);
							if(key == PSB_GREEN)
							{
							TIM_SetCompare4(TIM2,1805);//PA3,ֵ���޸�	
							delay_ms(10);
						}
						break;
					}
					 //�ſ�
					  case PSB_RED:
						{
							delay_ms(10);
							if(key == PSB_RED)
							{
								TIM_SetCompare4(TIM2,1840);//PA3,ֵ���޸�
								delay_ms(10);
						}
							break;
						}
					 default:

//						 TIM_SetCompare2(TIM2,first_angle);
//						 TIM_SetCompare3(TIM2,second_angle);
						 break;
				 }
				 
			 }
		 }
		 #ifdef OUTPUT
		 #else
		 printf("speed : %5d %5d \r\n", speed1, speed2);
		 #endif
		}
}

