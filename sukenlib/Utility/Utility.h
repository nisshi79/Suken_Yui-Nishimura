#pragma once

#include <DxLib.h>

#define RED		 		GetColor(255,0,0)
#define ORANGE	 		GetColor(255,122,0)
#define YELLOW	 		GetColor(255,255,0)
#define YELLOWGREEN		GetColor(122,255,0)
#define GREEN 		 	GetColor(0,255,0)
#define CYAN 			GetColor(0,255,255)
#define BLUE		 	GetColor(0,0,255)
#define PURPLE		 	GetColor(150,0,255)
#define MAGENTA		 	GetColor(255,0,255)

#define WHITE		 	GetColor(255,255,255)
#define LIGHTGRAY	 	GetColor(200,200,200)
#define GRAY		 	GetColor(128,128,128)
#define DARKGRAY	 	GetColor(80,80,80)
#define BLACK		 	GetColor(0,0,0)

#define RED_V			GetColor(238,0,38)	//v2
#define ORANGE_V		GetColor(255,89,11) //v5
#define YELLOW_V		GetColor(255,230,0) //v8
#define YELLOWGREEN_V	GetColor(153,207,21)//v10
#define GREEN_V			GetColor(51,162,61) //v12
#define CYAN_V			GetColor(5,93,135)	//v16
#define BLUE_V			GetColor(15,33,139)	//v18
#define PURPLE_V		GetColor(86,0,125)	//v22
#define MAGENTA_V		GetColor(175,0,101)	//v24

#define RED_S			GetColor(204,70,19)	//s2
#define ORANGE_S		GetColor(217,118,15)//s6
#define YELLOW_S		GetColor(204,185,20)//s8
#define YELLOWGREEN_S	GetColor(140,161,19)//s10
#define GREEN_S			GetColor(39,133,63)	//s12
#define CYAN_S			GetColor(32,91,133)	//s16
#define BLUE_S			GetColor(35,59,139)	//s18
#define PURPLE_S		GetColor(94,40,131)	//s22
#define MAGENTA_S		GetColor(153,15,79)	//s24

#define RED_B			GetColor(249,52,76)	//b2
#define ORANGE_B		GetColor(255,153,20)//b6
#define YELLOW_B		GetColor(255,242,49)//b8
#define YELLOWGREEN_B	GetColor(153,208,43)//b10
#define GREEN_B			GetColor(51,166,94)	//b12
#define CYAN_B			GetColor(29,134,174)//b16
#define BLUE_B			GetColor(56,108,176)//b18
#define PURPLE_B		GetColor(164,90,170)//b22
#define MAGENTA_B		GetColor(223,76,148)//b24

#define RED_DP			GetColor(158,0,44)	//dp2
#define ORANGE_DP		GetColor(163,74,2)	//dp6
#define YELLOW_DP		GetColor(163,130,4)	//dp8
#define YELLOWGREEN_DP	GetColor(81,133,23)	//dp10
#define GREEN_DP		GetColor(47,111,65)	//dp12
#define CYAN_DP			GetColor(4,67,109)	//dp16
#define BLUE_DP			GetColor(7,62,115)	//dp18
#define PURPLE_DP		GetColor(83,20,96)	//dp22
#define MAGENTA_DP		GetColor(116,0,80)	//dp24

//namespace suken {
//	struct Decimal {//èÊéZÅAèúéZéûÇ…ïÅí Ç…åÖóéÇøÇ∑ÇÈÇÃÇ≈ÅAíçà”
//		static const char BITS;
//		long long value;
//
//		Decimal();
//
//		Decimal(int arg);
//		Decimal(float arg);
//		Decimal(double arg);
//		Decimal(const Decimal& arg);
//
//		Decimal& operator =(int arg);
//		Decimal& operator =(float arg);
//		Decimal& operator =(double arg);
//		Decimal& operator =(const Decimal& arg);
//
//		Decimal operator +(int arg);
//		Decimal operator +(float arg);
//		Decimal operator +(double arg);
//		Decimal operator +(const Decimal& arg);
//
//		Decimal operator -(int arg);
//		Decimal operator -(float arg);
//		Decimal operator -(double arg);
//		Decimal operator -(const Decimal& arg);
//
//		Decimal operator *(int arg);
//		Decimal operator *(float arg);
//		Decimal operator *(double arg);
//		Decimal operator *(const Decimal& arg);
//
//		Decimal operator /(int arg);
//		Decimal operator /(float arg);
//		Decimal operator /(double arg);
//		Decimal operator /(const Decimal& arg);
//
//		Decimal& operator +=(int arg);
//		Decimal& operator +=(float arg);
//		Decimal& operator +=(double arg);
//		Decimal& operator +=(const Decimal& arg);
//
//		Decimal& operator -=(int arg);
//		Decimal& operator -=(float arg);
//		Decimal& operator -=(double arg);
//		Decimal& operator -=(const Decimal& arg);
//
//		Decimal& operator *=(int arg);
//		Decimal& operator *=(float arg);
//		Decimal& operator *=(double arg);
//		Decimal& operator *=(const Decimal& arg);
//
//		Decimal& operator /=(int arg);
//		Decimal& operator /=(float arg);
//		Decimal& operator /=(double arg);
//		Decimal& operator /=(const Decimal& arg);
//	};
//}