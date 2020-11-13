#include "sys.h"
#include "math.h"
#include "stdlib.h"

#define OUTPUT

 int main(void)
 {	
	 u8 key; 
	 int i;
	 int claw_angle=1850;//爪子舵机的角度
	 
	 s16 speed,speed1,speed2; 
	 s16 swerve;           //转弯量	 
	 
	 int first_angle = 1930;
	 int second_angle = 1905;
	 
	
	 delay_init(); //延时函数初始化
	 
	 delay_ms(100);
	 
	 Stm32_Clock_Init(9); //系统时钟设置
	 
	 LED_Init();
	 
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置 NVIC 中断分组 2:2 位
	 uart_init(9600);
	 
	 MOTOR_GPIO_init();
	 TIM3_DIANJI_PWM_Init(1999,719);//不分频。  //PWM频率=72000000/(719+1)/(1999+1)=50hz=20mS
	 TIM2_DUOJI_PWM_Init(1999,719);
	 
	 PS2_Init();	

	 PS2_SetInit();		 //配配置初始化,配置“红绿灯模式”，并选择是否可以修改
	 
	 TIM_SetCompare2(TIM2,first_angle);
	 TIM_SetCompare3(TIM2,second_angle);
	 
	 
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
			 
			 if(key)
			 {
				 switch(key)
				 {
					 //机械臂一级关节
					 case PSB_L1:
					 {
						 delay_ms(20);
						 if(key == PSB_L1)
						 {
							 TIM_SetCompare2(TIM2,1880);//PA1，值待修改
							 delay_ms(10);
							 TIM_SetCompare2(TIM2,1890);//PA1，值待修改
							 delay_ms(10);
							 TIM_SetCompare2(TIM2,1900);//PA1，值待修改
							 delay_ms(10);
							 TIM_SetCompare2(TIM2,1910);//PA1，值待修改
							 delay_ms(30);
							 TIM_SetCompare2(TIM2,1920);//PA1，值待修改
							 delay_ms(30);
							 TIM_SetCompare2(TIM2,1930);//PA1，值待修改
							 delay_ms(30);
					  }
						 break;
					 }
					 case PSB_L2:
					 {
						 delay_ms(20);
						 if(key == PSB_L2)
						 {
							TIM_SetCompare2(TIM2,1830);//PA1,值待修改
							delay_ms(10);
						 }
						 break;
					 }	
				
					 //机械臂二级关节
					 case PSB_R1:
					 {
						 delay_ms(20);
						 if(key == PSB_R1)
						 {
							TIM_SetCompare3(TIM2,1905);//PA2，值待修改
							delay_ms(10);
					 }
						 break;
					 }
					 case PSB_R2:
						{
							delay_ms(10);
							if(key == PSB_R2)
							{
								TIM_SetCompare3(TIM2,1950);//PA2,值待修改
								delay_ms(10);
							}
							break;
						}
						 
					 //抓取
					 case PSB_GREEN:
					 {
						 delay_ms(10);
							if(key == PSB_GREEN)
							{
							TIM_SetCompare4(TIM2,1805);//PA3,值待修改	
							delay_ms(10);
						}
						break;
					}
					 //放开
					  case PSB_RED:
						{
							delay_ms(10);
							if(key == PSB_RED)
							{
								TIM_SetCompare4(TIM2,1840);//PA3,值待修改
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

