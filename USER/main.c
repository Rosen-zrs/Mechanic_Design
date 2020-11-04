#include "sys.h"
#include "math.h"
#include "stdlib.h"




 int main(void)
 {	
	 u8 key; 
	 s16 speed,speed1,speed2; 
	 s16 swerve;           //转弯量	  
	 delay_init(); //延时函数初始化
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置 NVIC 中断分组 2:2 位
	 usart3_init(9600);
	 
	 MOTOR_GPIO_init();
	 TIM3_DIANJI_PWM_Init(1999,719);//不分频。  //PWM频率=72000000/(719+1)/(1999+1)=50hz=20mS
	 TIM2_DUOJI_PWM_Init(1999,719);
	 
	 PS2_Init();			
	 PS2_SetInit();		 //配配置初始化,配置“红绿灯模式”，并选择是否可以修改
	
	 //
	 while(1)
	 {
		 if( !PS2_RedLight())
		 {
			 delay_ms(50);	 //延时很重要不可去
			 LED0 = 0;
				
			 key = PS2_DataKey();	 //手柄按键捕获处理
				
			 speed = (PS2_AnologData(PSS_LY)-127) * 10;	   
			 swerve = (PS2_AnologData(PSS_RX)-128)* 5 *((float)abs(speed)/127); //	speed取绝对值，	算数运算，得到转弯量。
			 speed = -(PS2_AnologData(PSS_LY)-127) * 10;	   //正：前进；  负：后退
			 if(speed > 0) //向前
			 {
				 if(swerve < 0)//左转弯
				 {
					 speed1 = speed + swerve;
					 speed2 = speed - swerve;
				 }
				 else          //右转弯
				 {
					 speed1 = speed + swerve; 
					 speed2 = speed - swerve;;
				 }
				 Set_qian_motor(speed1, speed2);
				 Set_hou_motor(speed1, speed2);
			 }
			 else if(speed < 0)//向后
			 {
				 if(swerve < 0)//左转弯
				 {
					 speed1 = speed - swerve;
					 speed2 = speed + swerve;
				 }
				 else//右转弯
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
		 if(key!=0)                   //有按键按下
     {
		   printf("  \r\n   %d  is  light  \r\n",Data[1]);//ID
			 printf("  \r\n   %d  is  pressed  \r\n",key);
		 if(key == 11)
		 {
			 PS2_Vibration(0xFF,0x00);  //发出震动后必须有延时  delay_ms(1000);
			 delay_ms(500);
		 }
			else if(key == 12)
			{
				PS2_Vibration(0x00,0xFF);  //发出震动后必须有延时  delay_ms(1000);
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

