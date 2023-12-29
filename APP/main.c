/*
` * main.c

 *
 *  Created on: Oct 24, 2023
 *      Author: Aziz
 */


#include"../LIB/STD_TYPES.h"
#include"../LIB/BIT_MATH.h"
#include"../MCAL/DIO/DIO_interface.h"
#include"../MCAL/PORT/PORT_interface.h"
#include"../HAL/CLCD/CLCD_interface.h"
#include"../HAL/KPD/KPD_interface.h"
#include<util/delay.h>

#define PadLeft 0
#define PadRight 1
#define Ball_I 2

u8 Pad1[8] =
{
		0b00011,
		0b00011,
		0b00011,
		0b00011,
		0b00011,
		0b00011,
		0b00011,
		0b00011
};
u8 Pad2[8] =
{
		0b11000,
		0b11000,
		0b11000,
		0b11000,
		0b11000,
		0b11000,
		0b11000,
		0b11000
};
u8 Ball[8] =
{
		0b00000,
		0b00000,
		0b00000,
		0b01110,
		0b01110,
		0b01110,
		0b00000,
		0b00000
};
u8 BallX=7;
u8 BallY=0;
u8 Pad1Y=0;
u8 Pad2Y=0;
u8 moveLeft =0;
u8 PressedKey=0;
u8 Goal=0;
u8 Player1=0;
u8 Player2=0;
void main()
{
	PORT_voidInit();
	CLCD_voidInit();
	CLCD_voidWriteSpecialCharacter(Pad1,PadLeft,0,Pad1Y);
	CLCD_voidWriteSpecialCharacter(Pad2,PadRight,15,Pad2Y);
	CLCD_voidWriteSpecialCharacter(Ball,Ball_I,BallX,BallY);

	while (1)
	{
		PressedKey=KPD_u8GetPressedKey();
		CLCD_voidSendCommand(1);
		CLCD_voidGoToXY(BallX,BallY);
		CLCD_voidSendData(Ball_I);
		CLCD_voidGoToXY(0,Pad1Y);
		CLCD_voidSendData(PadLeft);
		CLCD_voidGoToXY(15,Pad2Y);
		CLCD_voidSendData(PadRight);
		_delay_ms(200);

		if(Goal==1)
		{
			_delay_ms(1000);
			CLCD_voidSendCommand(1);
			CLCD_voidGoToXY(5,0);
			CLCD_voidWriteString("GOOOOOAL");
			CLCD_voidGoToXY(7,1);
			ClCD_voidWriteInteger(Player1);
			CLCD_voidSendData('-');
			ClCD_voidWriteInteger(Player2);
			BallX=7;
			BallY=0;
			Pad1Y=0;
			Pad2Y=0;
			Goal=0;
			_delay_ms(2000);
		}
		if(Player1 == 5 || Player2 == 5)
		{
			_delay_ms(1000);
			CLCD_voidSendCommand(1);
			CLCD_voidGoToXY(4,0);
			CLCD_voidWriteString("END GAME");
			BallX=7;
			BallY=0;
			_delay_ms(2000);
			if(Player1==5)
			{
				_delay_ms(1000);
				CLCD_voidSendCommand(1);
				CLCD_voidGoToXY(0,0);
				CLCD_voidWriteString("Player1 is the");
				CLCD_voidGoToXY(4,1);
				CLCD_voidWriteString("Winner");
				_delay_ms(4000);
				Player1=0;
				Player2=0;
			}
			else if(Player2==5)
			{
				_delay_ms(1000);
				CLCD_voidSendCommand(1);
				CLCD_voidGoToXY(0,0);
				CLCD_voidWriteString("Player2 is the");
				CLCD_voidGoToXY(4,1);
				CLCD_voidWriteString("Winner");
				_delay_ms(4000);
				Player1=0;
				Player2=0;
			}
		}
		if(moveLeft)
		{
			BallX--;
			if(PressedKey==9 && BallY ==1)
			{
				BallY--;
			}
			if(PressedKey==3 && BallY==0)
			{
				BallY++;
			}
			if(PressedKey==7 && Pad1Y==1)
			{
				Pad1Y--;
			}
			if(PressedKey==1 && Pad1Y==0)
			{
				Pad1Y++;
			}
		}
		else
		{
			BallX++;
			if(PressedKey==7 && BallY==1)
			{
				BallY--;
			}
			if(PressedKey==1 && BallY==0)
			{
				BallY++;
			}
			if(PressedKey==9 && Pad2Y==1)
			{
				Pad2Y--;
			}
			if(PressedKey==3 && Pad2Y==0)
			{
				Pad2Y++;
			}
		}
		if(BallX==0 && BallY==Pad1Y)
		{
			moveLeft=0;
			BallX+=2;
		}
		else if(BallX==0 && BallY != Pad1Y)
		{
			Goal=1;
			moveLeft=0;
			Player2++;
		}
		if (BallX==15 && BallY==Pad2Y)
		{
			moveLeft=1;
			BallX-=2;
		}
		else if (BallX==15 && BallY != Pad2Y)
		{
			Goal=1;
			moveLeft=1;
			Player1++;
		}
	}
}
