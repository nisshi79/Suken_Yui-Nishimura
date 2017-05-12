#include "Debug.h"

#include "../System/System.h"
#include "../GameEngine/Game.h"
#include "../GameEngine/Input.h"
#include <typeinfo>

#ifdef DEBUG

int suken::CDebug::mouseX = 0, suken::CDebug::mouseY = 0, suken::CDebug::scrolD = 0;

bool suken::CDebug::click = false;

LRESULT CALLBACK suken::CDebug::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam){
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_MOUSEMOVE:
		mouseX = LOWORD(lParam);
		mouseY = HIWORD(lParam);
		break;
	case WM_LBUTTONDOWN:
		click = true;
		break;
	case WM_MOUSEWHEEL:
		scrolD = (short)HIWORD(wParam)/WHEEL_DELTA;
		break;
	default:
		return(DefWindowProc(hWnd, msg, wParam, lParam));
	}
	return (0L);
}

void suken::CDebug::Awake() {
	rect = new RECT();
	WNDCLASS myProg;
	myProg.style = NULL;
	myProg.lpfnWndProc = WndProc;
	myProg.cbClsExtra = 0;
	myProg.cbWndExtra = 0;
	myProg.hInstance = System.GetHInstance();
	myProg.hIcon = NULL;
	myProg.hCursor = LoadCursor(NULL, IDC_ARROW);
	myProg.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	myProg.lpszMenuName = NULL;
	myProg.lpszClassName = "ウィンドウ１クラスネーム";
	RegisterClass(&myProg);
	hWnd = CreateWindow(
		"ウィンドウ１クラスネーム",
		"＜DebugWindow＞SukenlibObjective",
		WS_OVERLAPPED | WS_CAPTION | WS_THICKFRAME,
		0, 0, 1, 1,
		NULL, NULL, System.GetHInstance(), NULL
	);
	ShowWindow(hWnd, System.GetNCmdShow());
	UpdateWindow(hWnd);
}

void suken::CDebug::Start() {
//	DxLib::LoadDivGraph("SukenLibAsset/LOGO/debug.png", 5, 5, 1, 32, 32,graph);
	font = CreateFontToHandle("MS UI Gothic", 32, -1);
	stopFlag = false;
	writeFlag = false;
	scrol = 0;
}

void suken::CDebug::SetUp() {
	if (PeekMessage(&msg, hWnd, 0, 0, PM_REMOVE)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

void suken::CDebug::SetWindowSize(int width, int height) {
	SetWindowPos(hWnd, NULL, 0, 0, width, height,SWP_NOMOVE);
}

void suken::CDebug::Loop() {
	WaitTimer(2);
	SetBackgroundColor(255,255,255);
	GetClientRect(hWnd, rect);
	ClearDrawScreen();

	if (!writeFlag)scrol += scrolD;
	if (scrol > 0)scrol = 0;
	{
		int buf = 0;
		CScene* scene = &Game;
		while (scene != nullptr) {
			++buf;
			buf += scene->manager().size();
			buf += scene->debugFuncVoid.size();
//			buf += scene->debugFuncInt.size();
//			buf += scene->debugFuncDouble.size();
			buf += scene->debugStr.size();
			buf += scene->debugFlag.size();
//			buf += scene->debugUchar.size();
			buf += scene->debugInt.size();
//			buf += scene->debugUint.size();
			buf += scene->debugFloat.size();
			buf += scene->debugDouble.size();
			buf += scene->debugBool.size();
			scene = scene->now.Get();
		}
		if (scrol < - buf + 1)scrol = - buf + 1;
	}
	int num = scrol;

//	DrawGraph(0, 0, graph[4], true);
//	DrawBox(32, 0, min(System.GetWindowX(),min(System.GetWindowX(),rect->right)), 32, GrayB, true);
//	DrawBox(32, 2, min(System.GetWindowX(),min(System.GetWindowX(),rect->right)), 30, GrayW, true);
	DrawFormatStringToHandle(16, 0, 0,font, "fps");
//	DrawGraph(64, 0, graph[4], true);
	DrawFormatStringToHandle(80, 0, 0, font, "%.1f", System.GetFps());

	if (stopFlag) {
//		DrawGraph(160, 0, graph[2], true);
		DrawFormatStringToHandle(160 + 32, 0, 0, font, "STOP");
		if (!writeFlag) {
			if (GetMouseEnter(160 + 32, 0, min(System.GetWindowX(),rect->right), 32) || Input.GetKeyEnter(Input.key.LALT) || Input.GetKeyEnter(Input.key.RALT) || Input.GetKeyEnter(Input.key.RETURN)) {
				stopFlag = false;
			}
		}
	}
	else {
//		DrawGraph(160, 0, graph[0], true);
		DrawFormatStringToHandle(160 + 32, 0, 0, font, "PLAY");
		if (!writeFlag && (GetMouseEnter(160 + 32, 0, 288, 32) || Input.GetKeyEnter(Input.key.LALT) || Input.GetKeyEnter(Input.key.RALT))) {
			stopFlag = true;
		}
	}

//	DrawGraph(288, 0, graph[4], true);
	if (writeFlag && writing == 0) {
		ki->Draw(304, 0);
		DrawStringToHandle(304 + ki->GetWidth(), 0, ".png", 0, font);
		if (!ki->GetActive()) {
			if (!ki->IsEscaped()) {
				DxLib::SetDrawScreen(Game.screen);
				if (strBuf != "") {
					DxLib::SaveDrawScreenToPNG(0, 0, System.GetWindowX(), System.GetWindowY(), (strBuf + ".png").c_str());
				}
				DxLib::SetDrawScreen(DX_SCREEN_BACK);
			}
			writeFlag = false;
			delete ki;
		}
	}
	else {
		DrawFormatStringToHandle(304, 0, 0, font, "ScreenShot");
		if (GetMouseEnter(304, 0, min(System.GetWindowX(),rect->right), 32) && !writeFlag) {
			writeFlag = true;
			stopFlag = true;
			writing = 0;
			strBuf = "ss";
			ki = new CKeyInputString(&strBuf, 20, 32, "MS UI Gothic");
			ki->Active();
		}
	}

	/*
	DrawGraph(0, num * 32, graph[0], true);
	DrawBox(32, num*32, min(System.GetWindowX(),min(System.GetWindowX(),rect->right)), 32+ num * 32, GrayB, true);
	DrawBox(32, 2 + num * 32, min(System.GetWindowX(),min(System.GetWindowX(),rect->right)), 30 + num * 32, GrayW, true);
	DrawStringToHandle(32, num * 32, "RootScene(Game)", 0, font);*/
	

	CScene* scene = &Game;

	while (scene != nullptr){
		++num;
		
		if (0 < num) {
			if (num > System.GetWindowY() / 32)break;
			if (scene != &Game) {
				Draw(num, scene->object.GetSize(), typeid(*scene).name() + 6, true);
			}
			else {
				Draw(num, -1, "RootScene(Game)", true);
			}
		}

		for (int i = 0; i < scene->manager().size(); ++i) {
			++num;
			if (0 < num) {
				if (num > min(rect->bottom, System.GetWindowY()) / 32)break;
				std::string buf = typeid(*scene->manager()[i]).name() + 28;
				buf.pop_back();
				Draw(num, scene->manager()[i]->GetSize(), (buf + "(Manager)").c_str(), false);
			}
		}

		for (auto i = scene->debugFuncVoid.begin(); i != scene->debugFuncVoid.end(); ++i) {
			++num;
			if (0 < num) {
				if (num > min(rect->bottom, System.GetWindowY()) / 32)break;
				Draw(num, i->first.c_str(), i->second);
			}
		}

//		for (auto i = scene->debugFuncInt.begin(); i != scene->debugFuncInt.end(); ++i) {
//			++num;
//			if (0 < num) {
//				if (num > min(rect->bottom, System.GetWindowY()) / 32)break;
////				Draw(num, i->first.c_str(), i->second);
//			}
//		}
//
//		for (auto i = scene->debugFuncDouble.begin(); i != scene->debugFuncDouble.end(); ++i) {
//			++num;
//			if (0 < num) {
//				if (num > min(rect->bottom, System.GetWindowY()) / 32)break;
////				Draw(num, i->first.c_str(), i->second);
//			}
//		}

		for (auto i = scene->debugStr.begin(); i != scene->debugStr.end(); ++i) {
			++num;
			if (0 < num) {
				if (num > min(rect->bottom, System.GetWindowY()) / 32)break;
				Draw(num, i->first.c_str(),i->second.c_str());
			}
		}

		for (auto i = scene->debugFlag.begin(); i != scene->debugFlag.end(); ++i) {
			++num;
			if (0 < num) {
				if (num > min(rect->bottom, System.GetWindowY()) / 32)break;
				Draw(num, i->first.c_str(), i->second);
			}
		}

		for (auto i = scene->debugBool.begin(); i != scene->debugBool.end(); ++i) {
			++num;
			if (0 < num) {
				if (num > min(rect->bottom, System.GetWindowY()) / 32)break;
				Draw(num, i->first.c_str(), i->second);
			}
		}

		//for (auto i = scene->debugUchar.begin(); i != scene->debugUchar.end(); ++i) {
		//	++num;
		//	if (0 < num) {
		//		if (num > min(rect->bottom, System.GetWindowY()) / 32)break;
		//		Draw(num, i->first.c_str(), i->second);
		//	}
		//}

		for (auto i = scene->debugInt.begin(); i != scene->debugInt.end(); ++i) {
			++num;
			if (0 < num) {
				if (num > min(rect->bottom, System.GetWindowY()) / 32)break;
				Draw(num, i->first.c_str(), i->second);
			}
		}

		//for (auto i = scene->debugUint.begin(); i != scene->debugUint.end(); ++i) {
		//	++num;
		//	if (0 < num) {
		//		if (num > min(rect->bottom, System.GetWindowY()) / 32)break;
		//		Draw(num, i->first.c_str(), i->second);
		//	}
		//}

		for (auto i = scene->debugFloat.begin(); i != scene->debugFloat.end(); ++i) {
			++num;
			if (0 < num) {
				if (num > min(rect->bottom, System.GetWindowY()) / 32)break;
				Draw(num, i->first.c_str(), i->second);
			}
		}

		for (auto i = scene->debugDouble.begin(); i != scene->debugDouble.end(); ++i) {
			++num;
			if (0 < num) {
				if (num > min(rect->bottom, System.GetWindowY()) / 32)break;
				Draw(num, i->first.c_str(), i->second);
			}
		}
		
		scene = scene->now.Get();
	}

	click = false;
	scrolD = 0;
	SetScreenFlipTargetWindow(hWnd);
	DxLib::ScreenFlip();
}

void suken::CDebug::Draw(int num,int obj, const char* name, bool isScene) {
	if (isScene) {
//		DrawGraph(0, num * 32, graph[0], true);
//		DrawBox(32, num * 32, min(System.GetWindowX(),rect->right), 32 + num * 32, GrayB, true);
//		DrawBox(32, 2 + num * 32, min(System.GetWindowX(),rect->right), 30 + num * 32, GrayW, true);
		DrawStringToHandle(32, num * 32, name, 0, font);
//		DrawBox(min(System.GetWindowX(),rect->right)*3 / 4 + 32, num * 32, min(System.GetWindowX(),rect->right), 32 + num * 32, GrayB, true);
//		DrawBox(min(System.GetWindowX(),rect->right) * 3 / 4 + 32, 2 + num * 32, min(System.GetWindowX(),rect->right), 30 + num * 32, GrayW, true);
		if (obj != -1) {
//			DrawGraph(min(System.GetWindowX(), rect->right) * 3 / 4, num * 32, graph[4], true);
			DrawFormatStringToHandle(min(System.GetWindowX(), rect->right) * 3 / 4 + 32, num * 32, 0, font, "%d", obj);
		}
	}
	else {
//		DrawGraph(32, num * 32, graph[3], true);
//		DrawBox(64, num * 32, min(System.GetWindowX(),min(System.GetWindowX(),rect->right)) + 32, 32 + num * 32, GrayB, true);
//		DrawBox(64, 2 + num * 32, min(System.GetWindowX(),min(System.GetWindowX(),rect->right)) + 32, 30 + num * 32, GrayW, true);
		DrawStringToHandle(64, num * 32, name, 0, font);
//		DrawBox(min(System.GetWindowX(),rect->right) * 3 / 4 + 32, num * 32, min(System.GetWindowX(),rect->right), 32 + num * 32, GrayB, true);
//		DrawBox(min(System.GetWindowX(),rect->right) * 3 / 4 + 32, 2 + num * 32, min(System.GetWindowX(),rect->right), 30 + num * 32, GrayW, true);
//		DrawGraph(min(System.GetWindowX(),rect->right) * 3 / 4, num * 32, graph[4], true);
		DrawFormatStringToHandle(min(System.GetWindowX(),rect->right) * 3 / 4 + 32, num * 32, 0, font, "%d", obj);
	}
}

void suken::CDebug::Draw(int num, const char* name, const char* value) {
//	DrawGraph(32, num * 32, graph[4], true);
//	DrawBox(64, num * 32, min(System.GetWindowX(),min(System.GetWindowX(),rect->right)) + 32, 32 + num * 32, GrayB, true);
//	DrawBox(64, 2 + num * 32, min(System.GetWindowX(),min(System.GetWindowX(),rect->right)) + 32, 30 + num * 32, GrayW, true);
	DrawStringToHandle(64, num * 32, name, 0, font);
//	DrawBox(min(System.GetWindowX(),rect->right) / 2 + 32, num * 32, min(System.GetWindowX(),rect->right), 32 + num * 32, GrayB, true);
//	DrawBox(min(System.GetWindowX(),rect->right) / 2 + 32, 2 + num * 32, min(System.GetWindowX(),rect->right), 30 + num * 32, GrayW, true);
//	DrawGraph(min(System.GetWindowX(),rect->right) / 2, num * 32, graph[4], true);
	DrawStringToHandle(min(System.GetWindowX(),rect->right) / 2 + 32, num * 32,value, 0, font);
}

void suken::CDebug::Draw(int num, const char* name, bool flag) {
//	DrawGraph(32, num * 32, graph[4], true);
//	DrawBox(64, num * 32, min(System.GetWindowX(), min(System.GetWindowX(), rect->right)) + 32, 32 + num * 32, GrayB, true);
//	DrawBox(64, 2 + num * 32, min(System.GetWindowX(), min(System.GetWindowX(), rect->right)) + 32, 30 + num * 32, GrayW, true);
	DrawStringToHandle(64, num * 32, name, 0, font);
//	DrawBox(min(System.GetWindowX(), rect->right) / 2 + 32, num * 32, min(System.GetWindowX(), rect->right), 32 + num * 32, GrayB, true);
//	DrawBox(min(System.GetWindowX(), rect->right) / 2 + 32, 2 + num * 32, min(System.GetWindowX(), rect->right), 30 + num * 32, GrayW, true);
//	DrawGraph(min(System.GetWindowX(), rect->right) / 2, num * 32, graph[4], true);
	if (flag) {
		DrawStringToHandle(min(System.GetWindowX(), rect->right) / 2 + 32, num * 32, "true", 0xFF0000, font);
	}
	else {
		DrawStringToHandle(min(System.GetWindowX(), rect->right) / 2 + 32, num * 32, "false", 0, font);
	}
}

void suken::CDebug::Draw(int num, const char* name, std::function<void()> func) {
//	DrawGraph(32, num * 32, graph[2], true);
//	DrawBox(64, num * 32, min(System.GetWindowX(), min(System.GetWindowX(), rect->right)) + 32, 32 + num * 32, GrayB, true);
//	DrawBox(64, 2 + num * 32, min(System.GetWindowX(), min(System.GetWindowX(), rect->right)) + 32, 30 + num * 32, GrayW, true);
	DrawStringToHandle(64, num * 32, name, 0, font);
//	DrawBox(min(System.GetWindowX(), rect->right) / 3 + 32, num * 32, min(System.GetWindowX(), rect->right), 32 + num * 32, GrayB, true);
//	DrawBox(min(System.GetWindowX(), rect->right) / 3 + 32, 2 + num * 32, min(System.GetWindowX(), rect->right), 30 + num * 32, GrayW, true);
//	DrawGraph(min(System.GetWindowX(), rect->right) / 3, num * 32, graph[4], true);
	if (writeFlag && num == writing) {

	}
	else {
		DrawStringToHandle(min(System.GetWindowX(), rect->right) / 3 + 32, num * 32, "Do", 0, font);
		if (GetMouseEnter(min(System.GetWindowX(), rect->right) / 3 + 32, num * 32, min(System.GetWindowX(), rect->right) * 3 / 4, 32 + num * 32)) {
			func();
		}
	}
//	DrawBox(min(System.GetWindowX(), rect->right) * 3 / 4 + 32, num * 32, min(System.GetWindowX(), rect->right), 32 + num * 32, GrayB, true);
//	DrawBox(min(System.GetWindowX(), rect->right) * 3 / 4 + 32, 2 + num * 32, min(System.GetWindowX(), rect->right), 30 + num * 32, GrayW, true);
//	DrawGraph(min(System.GetWindowX(), rect->right) * 3 / 4, num * 32, graph[4], true);
	DrawStringToHandle(min(System.GetWindowX(), rect->right) * 3 / 4 + 32, num * 32,"void", 0, font);
}

//void suken::CDebug::Draw(int num, const char* name, std::function<void(int)> func) {
////	DrawGraph(32, num * 32, graph[2], true);
////	DrawBox(64, num * 32, min(System.GetWindowX(), min(System.GetWindowX(), rect->right)) + 32, 32 + num * 32, GrayB, true);
////	DrawBox(64, 2 + num * 32, min(System.GetWindowX(), min(System.GetWindowX(), rect->right)) + 32, 30 + num * 32, GrayW, true);
//	DrawStringToHandle(64, num * 32, name, 0, font);
////	DrawBox(min(System.GetWindowX(), rect->right) / 3 + 32, num * 32, min(System.GetWindowX(), rect->right), 32 + num * 32, GrayB, true);
////	DrawBox(min(System.GetWindowX(), rect->right) / 3 + 32, 2 + num * 32, min(System.GetWindowX(), rect->right), 30 + num * 32, GrayW, true);
////	DrawGraph(min(System.GetWindowX(), rect->right) / 3, num * 32, graph[4], true);
//	if (writeFlag && num == writing) {
//		ki->Draw(min(System.GetWindowX(), rect->right) / 3 + 32, num * 32);
//		if (!ki->GetActive()) {
//			if (!ki->IsEscaped()) {
//				func(intBuf);
//			}
//			writeFlag = false;
//			delete ki;
//		}
//	}
//	else {
//		DrawStringToHandle(min(System.GetWindowX(), rect->right) / 3 + 32, num * 32, "Do", 0, font);
//		if (GetMouseEnter(min(System.GetWindowX(), rect->right) / 3 + 32, num * 32, min(System.GetWindowX(), rect->right) * 3 / 4, 32 + num * 32)) {
//			writeFlag = true;
//			stopFlag = true;
//			writing = num;
//			ki = new CKeyInputNum(&intBuf, 10, 32, "MS UI Gothic");
//			ki->Active();
//		}
//	}
////	DrawBox(min(System.GetWindowX(), rect->right) * 3 / 4 + 32, num * 32, min(System.GetWindowX(), rect->right), 32 + num * 32, GrayB, true);
////	DrawBox(min(System.GetWindowX(), rect->right) * 3 / 4 + 32, 2 + num * 32, min(System.GetWindowX(), rect->right), 30 + num * 32, GrayW, true);
////	DrawGraph(min(System.GetWindowX(), rect->right) * 3 / 4, num * 32, graph[4], true);
//	DrawStringToHandle(min(System.GetWindowX(), rect->right) * 3 / 4 + 32, num * 32, "int", 0, font);
//}
//
//void suken::CDebug::Draw(int num, const char* name, std::function<void(double)> func) {
//	DrawGraph(32, num * 32, graph[2], true);
//	DrawBox(64, num * 32, min(System.GetWindowX(), min(System.GetWindowX(), rect->right)) + 32, 32 + num * 32, GrayB, true);
//	DrawBox(64, 2 + num * 32, min(System.GetWindowX(), min(System.GetWindowX(), rect->right)) + 32, 30 + num * 32, GrayW, true);
//	DrawStringToHandle(64, num * 32, name, 0, font);
//	DrawBox(min(System.GetWindowX(), rect->right) / 3 + 32, num * 32, min(System.GetWindowX(), rect->right), 32 + num * 32, GrayB, true);
//	DrawBox(min(System.GetWindowX(), rect->right) / 3 + 32, 2 + num * 32, min(System.GetWindowX(), rect->right), 30 + num * 32, GrayW, true);
//	DrawGraph(min(System.GetWindowX(), rect->right) / 3, num * 32, graph[4], true);
//	if (writeFlag && num == writing) {
//		ki->Draw(min(System.GetWindowX(), rect->right) / 3 + 32, num * 32);
//		if (!ki->GetActive()) {
//			if (!ki->IsEscaped()) {
//				func(doubleBuf);
//			}
//			writeFlag = false;
//			delete ki;
//		}
//	}
//	else {
//		DrawStringToHandle(min(System.GetWindowX(), rect->right) / 3 + 32, num * 32, "Do", 0, font);
//		if (GetMouseEnter(min(System.GetWindowX(), rect->right) / 3 + 32, num * 32, min(System.GetWindowX(), rect->right) * 3 / 4, 32 + num * 32)) {
//			writeFlag = true;
//			stopFlag = true;
//			writing = num;
//			ki = new CKeyInputNumF(&doubleBuf, 10, 32, "MS UI Gothic");
//			ki->Active();
//		}
//	}
//	DrawBox(min(System.GetWindowX(), rect->right) * 3 / 4 + 32, num * 32, min(System.GetWindowX(), rect->right), 32 + num * 32, GrayB, true);
//	DrawBox(min(System.GetWindowX(), rect->right) * 3 / 4 + 32, 2 + num * 32, min(System.GetWindowX(), rect->right), 30 + num * 32, GrayW, true);
//	DrawGraph(min(System.GetWindowX(), rect->right) * 3 / 4, num * 32, graph[4], true);
//	DrawStringToHandle(min(System.GetWindowX(), rect->right) * 3 / 4 + 32, num * 32, "double", 0, font);
//}
//
//void suken::CDebug::Draw(int num, const char* name, unsigned char* value) {
//	DrawGraph(32, num * 32, graph[1], true);
//	DrawBox(64, num * 32, min(System.GetWindowX(),min(System.GetWindowX(),rect->right)) + 32, 32 + num * 32, GrayB, true);
//	DrawBox(64, 2 + num * 32, min(System.GetWindowX(),min(System.GetWindowX(),rect->right)) + 32, 30 + num * 32, GrayW, true);
//	DrawStringToHandle(64, num * 32, name, 0, font);
//	DrawBox(min(System.GetWindowX(),rect->right) / 3 + 32, num * 32, min(System.GetWindowX(),rect->right), 32 + num * 32, GrayB, true);
//	DrawBox(min(System.GetWindowX(),rect->right) / 3 + 32, 2 + num * 32, min(System.GetWindowX(),rect->right), 30 + num * 32, GrayW, true);
//	DrawGraph(min(System.GetWindowX(),rect->right) / 3, num * 32, graph[4], true);
//	if (writeFlag && num == writing) {
//		ki->Draw(min(System.GetWindowX(),rect->right) / 3 + 32, num * 32);
//		if (!ki->GetActive()) {
//			if (!ki->IsEscaped()) {
//				if (intBuf > 255) {
//					*value = 255;
//				}
//				else if (intBuf < 0) {
//					*value = 0;
//				}
//				else {
//					*value = intBuf;
//				}
//			}
//			writeFlag = false;
//			delete ki;
//		}
//	}
//	else {
//		DrawFormatStringToHandle(min(System.GetWindowX(),rect->right) / 3 + 32, num * 32, 0,font,"%d",*value);
//		if (GetMouseEnter(min(System.GetWindowX(),rect->right) / 3 + 32, num * 32, min(System.GetWindowX(),rect->right) * 3 / 4, 32 + num * 32)) {
//			writeFlag = true;
//			stopFlag = true;
//			writing = num;
//			intBuf = *value;
//			ki = new CKeyInputNum(&intBuf, 3, 32, "MS UI Gothic");
//			ki->Active();
//		}
//	}
//	DrawBox(min(System.GetWindowX(),rect->right) * 3 / 4 + 32, num * 32, min(System.GetWindowX(),rect->right), 32 + num * 32, GrayB, true);
//	DrawBox(min(System.GetWindowX(),rect->right) * 3 / 4 + 32, 2 + num * 32, min(System.GetWindowX(),rect->right), 30 + num * 32, GrayW, true);
//	DrawGraph(min(System.GetWindowX(),rect->right) * 3 / 4, num * 32, graph[4], true);
//	DrawStringToHandle(min(System.GetWindowX(),rect->right) * 3 / 4 + 32, num * 32, "uchar", 0, font);
//}

void suken::CDebug::Draw(int num, const char* name, int* value) {
//	DrawGraph(32, num * 32, graph[1], true);
//	DrawBox(64, num * 32, min(System.GetWindowX(),min(System.GetWindowX(),rect->right)) + 32, 32 + num * 32, GrayB, true);
//	DrawBox(64, 2 + num * 32, min(System.GetWindowX(),min(System.GetWindowX(),rect->right)) + 32, 30 + num * 32, GrayW, true);
	DrawStringToHandle(64, num * 32, name, 0, font);
//	DrawBox(min(System.GetWindowX(),rect->right) / 3 + 32, num * 32, min(System.GetWindowX(),rect->right), 32 + num * 32, GrayB, true);
//	DrawBox(min(System.GetWindowX(),rect->right) / 3 + 32, 2 + num * 32, min(System.GetWindowX(),rect->right), 30 + num * 32, GrayW, true);
//	DrawGraph(min(System.GetWindowX(),rect->right) / 3, num * 32, graph[4], true);
	if (writeFlag && num == writing) {
		ki->Draw(min(System.GetWindowX(),rect->right) / 3 + 32, num * 32);
		if (!ki->GetActive()) {
			if (!ki->IsEscaped()) {
				*value = intBuf;
			}
			writeFlag = false;
			delete ki;
		}
	}
	else {
		DrawFormatStringToHandle(min(System.GetWindowX(),rect->right) / 3 + 32, num * 32, 0, font, "%d", *value);
		if (GetMouseEnter(min(System.GetWindowX(),rect->right) / 3 + 32, num * 32, min(System.GetWindowX(),rect->right) * 3 / 4, 32 + num * 32)) {
			writeFlag = true;
			stopFlag = true;
			writing = num;
			intBuf = *value;
			ki = new CKeyInputNum(&intBuf, 10, 32, "MS UI Gothic");
			ki->Active();
		}
	}
//	DrawBox(min(System.GetWindowX(),rect->right) * 3 / 4 + 32, num * 32, min(System.GetWindowX(),rect->right), 32 + num * 32, GrayB, true);
//	DrawBox(min(System.GetWindowX(),rect->right) * 3 / 4 + 32, 2 + num * 32, min(System.GetWindowX(),rect->right), 30 + num * 32, GrayW, true);
//	DrawGraph(min(System.GetWindowX(),rect->right) * 3 / 4, num * 32, graph[4], true);
	DrawStringToHandle(min(System.GetWindowX(),rect->right) * 3 / 4 + 32, num * 32, "int", 0, font);
}

//void suken::CDebug::Draw(int num, const char* name, unsigned int* value) {
//	DrawGraph(32, num * 32, graph[1], true);
//	DrawBox(64, num * 32, min(System.GetWindowX(),min(System.GetWindowX(),rect->right)) + 32, 32 + num * 32, GrayB, true);
//	DrawBox(64, 2 + num * 32, min(System.GetWindowX(),min(System.GetWindowX(),rect->right)) + 32, 30 + num * 32, GrayW, true);
//	DrawStringToHandle(64, num * 32, name, 0, font);
//	DrawBox(min(System.GetWindowX(),rect->right) / 3 + 32, num * 32, min(System.GetWindowX(),rect->right), 32 + num * 32, GrayB, true);
//	DrawBox(min(System.GetWindowX(),rect->right) / 3 + 32, 2 + num * 32, min(System.GetWindowX(),rect->right), 30 + num * 32, GrayW, true);
//	DrawGraph(min(System.GetWindowX(),rect->right) / 3, num * 32, graph[4], true);
//	if (writeFlag && num == writing) {
//		ki->Draw(min(System.GetWindowX(),rect->right) / 3 + 32, num * 32);
//		if (!ki->GetActive()) {
//			if (!ki->IsEscaped()) {
//				*value = intBuf;
//			}
//			writeFlag = false;
//			delete ki;
//		}
//	}
//	else {
//		DrawFormatStringToHandle(min(System.GetWindowX(),rect->right) / 3 + 32, num * 32, 0, font, "%d", *value);
//		if (GetMouseEnter(min(System.GetWindowX(),rect->right) / 3 + 32, num * 32, min(System.GetWindowX(),rect->right) * 3 / 4, 32 + num * 32)) {
//			writeFlag = true;
//			stopFlag = true;
//			writing = num;
//			intBuf = *value;
//			ki = new CKeyInputNum(&intBuf, 10, 32, "MS UI Gothic");
//			ki->Active();
//		}
//	}
//	DrawBox(min(System.GetWindowX(),rect->right) * 3 / 4 + 32, num * 32, min(System.GetWindowX(),rect->right), 32 + num * 32, GrayB, true);
//	DrawBox(min(System.GetWindowX(),rect->right) * 3 / 4 + 32, 2 + num * 32, min(System.GetWindowX(),rect->right), 30 + num * 32, GrayW, true);
//	DrawGraph(min(System.GetWindowX(),rect->right) * 3 / 4, num * 32, graph[4], true);
//	DrawStringToHandle(min(System.GetWindowX(),rect->right) * 3 / 4 + 32, num * 32, "uint", 0, font);
//}

void suken::CDebug::Draw(int num, const char* name, float* value) {
//	DrawGraph(32, num * 32, graph[1], true);
//	DrawBox(64, num * 32, min(System.GetWindowX(),min(System.GetWindowX(),rect->right)) + 32, 32 + num * 32, GrayB, true);
//	DrawBox(64, 2 + num * 32, min(System.GetWindowX(),min(System.GetWindowX(),rect->right)) + 32, 30 + num * 32, GrayW, true);
	DrawStringToHandle(64, num * 32, name, 0, font);
//	DrawBox(min(System.GetWindowX(),rect->right) / 3 + 32, num * 32, min(System.GetWindowX(),rect->right), 32 + num * 32, GrayB, true);
//	DrawBox(min(System.GetWindowX(),rect->right) / 3 + 32, 2 + num * 32, min(System.GetWindowX(),rect->right), 30 + num * 32, GrayW, true);
//	DrawGraph(min(System.GetWindowX(),rect->right) / 3, num * 32, graph[4], true);
	if (writeFlag && num == writing) {
		ki->Draw(min(System.GetWindowX(),rect->right) / 3 + 32, num * 32);
		if (!ki->GetActive()) {
			if (!ki->IsEscaped()) {
				*value = (float)doubleBuf;
			}
			writeFlag = false;
			delete ki;
		}
	}
	else {
		DrawFormatStringToHandle(min(System.GetWindowX(),rect->right) / 3 + 32, num * 32, 0, font, "%0.10f", *value);
		if (GetMouseEnter(min(System.GetWindowX(),rect->right) / 3 + 32, num * 32, min(System.GetWindowX(),rect->right) * 3 / 4, 32 + num * 32)) {
			writeFlag = true;
			stopFlag = true;
			writing = num;
			doubleBuf = *value;
			ki = new CKeyInputNumF(&doubleBuf, 20, 32, "MS UI Gothic");
			ki->Active();
		}
	}
//	DrawBox(min(System.GetWindowX(),rect->right) * 3 / 4 + 32, num * 32, min(System.GetWindowX(),rect->right), 32 + num * 32, GrayB, true);
//	DrawBox(min(System.GetWindowX(),rect->right) * 3 / 4 + 32, 2 + num * 32, min(System.GetWindowX(),rect->right), 30 + num * 32, GrayW, true);
//	DrawGraph(min(System.GetWindowX(),rect->right) * 3 / 4, num * 32, graph[4], true);
	DrawStringToHandle(min(System.GetWindowX(),rect->right) * 3 / 4 + 32, num * 32, "float", 0, font);
}

void suken::CDebug::Draw(int num, const char* name, double* value) {
//	DrawGraph(32, num * 32, graph[1], true);
//	DrawBox(64, num * 32, min(System.GetWindowX(), min(System.GetWindowX(), rect->right)) + 32, 32 + num * 32, GrayB, true);
//	DrawBox(64, 2 + num * 32, min(System.GetWindowX(), min(System.GetWindowX(), rect->right)) + 32, 30 + num * 32, GrayW, true);
	DrawStringToHandle(64, num * 32, name, 0, font);
//	DrawBox(min(System.GetWindowX(), rect->right) / 3 + 32, num * 32, min(System.GetWindowX(), rect->right), 32 + num * 32, GrayB, true);
//	DrawBox(min(System.GetWindowX(), rect->right) / 3 + 32, 2 + num * 32, min(System.GetWindowX(), rect->right), 30 + num * 32, GrayW, true);
//	DrawGraph(min(System.GetWindowX(), rect->right) / 3, num * 32, graph[4], true);
	if (writeFlag && num == writing) {
		ki->Draw(min(System.GetWindowX(), rect->right) / 3 + 32, num * 32);
		if (!ki->GetActive()) {
			if (!ki->IsEscaped()) {
				*value = doubleBuf;
			}
			writeFlag = false;
			delete ki;
		}
	}
	else {
		DrawFormatStringToHandle(min(System.GetWindowX(), rect->right) / 3 + 32, num * 32, 0, font, "%0.10f", *value);
		if (GetMouseEnter(min(System.GetWindowX(), rect->right) / 3 + 32, num * 32, min(System.GetWindowX(), rect->right) * 3 / 4, 32 + num * 32)) {
			writeFlag = true;
			stopFlag = true;
			writing = num;
			doubleBuf = *value;
			ki = new CKeyInputNumF(&doubleBuf, 20, 32, "MS UI Gothic");
			ki->Active();
		}
	}
//	DrawBox(min(System.GetWindowX(), rect->right) * 3 / 4 + 32, num * 32, min(System.GetWindowX(), rect->right), 32 + num * 32, GrayB, true);
//	DrawBox(min(System.GetWindowX(), rect->right) * 3 / 4 + 32, 2 + num * 32, min(System.GetWindowX(), rect->right), 30 + num * 32, GrayW, true);
//	DrawGraph(min(System.GetWindowX(), rect->right) * 3 / 4, num * 32, graph[4], true);
	DrawStringToHandle(min(System.GetWindowX(), rect->right) * 3 / 4 + 32, num * 32, "double", 0, font);
}

void suken::CDebug::Draw(int num, const char* name, bool* value) {
//	DrawGraph(32, num * 32, graph[1], true);
//	DrawBox(64, num * 32, min(System.GetWindowX(),min(System.GetWindowX(),rect->right)) + 32, 32 + num * 32, GrayB, true);
//	DrawBox(64, 2 + num * 32, min(System.GetWindowX(),min(System.GetWindowX(),rect->right)) + 32, 30 + num * 32, GrayW, true);
	DrawStringToHandle(64, num * 32, name, 0, font);
//	DrawBox(min(System.GetWindowX(),rect->right) / 3 + 32, num * 32, min(System.GetWindowX(),rect->right), 32 + num * 32, GrayB, true);
//	DrawBox(min(System.GetWindowX(),rect->right) / 3 + 32, 2 + num * 32, min(System.GetWindowX(),rect->right), 30 + num * 32, GrayW, true);
//	DrawGraph(min(System.GetWindowX(),rect->right) / 3, num * 32, graph[4], true);
	if (writeFlag && num == writing) {
		ki->Draw(min(System.GetWindowX(),rect->right) / 3 + 32, num * 32);
		if (!ki->GetActive()) {
			if (!ki->IsEscaped()) {
				if (strBuf == "true" || strBuf == "TRUE" || strBuf == "1")*value = true;
				if (strBuf == "false" || strBuf == "FALSE" || strBuf == "0")*value = false;
			}
			writeFlag = false;
			delete ki;
		}
	}
	else {
		if (*value) {
			DrawStringToHandle(min(System.GetWindowX(),rect->right) / 3 + 32, num * 32, "true", 0xFF0000, font);
		}
		else {
			DrawStringToHandle(min(System.GetWindowX(),rect->right) / 3 + 32, num * 32, "false", 0, font);
		}
		if (GetMouseEnter(min(System.GetWindowX(),rect->right) / 3 + 32, num * 32, min(System.GetWindowX(),rect->right) * 3 / 4, 32 + num * 32)) {
			writeFlag = true;
			stopFlag = true;
			writing = num;
			strBuf.clear();
			ki = new CKeyInputString(&strBuf, 5, 32, "MS UI Gothic");
			ki->Active();
		}
	}
//	DrawBox(min(System.GetWindowX(),rect->right) * 3 / 4 + 32, num * 32, min(System.GetWindowX(),rect->right), 32 + num * 32, GrayB, true);
//	DrawBox(min(System.GetWindowX(),rect->right) * 3 / 4 + 32, 2 + num * 32, min(System.GetWindowX(),rect->right), 30 + num * 32, GrayW, true);
//	DrawGraph(min(System.GetWindowX(),rect->right) * 3 / 4, num * 32, graph[4], true);
	DrawStringToHandle(min(System.GetWindowX(),rect->right) * 3 / 4 + 32, num * 32, "bool", 0, font);
}

bool suken::CDebug::GetMouseEnter(int x1, int y1, int x2, int y2) {
	return click && (x1 < mouseX && x2 > mouseX && y1 < mouseY && y2 > mouseY);
}

#endif // DEBUG