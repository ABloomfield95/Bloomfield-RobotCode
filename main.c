/*
 * Final Robot Code.c
 *
 * Created: 4/4/2024 4:12:29 PM
 * Author : abloomfie
 */ 

#include "C:\Spring 2024\UR1\Class Libraries\F_cpu_lib.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <util/delay.h>
#include <stdbool.h>
#include "C:\Spring 2024\UR1\Class Libraries\A2D_lib.h"
#include "C:\Spring 2024\UR1\Class Libraries\LCD_lib.h"
#include "C:\Spring 2024\UR1\Class Libraries\Serial_lib2.h"
#include "C:\Spring 2024\UR1\Class Libraries\Motor_PWM_lib.h"



int main(void)
{
    //LCD Screen Initialization
    LCD_init();							//Gets no value (void)
    LCDGoToPosition(1,1); 				//Position given by the lab report (First Position, Top Row)
    char LCD_out[20];					//LCD Output String
    sprintf(LCD_out, "LCD On");			//Confirmation Message for LCD
    LCDSendString(LCD_out);				//Makes sure the string is sent to the display
    _delay_ms(500);						//Short delay to make sure message can be seen
    LCDClearScreen();					//Clears the screen
	USART_vInit();
  
	
	//Serial Communication Initialization
	AD_init();							//Use to setup the analog input ports
	sei();								//This function allows the needed ADC interrupts
	DDRC |= 1 << PINC2;					//Sets up LED as indicator
	
	//Initialization for state machine
	uint8_t state = 1;
	uint16_t videoInput;
	
	//Motor Definitions
	#define LMOT 0
	#define RMOT 1
	
    while (1) 
    {
		PORTC |=1 <<PINC2;
		videoInput = USART_vReceiveByte();
		PORTC &=0 <<PINC2;
	
				
		HBridgeInit();
		
		switch(state)
		{
			//State 1: Forward Drive
			case 1:
			HBridgeCommand(RMOT,68,0);
			HBridgeCommand(LMOT,71,0);
			
			LCDGoToPosition(1,1);
			sprintf(LCD_out, "State 1");
			LCDSendString(LCD_out);
			LCDGoToPosition(1,2);
			sprintf(LCD_out, "SV: %d", videoInput);
			LCDSendString(LCD_out);
			_delay_ms(100);
			
			
			//High pixels far left
			if(videoInput == 1)
			{
				state = 3;
			}
			//High pixels far right
			else if(videoInput == 5)
			{
				state = 5;
			}
			//High pixels middle left
			else if (videoInput == 2)
			{
				state = 2;
			}
			//High pixels middle right
			else if (videoInput == 4)
			{
				state = 4;
			}
			//Red line pixels
			else if(videoInput == 6)
			{
				state = 6;
			}
			break;
			
			
			//State 2:  Soft Left Turn
			case 2:
			HBridgeCommand(LMOT,70,0);
			HBridgeCommand(RMOT,34,0);
			
			LCDGoToPosition(1,1);
			sprintf(LCD_out, "State 2");
			LCDSendString(LCD_out);
			LCDGoToPosition(1,2);
			sprintf(LCD_out, "SV: %d", videoInput);
			LCDSendString(LCD_out);
			_delay_ms(100);
			
			//Balanced White Pixels
			if(videoInput == 3)
			{
				state = 1;
			}
			//High pixels far left
			else if(videoInput == 1)
			{
				state = 3;
			}
			//High pixels far right
			else if(videoInput == 5)
			{
				state = 5;
			}
			//High pixels middle right
			else if (videoInput == 4)
			{
				state = 4;
			}
			//Red line pixels
			else if(videoInput == 6)
			{
				state = 6;
			}
			break;
			
			
			//State 3: Hard Left Turn
			case 3:
			HBridgeCommand(LMOT,100,0);
			HBridgeCommand(RMOT,26,0);
			
			LCDGoToPosition(1,1);
			sprintf(LCD_out, "State 3");
			LCDSendString(LCD_out);
			LCDGoToPosition(1,2);
			sprintf(LCD_out, "SV: %d", videoInput);
			LCDSendString(LCD_out);
			_delay_ms(150);
			
			//Balanced White Pixels
			if(videoInput == 3)
			{
				state = 1;
			}
			//High pixels middle left
			else if(videoInput == 2)
			{
				state = 2;
			}
			//High pixels far right
			else if(videoInput == 5)
			{
				state = 5;
			}
			//High pixels middle right
			else if (videoInput == 4)
			{
				state = 4;
			}
			//Red line pixels
			else if(videoInput == 6)
			{
				state = 6;
			}
			break;
			
			//State 4: Soft Right Turn
			case 4:
			HBridgeCommand(LMOT,37,0);
			HBridgeCommand(RMOT,73,0);
			
			LCDGoToPosition(1,1);
			sprintf(LCD_out, "State 4");
			LCDSendString(LCD_out);
			LCDGoToPosition(1,2);
			sprintf(LCD_out, "SV: %d", videoInput);
			LCDSendString(LCD_out);
			_delay_ms(100);
			
			//Balanced White Pixels
			if(videoInput == 3)
			{
				state = 1;
			}
			//High pixels far left
			else if(videoInput == 1)
			{
				state = 3;
			}
			//High pixels far right
			else if(videoInput == 5)
			{
				state = 5;
			}
			//High pixels middle right
			else if (videoInput == 2)
			{
				state = 2;
			}
			//Red line pixels
			else if(videoInput == 6)
			{
				state = 6;
			}
			break;
			
			
			//State 5: Hard Right Turn
			case 5:
			HBridgeCommand(LMOT,18,0);
			HBridgeCommand(RMOT,100,0);
			
			LCDGoToPosition(1,1);
			sprintf(LCD_out, "State 5");
			LCDSendString(LCD_out);
			LCDGoToPosition(1,2);
			sprintf(LCD_out, "SV: %d", videoInput);
			LCDSendString(LCD_out);
			_delay_ms(150);
			
			//Balanced White Pixels
			if(videoInput == 3)
			{
				state = 1;
			}
			//High pixels far left
			else if(videoInput == 1)
			{
				state = 3;
			}
			//High pixels middle left
			else if(videoInput == 2)
			{
				state = 2;
			}
			//High pixels middle right
			else if (videoInput == 4)
			{
				state = 4;
			}
			//Red line pixels
			else if(videoInput == 6)
			{
				state = 6;
			}
			break;
			
			//State 6: Stop
			case 6:
			_delay_ms(50000);
			HBridgeCommand(LMOT,0,0);
			HBridgeCommand(RMOT,0,0);
			
			LCDGoToPosition(1,1);
			sprintf(LCD_out, "State 6");
			LCDSendString(LCD_out);
			LCDGoToPosition(1,2);
			sprintf(LCD_out, "SV: %d", videoInput);
			LCDSendString(LCD_out);
			
			break;
			
		}//Switch block
			
    }//while loop
}//int main loop