#include "sys.h"
#include "math.h"
#include "stdlib.h"

#define OUTPUT

 int main(void)
 {	
	 u8 key; 

	 
	 s16 speed,speed1,speed2; 
	 s16 swerve;           //转弯量	 
	 
	 int first_angle = 1768;
	 int second_angle = 1860;
	
	 
	 delay_init(); //延时函数初始化
	 
	 delay_ms(100);
	 
	 Stm32_Clock_Init(9); //系统时钟设置
	 
	 //LED_Init();
	 
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //�	柚� NVIC 中断分组 2:2 位
	 uart_init(9600);
	 
	 MOTOR_GPIO_init();
	 TIM3_DIANJI_PWM_Init(1999,719);//不分频。  //PWM频率=72000000/(719+1)/(1999+1)=50hz=20mS
	 TIM2_DUOJI_PWM_Init(1999,719);
	 TIM1_YUANTONG_PWM_Init(1999,719);
	 TIM4_CHUCUN_PWM_Init(1999,719);
	 PS2_Init();	

	 PS2_SetInit();		 //配配置初始化,配置“红绿灯模式”，并选择是否可以修改
	 
	 TIM_SetCompare2(TIM2,first_angle);//一级关节初始值
	 TIM_SetCompare3(TIM2,second_angle);//二级关节初始值
	 
	 
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
							 first_angle = 1770;
							 TIM_SetCompare2(TIM2,1770);//PA1，值待修改
							 delay_ms(10);		
							 TIM_SetCompare2(TIM2,1780);//PA1，值待修改
							 delay_ms(10);		
							 TIM_SetCompare2(TIM2,1790);//PA1，值待修改
							 delay_ms(10);		
							 TIM_SetCompare2(TIM2,1800);//PA1，值待修改
							 delay_ms(10);
							 TIM_SetCompare2(TIM2,1810);//PA1，值待修改
							 delay_ms(10);		
							 TIM_SetCompare2(TIM2,1820);//PA1，值待修改
							 delay_ms(10);
							 TIM_SetCompare2(TIM2,1830);//PA1，值待修改
							 delay_ms(10);		
							 TIM_SetCompare2(TIM2,1840);//PA1，值待修改
							 delay_ms(10);
							 TIM_SetCompare2(TIM2,1850);//PA1，值待修改
							 delay_ms(10);		
							 TIM_SetCompare2(TIM2,1860);//PA1，值待修改
							 delay_ms(10);
							 TIM_SetCompare2(TIM2,1870);//PA1，值待修改
							 delay_ms(10);		
							 TIM_SetCompare2(TIM2,1880);//PA1，值待修改
							 delay_ms(10);
							 TIM_SetCompare2(TIM2,1890);//PA1，值待修改
							 delay_ms(10);
							 TIM_SetCompare2(TIM2,1900);//PA1，值待修改
							 delay_ms(10);
							 TIM_SetCompare2(TIM2,1910);//PA1，值待修改
							 delay_ms(10);
							 TIM_SetCompare2(TIM2,1920);//PA1，值待修改
							 delay_ms(10);
							 TIM_SetCompare2(TIM2,1930);//PA1，值待修改
							 delay_ms(10);
							 TIM_SetCompare2(TIM2,1940);//PA1，值待修改
							 delay_ms(10);
							 

							 
					  }
						 break;
					 }
					 case PSB_L2:
					 {
						 delay_ms(20);
						 if(key == PSB_L2)
						 {
							TIM_SetCompare2(TIM2,1768);//PA1,值待修改
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
							TIM_SetCompare3(TIM2,1860);//PA2，值待修改
							delay_ms(10);
					 }
						 break;
					 }
					 case PSB_R2:
						{
							delay_ms(10);
							if(key == PSB_R2)
							{
								TIM_SetCompare3(TIM2,1860);//PA2,值待修改
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
							TIM_SetCompare4(TIM2,1825);//PA3,值待修改	
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
								TIM_SetCompare4(TIM2,1860);//PA3,值待修改
								delay_ms(10);
						}
							break;
						}
						case PSB_PAD_UP:
						{
							delay_ms(10);
							if(key == PSB_PAD_UP)
							{
								Set_chouji_motor(1000);
								
						}
							break;
						}
						case PSB_PAD_DOWN:
						{
							delay_ms(10);
							if(key == PSB_PAD_DOWN)
							{
							  Set_chouji_motor(-1000);
							
						}
							break;
						}
						
						//储存
						case PSB_PINK:
						{
							delay_ms(10);
							if(key == PSB_PINK)
							{
								TIM_SetCompare4(TIM4,1900);
						  }
							break;
						}
						case PSB_BLUE:
						{
							delay_ms(10);
							if(key == PSB_BLUE)
							{
								TIM_SetCompare4(TIM4,1950);
						  }
							break;
						}
					 default:
//						 TIM_SetCompare2(TIM2,first_angle);
//						 TIM_SetCompare3(TIM2,second_angle);
						 break;
				 }
				 
			 }
			 else{
				 yuan_AIN1 = 0;
				 yuan_AIN2 = 0;
			 }
		 }
		 #ifdef OUTPUT
		 #else
		 printf("speed : %5d %5d \r\n", speed1, speed2);
		 #endif
		}
}

