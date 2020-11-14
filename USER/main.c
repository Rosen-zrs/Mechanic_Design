#include "sys.h"
#include "math.h"
#include "stdlib.h"

#define OUTPUT

 int main(void)
 {	
	 u8 key; 
	 int i;
	 
	 s16 speed,speed1,speed2; 
	 s16 swerve;           //×ªÍäÁ¿	 
	 
	 int first_angle = 1768;
	 int second_angle = 1860;
	 
	
	 delay_init(); //ÑÓÊ±º¯Êı³õÊ¼»¯
	 
	 delay_ms(100);
	 
	 Stm32_Clock_Init(9); //ÏµÍ³Ê±ÖÓÉèÖÃ
	 
	 LED_Init();
	 
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //É	èÖÃ NVIC ÖĞ¶Ï·Ö×é 2:2 Î»
	 uart_init(9600);
	 
	 MOTOR_GPIO_init();
	 TIM3_DIANJI_PWM_Init(1999,719);//²»·ÖÆµ¡£  //PWMÆµÂÊ=72000000/(719+1)/(1999+1)=50hz=20mS
	 TIM2_DUOJI_PWM_Init(1999,719);
	 
	 PS2_Init();	

	 PS2_SetInit();		 //ÅäÅäÖÃ³õÊ¼»¯,ÅäÖÃ¡°ºìÂÌµÆÄ£Ê½¡±£¬²¢Ñ¡ÔñÊÇ·ñ¿ÉÒÔĞŞ¸Ä
	 
	 TIM_SetCompare2(TIM2,first_angle);//Ò»¼¶¹Ø½Ú³õÊ¼Öµ
	 TIM_SetCompare3(TIM2,second_angle);//¶ş¼¶¹Ø½Ú³õÊ¼Öµ
	 
	 
	 while(1)
	 {
		 if( !PS2_RedLight())
		 {
			 
			 delay_ms(50);	 //ÑÓÊ±ºÜÖØÒª²»¿ÉÈ¥
			 
			 key = PS2_DataKey();	 //ÊÖ±ú°´¼ü²¶»ñ´¦Àí
				
			 speed = -(PS2_AnologData(PSS_LY)-127) * 10;	   
			 if(speed != 0)
			 {
				 swerve = (PS2_AnologData(PSS_RX)-128)* 5 *((float)abs(speed)/1270); //	speedÈ¡¾ø¶ÔÖµ£¬	ËãÊıÔËËã£¬µÃµ½×ªÍäÁ¿¡£
			 }
			 else swerve = (PS2_AnologData(PSS_RX)-128)* 8;
			 if(speed >= 0) //ÏòÇ°
			 {
				 if(swerve < 0)//×ó×ªÍä 
				 {
					 speed1 = speed + swerve;
					 speed2 = speed - swerve;
				 }
				 else          //ÓÒ×ªÍä
				 {
					 speed1 = speed + swerve; 
					 speed2 = speed - swerve;;
				 }
			 }
			 else if(speed < 0)//Ïòºó
			 {
				 if(swerve < 0)//×ó×ªÍä
				 {
					 speed1 = speed - swerve;
					 speed2 = speed + swerve;
				 }
				 else//ÓÒ×ªÍä
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
					 //»úĞµ±ÛÒ»¼¶¹Ø½Ú
					 case PSB_L1:
					 {
						 delay_ms(20);
						 if(key == PSB_L1)
						 {
							 first_angle = 1770;
							 TIM_SetCompare2(TIM2,1770);//PA1£¬Öµ´ıĞŞ¸Ä
							 delay_ms(10);		
							 TIM_SetCompare2(TIM2,1780);//PA1£¬Öµ´ıĞŞ¸Ä
							 delay_ms(10);		
							 TIM_SetCompare2(TIM2,1790);//PA1£¬Öµ´ıĞŞ¸Ä
							 delay_ms(10);		
							 TIM_SetCompare2(TIM2,1800);//PA1£¬Öµ´ıĞŞ¸Ä
							 delay_ms(10);
							 TIM_SetCompare2(TIM2,1810);//PA1£¬Öµ´ıĞŞ¸Ä
							 delay_ms(10);		
							 TIM_SetCompare2(TIM2,1820);//PA1£¬Öµ´ıĞŞ¸Ä
							 delay_ms(10);
							 TIM_SetCompare2(TIM2,1830);//PA1£¬Öµ´ıĞŞ¸Ä
							 delay_ms(10);		
							 TIM_SetCompare2(TIM2,1840);//PA1£¬Öµ´ıĞŞ¸Ä
							 delay_ms(10);
							 TIM_SetCompare2(TIM2,1850);//PA1£¬Öµ´ıĞŞ¸Ä
							 delay_ms(10);		
							 TIM_SetCompare2(TIM2,1860);//PA1£¬Öµ´ıĞŞ¸Ä
							 delay_ms(10);
							 TIM_SetCompare2(TIM2,1870);//PA1£¬Öµ´ıĞŞ¸Ä
							 delay_ms(10);		
							 TIM_SetCompare2(TIM2,1880);//PA1£¬Öµ´ıĞŞ¸Ä
							 delay_ms(10);
							 TIM_SetCompare2(TIM2,1890);//PA1£¬Öµ´ıĞŞ¸Ä
							 delay_ms(10);
							 TIM_SetCompare2(TIM2,1900);//PA1£¬Öµ´ıĞŞ¸Ä
							 delay_ms(10);
							 TIM_SetCompare2(TIM2,1910);//PA1£¬Öµ´ıĞŞ¸Ä
							 delay_ms(10);
							 TIM_SetCompare2(TIM2,1920);//PA1£¬Öµ´ıĞŞ¸Ä
							 delay_ms(10);
							 TIM_SetCompare2(TIM2,1930);//PA1£¬Öµ´ıĞŞ¸Ä
							 delay_ms(10);
							 TIM_SetCompare2(TIM2,1940);//PA1£¬Öµ´ıĞŞ¸Ä
							 delay_ms(10);
							 

							 
					  }
						 break;
					 }
					 case PSB_L2:
					 {
						 delay_ms(20);
						 if(key == PSB_L2)
						 {
							TIM_SetCompare2(TIM2,1768);//PA1,Öµ´ıĞŞ¸Ä
							delay_ms(10);
						 }
						 break;
					 }	
				
					 //»úĞµ±Û¶ş¼¶¹Ø½Ú
					 case PSB_R1:
					 {
						 delay_ms(20);
						 if(key == PSB_R1)
						 {
							TIM_SetCompare3(TIM2,1860);//PA2£¬Öµ´ıĞŞ¸Ä
							delay_ms(10);
					 }
						 break;
					 }
					 case PSB_R2:
						{
							delay_ms(10);
							if(key == PSB_R2)
							{
								TIM_SetCompare3(TIM2,1860);//PA2,Öµ´ıĞŞ¸Ä
								delay_ms(10);
							}
							break;
						}
						 
					 //×¥È¡
					 case PSB_GREEN:
					 {
						 delay_ms(10);
							if(key == PSB_GREEN)
							{
							TIM_SetCompare4(TIM2,1805);//PA3,Öµ´ıĞŞ¸Ä	
							delay_ms(10);
						}
						break;
					}
					 //·Å¿ª
					  case PSB_RED:
						{
							delay_ms(10);
							if(key == PSB_RED)
							{
								TIM_SetCompare4(TIM2,1840);//PA3,Öµ´ıĞŞ¸Ä
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

