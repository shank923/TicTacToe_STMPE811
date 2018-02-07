/* Include core modules */
#include "stm32f4xx.h"
/* Include my libraries here */
#include "defines.h"
#include "tm_stm32f4_ili9341.h"
#include "tm_stm32f4_stmpe811.h"
#include <stdbool.h>
#include <stdio.h>

void draw_layout(void);
void draw_x(short xb, short yb);
void draw_c(short xb, short yb);
uint8_t check(uint8_t win_arr[3][3]);



int main(void) {
	char str[30];
	/* Create TouchData struct */
	TM_STMPE811_TouchData touchData;
	
	/* Initialize system */
	SystemInit();
	
	/* Initialize LCD */
	TM_ILI9341_Init();
	
	/* Rotate LCD */
	TM_ILI9341_Rotate(TM_ILI9341_Orientation_Portrait_2);
	
	/* Fill with orange color */
	TM_ILI9341_Fill(ILI9341_COLOR_RED);
	
	bool turn_flag = false;
	
	bool r_c_flag[9];
	
	uint8_t win_flag[3][3] = {{0,0,0},
	                        {0,0,0},
													{0,0,0}};
	
	for(int i = 0; i < 9;i++)
	r_c_flag[i] = true;
	
	/* Initialize Touch */
	if (TM_STMPE811_Init() != TM_STMPE811_State_Ok) {
		TM_ILI9341_Puts(20, 20, "STMPE811 Error", &TM_Font_11x18, ILI9341_COLOR_ORANGE, ILI9341_COLOR_BLACK);
		
		while (1);
	}
	
	/* Select touch screen orientation */
	touchData.orientation = TM_STMPE811_Orientation_Portrait_2;
	
	sprintf(str, "SUPER TIC-TAC-TOE");
			TM_ILI9341_Puts(17, 5, str, &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_RED);
	
	sprintf(str, "Restart");
			TM_ILI9341_Puts(5, 275, str, &TM_Font_11x18, ILI9341_COLOR_CYAN, ILI9341_COLOR_RED);
	
	sprintf(str, "(c)Anar_Genius");
			TM_ILI9341_Puts(135, 310, str, &TM_Font_7x10, ILI9341_COLOR_BROWN, ILI9341_COLOR_RED);
	
	/* Print some text */
	draw_layout();
	
	uint32_t mymillis = 0;
	
	while (1) {
		
		if(check(win_flag)== 1)
			{
				for(int i = 0; i < 3;i++)
				{
					for(int j = 0; j < 3;j++)
					win_flag[i][j]=0;
				}
				sprintf(str, "Player 1 win :)");
			TM_ILI9341_Puts(5, 40, str, &TM_Font_11x18, ILI9341_COLOR_YELLOW, ILI9341_COLOR_RED);
		}
		
			else if(check(win_flag)== 2)
				{
				for(int i = 0; i < 3;i++)
				{
					for(int j = 0; j < 3;j++)
					win_flag[i][j]=0;
				}
				sprintf(str, "Player 2 win :)");
			TM_ILI9341_Puts(5, 40, str, &TM_Font_11x18, ILI9341_COLOR_YELLOW, ILI9341_COLOR_RED);
			}
		
		if ((TM_STMPE811_ReadTouch(&touchData) == TM_STMPE811_State_Pressed) && (TM_DELAY_Time() - mymillis > 100)) 
			{
			mymillis = TM_DELAY_Time();
			
			if((touchData.x <= 50 && touchData.x > 0) && (touchData.y >= 265  && touchData.y <= 290))
			{
				TM_ILI9341_Fill(ILI9341_COLOR_RED);
				for(int i = 0; i < 9;i++)
	      r_c_flag[i] = true;
				
				for(int i = 0; i < 3;i++)
				{
					for(int j = 0; j < 3;j++)
					win_flag[i][j]=0;
				}
				
			sprintf(str, "Restart");
			TM_ILI9341_Puts(5, 275, str, &TM_Font_11x18, ILI9341_COLOR_CYAN, ILI9341_COLOR_RED);
				
			sprintf(str, "(c)Anar_Genius");
			TM_ILI9341_Puts(135, 310, str, &TM_Font_7x10, ILI9341_COLOR_BROWN, ILI9341_COLOR_RED);
				
			sprintf(str, "SUPER TIC-TAC-TOE");
			TM_ILI9341_Puts(17, 5, str, &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_RED);
				
				draw_layout();
			}
			
			// first row
			if((touchData.x <= 90 && touchData.x >= 30) && (touchData.y >= 75 && touchData.y <= 120) && r_c_flag[0] == true)
			{				
				if(turn_flag)
				{
				win_flag[0][0] = 1;
				draw_x(30, 75);
					turn_flag = false;
				}			
				else
				{
				win_flag[0][0] = 2;
				draw_c(30, 75);
					turn_flag = true;
				}
				
				r_c_flag[0] = false;
			}
			
			else if((touchData.x <= 150 && touchData.x > 90) && (touchData.y >= 75 && touchData.y <= 120) && r_c_flag[1] == true)
			{
				
				if(turn_flag)
				{
				win_flag[0][1] = 1;
				draw_x(85, 75);
					turn_flag = false;
				}			
				else
				{
				win_flag[0][1] = 2;
				draw_c(85, 75);
					turn_flag = true;
				}				
				
				
				r_c_flag[1] = false;
			}
			
			else if((touchData.x <= 205 && touchData.x > 150) && (touchData.y >= 75 && touchData.y <= 120) && r_c_flag[2] == true)
			{
				
			if(turn_flag)
				{
				win_flag[0][2] = 1;
				draw_x(145, 75);
					turn_flag = false;
				}			
				else
				{
				win_flag[0][2] = 2;
				draw_c(145, 75);
					turn_flag = true;
				}
				
				
				r_c_flag[2] = false;
			}	
			
			//second row
			
    else if((touchData.x <= 90 && touchData.x >= 30) && (touchData.y >= 120 && touchData.y <= 170) && r_c_flag[3] == true)
			{
				
			if(turn_flag)
				{
				win_flag[1][0] = 1;
				draw_x(30, 120);
					turn_flag = false;
				}			
				else
				{
				win_flag[1][0] = 2;
				draw_c(30, 120);
					turn_flag = true;
				}
				
				
				r_c_flag[3] = false;
			}			
			
   else if((touchData.x <= 150 && touchData.x > 90) && (touchData.y > 120 && touchData.y <= 170) && r_c_flag[4] == true)
			{
				
				if(turn_flag)
				{
				win_flag[1][1] = 1;
				draw_x(85, 120);
					turn_flag = false;
				}			
				else
				{
				win_flag[1][1] = 2;
				draw_c(85, 120);
					turn_flag = true;
				}
				
				
				r_c_flag[4] = false;
			}		
			
   else if((touchData.x <= 205 && touchData.x > 150) && (touchData.y > 120 && touchData.y <= 170) && r_c_flag[5] == true)
	 {
		 
		 if(turn_flag)
				{
				win_flag[1][2] = 1;
				draw_x(145, 120);
					turn_flag = false;
				}			
				else
				{
				win_flag[1][2] = 2;
				draw_c(145, 120);
					turn_flag = true;
				}
				
				
				r_c_flag[5] = false;
			}			
	 
	//third row
			
    else if((touchData.x <= 90 && touchData.x >= 30) && (touchData.y >= 170 && touchData.y <= 225) && r_c_flag[6] == true)
		{
			
			if(turn_flag)
				{
				win_flag[2][0] = 1;
				draw_x(30, 170);
					turn_flag = false;
				}			
				else
				{
				win_flag[2][0] = 2;
				draw_c(30, 170);
					turn_flag = true;
				}
				
				r_c_flag[6] = false;
			}			
		
   else if((touchData.x <= 150 && touchData.x > 90) && (touchData.y > 170 && touchData.y <= 225) && r_c_flag[7] == true)
			{
				
				if(turn_flag)
				{
				win_flag[2][1] = 1;
				draw_x(85, 170);
					turn_flag = false;
				}			
				else
				{
				win_flag[2][1] = 2;	
				draw_c(85, 170);
					turn_flag = true;
				}
				
				
				r_c_flag[7] = false;
			}		
			
   else if((touchData.x <= 205 && touchData.x > 150) && (touchData.y > 170 && touchData.y <= 225) && r_c_flag[8] == true)
			{
				
				if(turn_flag)
				{
				win_flag[2][2] = 1;
				draw_x(145, 170);
					turn_flag = false;
				}			
				else
				{
				win_flag[2][2] = 2;
				draw_c(145, 170);
					turn_flag = true;
				}
				
				
				r_c_flag[8] = false;
			}					
			
			else
			{
			//sprintf(str, "miss click");
			//TM_ILI9341_Puts(5, 5, str, &TM_Font_11x18, ILI9341_COLOR_CYAN, ILI9341_COLOR_RED);
			}
		}
		} 
	}



void draw_layout(void)
{
	short xh = 40, yh = 100;
	
	short xv = 80, yv = 80;
	
 for(int i = 0; i < 140;i++)
	{
		//horizontal
		TM_ILI9341_Putc(xh+i, yh, '_', &TM_Font_16x26, ILI9341_COLOR_WHITE, ILI9341_COLOR_RED);
	  TM_ILI9341_Putc(xh+i, yh+50, '_', &TM_Font_16x26, ILI9341_COLOR_WHITE, ILI9341_COLOR_RED);
	}

	for(int i = 0; i < 115; i++)
	{
	 		//vertical
		TM_ILI9341_Putc(xv, yv+i, '|', &TM_Font_11x18, ILI9341_COLOR_WHITE, ILI9341_COLOR_RED);
	  TM_ILI9341_Putc(xv+60, yv+i, '|', &TM_Font_11x18, ILI9341_COLOR_WHITE, ILI9341_COLOR_RED);
	}
}


void draw_x(short xb, short yb)
{
	int xb1 = xb+40, yb1 = yb+10;
	xb+=13;
	yb+=10;
	for(int i = 0; i < 30; i+=5)
	{
	 TM_ILI9341_Putc(xb+i, yb+i, 'o', &TM_Font_7x10, ILI9341_COLOR_WHITE, ILI9341_COLOR_RED);
	}
   
	for(int i = 0; i < 30; i+=5)
	{
	 TM_ILI9341_Putc(xb1-i, yb1+i, 'o', &TM_Font_7x10, ILI9341_COLOR_WHITE, ILI9341_COLOR_RED);
	}
}	


void draw_c(short xb, short yb)
{
	TM_ILI9341_DrawCircle(xb+30, yb+25, 8, ILI9341_COLOR_WHITE);
}	


uint8_t check(uint8_t win_arr[3][3])
{
  for(int i = 0, j = 0;i < 3;i++, j++)
	{		
		if(i == 0)
		{
			//0 raw
	  if(win_arr[i][j] == 1 && win_arr[i][j+1] == 1 && win_arr[i][j+2] == 1)
		{
			TM_ILI9341_DrawLine(35,100,200,100,ILI9341_COLOR_BLACK);
			return 1;
		}
		else if(win_arr[i][j] == 2 && win_arr[i][j+1] == 2 && win_arr[i][j+2] == 2)
		{
			TM_ILI9341_DrawLine(35,100,200,100,ILI9341_COLOR_BLACK);
			return 2;
		}
		
		//0 column
		else if(win_arr[i][j] == 1 && win_arr[i+1][j] == 1 && win_arr[i+2][j] == 1)
		{
			TM_ILI9341_DrawLine(58,80,58,215,ILI9341_COLOR_BLACK);
			return 1;
		}
		else if(win_arr[i][j] == 2 && win_arr[i+1][j] == 2 && win_arr[i+2][j] == 2)
		{
			TM_ILI9341_DrawLine(58,80,58,215,ILI9341_COLOR_BLACK);
			return 2;
		}
		
		//diagonal
		else if(win_arr[i][j] == 1 && win_arr[i+1][j+1] == 1 && win_arr[i+2][j+2] == 1)
		{
			TM_ILI9341_DrawLine(45,95,185,205,ILI9341_COLOR_BLACK);
			return 1;
		}
		else if(win_arr[i][j] == 2 && win_arr[i+1][j+1] == 2 && win_arr[i+2][j+2] == 2)
		{
			TM_ILI9341_DrawLine(45,95,185,205,ILI9341_COLOR_BLACK);
			return 2;
		}
		
		else if(win_arr[i][j+2] == 1 && win_arr[i+1][j+1] == 1 && win_arr[i+2][j] == 1)
		{
			for(int i = 0;i<150;i++)
			TM_ILI9341_DrawPixel(40+i,210-i*0.85, ILI9341_COLOR_BLACK);
			return 1;
		}
		else if(win_arr[i][j+2] == 2 && win_arr[i+1][j+1] == 2 && win_arr[i+2][j] == 2)
		{
			for(int i = 0;i<150;i++)
			TM_ILI9341_DrawPixel(40+i,210-i*0.85, ILI9341_COLOR_BLACK);
			return 2;
		}
	  }
		
		if(i == 1)
		{
			//1 raw
		  if(win_arr[i][j] == 1 && win_arr[i][j-1] == 1 && win_arr[i][j+1] == 1)
			{
				TM_ILI9341_DrawLine(35,148,200,148,ILI9341_COLOR_BLACK);
			return 1;
			}
		else if(win_arr[i][j] == 2 && win_arr[i][j-1] == 2 && win_arr[i][j+1] == 2)
		{
			TM_ILI9341_DrawLine(35,148,200,148,ILI9341_COLOR_BLACK);
			return 2;
		}
		
		//1 column
		else if(win_arr[i][j] == 1 && win_arr[i-1][j] == 1 && win_arr[i+1][j] == 1)
		{
			TM_ILI9341_DrawLine(112,80,112,215,ILI9341_COLOR_BLACK);
			return 1;
		}
		else if(win_arr[i][j] == 2 && win_arr[i-1][j] == 2 && win_arr[i+1][j] == 2)
		{
			TM_ILI9341_DrawLine(112,80,112,215,ILI9341_COLOR_BLACK);
			return 2;
		}
		}
		
		if(i == 2)
		{
			//2 raw
		  if(win_arr[i][j] == 1 && win_arr[i][j-1] == 1 && win_arr[i][j-2] == 1)
			{
				TM_ILI9341_DrawLine(35,200,200,200,ILI9341_COLOR_BLACK);
				
			return 1;
			}
		else if(win_arr[i][j] == 2 && win_arr[i][j-1] == 2 && win_arr[i][j-2] == 2)
		{
			TM_ILI9341_DrawLine(35,200,200,200,ILI9341_COLOR_BLACK);
			return 2;
		}
		
		//2 column
		else if(win_arr[i][j] == 1 && win_arr[i-1][j] == 1 && win_arr[i-2][j] == 1)
		{
			TM_ILI9341_DrawLine(173,80,173,215,ILI9341_COLOR_BLACK);
			return 1;
		}
		else if(win_arr[i][j] == 2 && win_arr[i-1][j] == 2 && win_arr[i-2][j] == 2)
		{
			TM_ILI9341_DrawLine(173,80,173,215,ILI9341_COLOR_BLACK);
			return 2;
		}
		
		}	
	}
	
   return 0;
}
