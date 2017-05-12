#pragma once

#include "../Manager.h"
#include "../Utility/KeyInputString.h"
#include <functional>

#ifdef DEBUG

namespace suken {
	class CDebug {
		static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

		void Awake();

		void Start();

		void SetUp();

		void Loop();

		void SetWindowSize(int width,int height);
		void Draw(int num,int obj, const char* name, bool isScene);
		void Draw(int num, const char* name, const char* value);
		void Draw(int num, const char* name, bool flag);

		void Draw(int num, const char* name, std::function<void()> func);/*
		void Draw(int num, const char* name, std::function<void(int)> func);
		void Draw(int num, const char* name, std::function<void(double)> func);*/
/*
		void Draw(int num, const char* name, unsigned char* value);*/
		void Draw(int num, const char* name, int* value);/*
		void Draw(int num, const char* name, unsigned int* value);*/
		void Draw(int num, const char* name, float* value);
		void Draw(int num, const char* name, double* value);
		void Draw(int num,const char* name, bool* value);

		bool GetMouseEnter(int x1, int y1, int x2, int y2);

		HWND hWnd;
		MSG msg;
		LPRECT rect;
/*
		static const int GrayB = 0x464646,GrayW = 0xB4B4B4;*/

		int /*graph[5],*/font,writing,scrol;

		static int mouseX, mouseY, scrolD;

		static bool click;

		bool stopFlag,writeFlag;

		CKeyInput* ki;

		int intBuf;
		double doubleBuf;
		std::string strBuf;

		friend class CSystem;
		friend int Main(HINSTANCE hInstance, HINSTANCE hPreInst, LPSTR lpszCmdLine, int nCmdShow);
	};
}

#endif