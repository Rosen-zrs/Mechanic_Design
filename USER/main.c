#include "sys.h"
#include "math.h"
#include "stdlib.h"




 int main(void)
 {	
	 u8 key; 
	 s16 speed,speed1,speed2; 
	 s16 swerve;           //ת����	  
	 delay_init(); //��ʱ������ʼ��
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //���� NVIC �жϷ��� 2:2 λ
	 usart3_init(9600);
	 
	 MOTOR_GPIO_init();
	 TIM3_DIANJI_PWM_Init(1999,719);//����Ƶ��  //PWMƵ��=72000000/(719+1)/(1999+1)=50hz=20mS
	 TIM2_DUOJI_PWM_Init(1999,719);
	 
	 PS2_Init();			
	 PS2_SetInit();		 //�����ó�ʼ��,���á����̵�ģʽ������ѡ���Ƿ�����޸�
	
	 //
	 while(1)
	 {
		 if( !PS2_RedLight())
		 {
			 delay_ms(50);	 //��ʱ����Ҫ����ȥ
			 LED0 = 0;
				
			 key = PS2_DataKey();	 //�ֱ�����������
				
			 speed = (PS2_AnologData(PSS_LY)-127) * 10;	   
			 swerve = (PS2_AnologData(PSS_RX)-128)* 5 *((float)abs(speed)/127); //	speedȡ����ֵ��	�������㣬�õ�ת������
			 speed = -(PS2_AnologData(PSS_LY)-127) * 10;	   //����ǰ����  ��������
			 if(speed > 0) //��ǰ
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
				 Set_qian_motor(speed1, speed2);
				 Set_hou_motor(speed1, speed2);
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
				 Set_qian_motor(speed1, speed2);
				 Set_hou_motor(speed1, speed2);
			 }
			 else 
			 {
				 Set_qian_motor(0, 0);
				 Set_hou_motor(0, 0);
			 }
		 }
		 if(key!=0)                   //�а�������
     {
		   printf("  \r\n   %d  is  light  \r\n",Data[1]);//ID
			 printf("  \r\n   %d  is  pressed  \r\n",key);
		 if(key == 11)
		 {
			 PS2_Vibration(0xFF,0x00);  //�����𶯺��������ʱ  delay_ms(1000);
			 delay_ms(500);
		 }
			else if(key == 12)
			{
				PS2_Vibration(0x00,0xFF);  //�����𶯺��������ʱ  delay_ms(1000);
				delay_ms(500);
			}
			else
				 PS2_Vibration(0x00,0x00); 
    	}
		printf(" %5d %5d %5d %5d\r\n",PS2_AnologData(PSS_LX),PS2_AnologData(PSS_LY),
		                              PS2_AnologData(PSS_RX),PS2_AnologData(PSS_RY) );
		delay_ms(50);
		}
}

