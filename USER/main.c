#include "sys.h"
#include "math.h"
#include "stdlib.h"

#define OUTPUT

 int main(void)
 {	
	 u8 key; 
	 int claw_angle=1850;//爪子舵机的角度
	 int max_angle=1810;//在1800~1850间，爪子舵机的角度设置
	 int min_angle=1860;//在1850~1900间
	 s16 speed,speed1,speed2; 
	 s16 swerve;           //转弯量	 
	 int first_flag=1;//第一级关节的标志位
	 int second_flag=1;//第二级关节的标志位
	 //int third_flag=1;
	 delay_init(); //延时函数初始化
	 
	 Stm32_Clock_Init(9); //系统时钟设置
	 
	 LED_Init();
	 
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置 NVIC 中断分组 2:2 位
	 uart_init(9600);
	 
	 MOTOR_GPIO_init();
	 TIM3_DIANJI_PWM_Init(1999,719);//不分频。  //PWM频率=72000000/(719+1)/(1999+1)=50hz=20mS
	 TIM2_DUOJI_PWM_Init(1999,719);
	 
	 PS2_Init();	

	 PS2_SetInit();		 //配配置初始化,配置“红绿灯模式”，并选择是否可以修改
	 
	 
	 while(1)
	 {
		 if( !PS2_RedLight())
		 {
			 delay_ms(50);	 //延时很重要不可去
				
			 key = PS2_DataKey();	 //手柄按键捕获处理
				
			 speed = -(PS2_AnologData(PSS_LY)-127) * 10;	   
			 if(speed != 0)
			 {
				 swerve = (PS2_AnologData(PSS_RX)-128)* 5 *((float)abs(speed)/1270); //	speed取绝对值，	算数运算，得到转弯量。
			 }
			 else swerve = (PS2_AnologData(PSS_RX)-128)* 8;
			 if(speed >= 0) //向前
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
			 }
			 Set_qian_motor(speed1, speed2);
			 Set_hou_motor(speed1, speed2);
			 
			 if(key != 0)
			 {
				 switch(key)
				 {
					 //机械臂一级关节
					 case PSB_GREEN:
					 {
						 
						 /**********************************************/
						if(first_flag)
						{
							TIM_SetCompare2(TIM2,1950);//PA1，值待修改
							first_flag=0;
						}
						else
						{
							TIM_SetCompare2(TIM2,1750);//PA1,值待修改
							first_flag=1;
						}
			
						 break;
					 }
					 //机械臂二级关节
					 case PSB_BLUE:
					 {
						 
						 /**********************************************/
						 if(second_flag)
						{
							TIM_SetCompare3(TIM2,1950);//PA2，值待修改
							second_flag=0;
						}
						else
						{
							TIM_SetCompare3(TIM2,1750);//PA2,值待修改
							second_flag=1;
						}
						 break;
					 }
					 //抓取
					 case PSB_RED:
					 {
						 if(claw_angle<max_angle-5)
						 {
								TIM_SetCompare4(TIM2,claw_angle+=5);//PA3,值待修改
								printf("  \r\n claw_angle is %d  \r\n",claw_angle);
						 }
					 
						 break;
					 }
					 //放开
					  case PSB_PINK:
						{
							if(claw_angle>min_angle+5)
						 {
								TIM_SetCompare4(TIM2,claw_angle-=5);//PA3,值待修改
							  printf("  \r\n claw_angle is %d  \r\n",claw_angle);
						 }
							
							break;
						}
					 case PSB_L1:
					 {
						 PS2_Vibration(0xFF,0x00);  //发出震动后必须有延时  delay_ms(1000);
						 delay_ms(500);
						 PS2_Vibration(0x00,0x00); 
						 break;
					 }
					 case PSB_R1:
					 {
						 PS2_Vibration(0x00,0xFF);  //发出震动后必须有延时  delay_ms(1000);
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

