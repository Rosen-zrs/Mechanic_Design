#include "sys.h"
#include "math.h"
#include "stdlib.h"

#define OUTPUT

 int main(void)
 {	
	 u8 key; 
	 int claw_angle=1850;//צ�Ӷ���ĽǶ�
	 int max_angle=1810;//��1800~1850�䣬צ�Ӷ���ĽǶ�����
	 int min_angle=1860;//��1850~1900��
	 s16 speed,speed1,speed2; 
	 s16 swerve;           //ת����	 
	 int first_flag=1;//��һ���ؽڵı�־λ
	 int second_flag=1;//�ڶ����ؽڵı�־λ
	 //int third_flag=1;
	 delay_init(); //��ʱ������ʼ��
	 
	 Stm32_Clock_Init(9); //ϵͳʱ������
	 
	 LED_Init();
	 
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //���� NVIC �жϷ��� 2:2 λ
	 uart_init(9600);
	 
	 MOTOR_GPIO_init();
	 TIM3_DIANJI_PWM_Init(1999,719);//����Ƶ��  //PWMƵ��=72000000/(719+1)/(1999+1)=50hz=20mS
	 TIM2_DUOJI_PWM_Init(1999,719);
	 
	 PS2_Init();	

	 PS2_SetInit();		 //�����ó�ʼ��,���á����̵�ģʽ������ѡ���Ƿ�����޸�
	 
	 
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
			 
			 if(key != 0)
			 {
				 switch(key)
				 {
					 //��е��һ���ؽ�
					 case PSB_GREEN:
					 {
						 
						 /**********************************************/
						if(first_flag)
						{
							TIM_SetCompare2(TIM2,1950);//PA1��ֵ���޸�
							first_flag=0;
						}
						else
						{
							TIM_SetCompare2(TIM2,1750);//PA1,ֵ���޸�
							first_flag=1;
						}
			
						 break;
					 }
					 //��е�۶����ؽ�
					 case PSB_BLUE:
					 {
						 
						 /**********************************************/
						 if(second_flag)
						{
							TIM_SetCompare3(TIM2,1950);//PA2��ֵ���޸�
							second_flag=0;
						}
						else
						{
							TIM_SetCompare3(TIM2,1750);//PA2,ֵ���޸�
							second_flag=1;
						}
						 break;
					 }
					 //ץȡ
					 case PSB_RED:
					 {
						 if(claw_angle<max_angle-5)
						 {
								TIM_SetCompare4(TIM2,claw_angle+=5);//PA3,ֵ���޸�
								printf("  \r\n claw_angle is %d  \r\n",claw_angle);
						 }
					 
						 break;
					 }
					 //�ſ�
					  case PSB_PINK:
						{
							if(claw_angle>min_angle+5)
						 {
								TIM_SetCompare4(TIM2,claw_angle-=5);//PA3,ֵ���޸�
							  printf("  \r\n claw_angle is %d  \r\n",claw_angle);
						 }
							
							break;
						}
					 case PSB_L1:
					 {
						 PS2_Vibration(0xFF,0x00);  //�����𶯺��������ʱ  delay_ms(1000);
						 delay_ms(500);
						 PS2_Vibration(0x00,0x00); 
						 break;
					 }
					 case PSB_R1:
					 {
						 PS2_Vibration(0x00,0xFF);  //�����𶯺��������ʱ  delay_ms(1000);
						 delay_ms(500);
						 PS2_Vibration(0x00,0x00); 
						 break;
					 }
				 }
				 
				 #ifdef OUTPUT
				 printf("  \r\n   %d  is  pressed  \r\n",key);
				 #endif
			 }
		 }
		 #ifdef OUTPUT
		 #else
		 printf("speed : %5d %5d \r\n", speed1, speed2);
		 #endif
		}
}

