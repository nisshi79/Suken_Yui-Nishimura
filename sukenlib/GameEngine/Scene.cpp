#include "Scene.h"
#include "Object\Object.h"
#include "../System/System.h"

suken::DrawMode::DrawMode(unsigned char blendMode, unsigned char param, unsigned char red, unsigned char green, unsigned char blue) :
	blendMode(blendMode), param(param), red(red), green(green), blue(blue) {};

suken::CScene::CScene() {
	screen = MakeScreen(System.GetWindowX(),System.GetWindowY(),true);
	nextScreen = MakeScreen(System.GetWindowX(), System.GetWindowY(), true);
	scrol.Set(0, 0);
	flip = nullptr;
	mode = nullptr;
	flag = 0;
}

suken::CScene::CScene(bool fake) {}

suken::CScene::CScene(CScene* scene) {
	screen = MakeScreen(System.GetWindowX(), System.GetWindowY(), true);
	nextScreen = MakeScreen(System.GetWindowX(), System.GetWindowY(), true);
	scrol.Set(0, 0);
	flip = nullptr;
	mode = nullptr;
	flag = 0;
	now.Reset(scene);
	if (now) {
		now->Start();
		now->Regist();
	}
}

suken::CScene::CScene(CScene* scene, const char* ruleGraph, unsigned char speed, unsigned char gradate) {
	screen = MakeScreen(System.GetWindowX(), System.GetWindowY(), true);
	nextScreen = MakeScreen(System.GetWindowX(), System.GetWindowY(), true);
	scrol.Set(0, 0);
	mode = nullptr;
	flag = 0;
	next.Reset(scene);
	if (next) {
		next->Start();
		next->Regist();
	}
	flag |= isFliping;//bit演算　フラグオン
	flip = new Flip(Flip::DEFAULT, ruleGraph, "", speed, gradate);
}

suken::CScene::CScene(CScene* scene, const char* ruleGraph, const char* ruleGraph2, unsigned char speed, unsigned char gradate) {
	screen = MakeScreen(System.GetWindowX(), System.GetWindowY(), true);
	nextScreen = MakeScreen(System.GetWindowX(), System.GetWindowY(), true);
	scrol.Set(0, 0);
	mode = nullptr;
	flag = 0;
	next.Reset(scene);
	if (next) {
		next->Start();
		next->Regist();
	}
	flag |= isFliping;//bit演算　フラグオン
	flip = new Flip(Flip::DEFAULT, ruleGraph, ruleGraph2, speed, gradate);
}

suken::CScene::CScene(CScene* scene, Flip::Type flipType, unsigned char speed) {
	screen = MakeScreen(System.GetWindowX(), System.GetWindowY(), true);
	nextScreen = MakeScreen(System.GetWindowX(), System.GetWindowY(), true);
	scrol.Set(0, 0);
	mode = nullptr;
	flag = 0;
	next.Reset(scene);
	if (next) {
		next->Start();
		next->Regist();
	}
	flag |= isFliping;//bit演算　フラグオン
	flip = new Flip(flipType, "", "", speed);
}

suken::CScene::~CScene() {

}

void suken::CScene::FlipScene(CScene* scene) {
	next.Reset(scene);
	flag |= isNextFlip;//bit演算　フラグオン
	flag &= ~isFliping;
	flip = nullptr;
}

void suken::CScene::FlipScene(CScene* scene, const char* ruleGraph, unsigned char speed, unsigned char gradate) {
	next.Reset(scene);
	flag |= isNextFlip;//bit演算　フラグオン
	flip = new Flip(Flip::DEFAULT, ruleGraph, "", speed,gradate);
}

void suken::CScene::FlipScene(CScene* scene, const char* ruleGraph, const char* ruleGraph2, unsigned char speed, unsigned char gradate) {
	next.Reset(scene);
	flag |= isNextFlip;//bit演算　フラグオン
	flip = new Flip(Flip::DEFAULT, ruleGraph, ruleGraph2, speed, gradate);
}

void suken::CScene::FlipScene(CScene* scene, Flip::Type flipType, unsigned char speed) {
	next.Reset(scene);
	flag |= isNextFlip;//bit演算　フラグオン
	flip = new Flip(flipType, "", "", speed);
}

void suken::CScene::RemoveScene() {
	next.Reset(nullptr);
	flag |= isNextFlip;//bit演算　フラグオン
	flag &= ~isFliping;
	flip = nullptr;
}

void suken::CScene::RemoveScene(const char* ruleGraph, unsigned char speed, unsigned char gradate) {
	next.Reset(nullptr);
	flag |= isNextFlip;//bit演算　フラグオン
	flip = new Flip(Flip::DEFAULT, ruleGraph, "", speed, gradate);
}

void suken::CScene::RemoveScene(Flip::Type flipType, unsigned char speed) {
	next.Reset(nullptr);
	flag |= isNextFlip;//bit演算　フラグオン
	flip = new Flip(flipType, "", "", speed);
}

void suken::CScene::AddObject(CObject* object) {
	this->object.AddObject(object);
	object->SetScene(this);
}

void suken::CScene::SetScrol(float x, float y) {
	scrol.Set(x, y);
}

suken::Twin<float> suken::CScene::GetScrol() {
	return scrol;
}

float suken::CScene::GetScrolX() {
	return scrol.x;
}

float suken::CScene::GetScrolY() {
	return scrol.y;
}

void suken::CScene::SetBlendMode(unsigned char blendMode, unsigned char param) {
	if (mode == nullptr) {
		mode = new DrawMode(blendMode,param,255,255,255);
	}
	else {
		mode->blendMode = blendMode;
		mode->param = param;
	}
}

void suken::CScene::SetBright(unsigned char red, unsigned char green, unsigned char blue) {
	if (mode == nullptr) {
		mode = new DrawMode(DX_BLENDMODE_NOBLEND,255,red,green,blue);
	}
	else {
		mode->red = red;
		mode->green = green;
		mode->blue = blue;
	}
}

suken::DrawMode* suken::CScene::GetDrawMode() {
	return mode;
}

void suken::CScene::SetBackGround(const char* fileName) {
	backGround = fileName;
}

void suken::CScene::DebugPrint(const char* name, const char* string) {
#ifdef DEBUG
	debugStr.push_back(std::make_pair(name, string));
#endif // DEBUG
}

void suken::CScene::DebugPrintFlag(const char* name, bool flag) {
#ifdef DEBUG
	debugFlag.push_back(std::make_pair(name, flag));
#endif // DEBUG
}

void suken::CScene::DebugRegistFunc(const char* name, std::function<void()> func) {
#ifdef DEBUG
	debugFuncVoid.push_back(std::make_pair(name, func));
#endif // DEBUG
}

//void suken::CScene::DebugRegistFuncInt(const char* name, std::function<void(int)> func) {
//#ifdef DEBUG
//	debugFuncInt.push_back(std::make_pair(name, func));
//#endif // DEBUG
//}

//void suken::CScene::DebugRegistFuncDouble(const char* name, std::function<void(double)> func) {
//#ifdef DEBUG
//	debugFuncDouble.push_back(std::make_pair(name, func));
//#endif // DEBUG
//}

//void suken::CScene::DebugRegist(const char* name, unsigned char* value) {
//#ifdef DEBUG
//	debugUchar.push_back(std::make_pair(name, value));
//#endif // DEBUG
//}

void suken::CScene::DebugRegist(const char* name, int* value) {
#ifdef DEBUG
	debugInt.push_back(std::make_pair(name, value));
#endif // DEBUG
}

//void suken::CScene::DebugRegist(const char* name, unsigned int* value) {
//#ifdef DEBUG
//	debugUint.push_back(std::make_pair(name, value));
//#endif // DEBUG
//}

void suken::CScene::DebugRegist(const char* name, float* value) {
#ifdef DEBUG
	debugFloat.push_back(std::make_pair(name, value));
#endif // DEBUG
}

void suken::CScene::DebugRegist(const char* name, double* value) {
#ifdef DEBUG
	debugDouble.push_back(std::make_pair(name, value));
#endif // DEBUG
}

void suken::CScene::DebugRegist(const char* name, bool* value) {
#ifdef DEBUG
	debugBool.push_back(std::make_pair(name, value));
#endif // DEBUG
}

//void suken::CScene::DebugRemove(unsigned char* value) {
//#ifdef DEBUG
//	debugUchar.remove_if([value](const std::pair<std::string, unsigned char*>& p) {
//		return p.second == value;
//	});
//#endif // DEBUG
//}

void suken::CScene::DebugRemove(int* value) {
#ifdef DEBUG
	debugInt.remove_if([value](const std::pair<std::string, int*>& p) {
		return p.second == value;
	});
#endif // DEBUG
}

//void suken::CScene::DebugRemove(unsigned int* value) {
//#ifdef DEBUG
//	debugUint.remove_if([value](const std::pair<std::string, unsigned int*>& p) {
//		return p.second == value;
//	});
//#endif // DEBUG
//}

void suken::CScene::DebugRemove(float* value) {
#ifdef DEBUG
	debugFloat.remove_if([value](const std::pair<std::string, float*>& p) {
		return p.second == value;
	});
#endif // DEBUG
}

void suken::CScene::DebugRemove(double* value) {
#ifdef DEBUG
	debugDouble.remove_if([value](const std::pair<std::string, double*>& p) {
		return p.second == value;
	});
#endif // DEBUG
}

void suken::CScene::DebugRemove(bool* value) {
#ifdef DEBUG
	debugBool.remove_if([value](const std::pair<std::string, bool*>& p) {
		return p.second == value;
	});
#endif // DEBUG
}

void suken::CScene::Start() {}

void suken::CScene::Update() {
#ifdef DEBUG
	debugStr.clear();
	debugFlag.clear();
#endif // DEBUG
	if ((flag & isFliping) == 0) {//bit演算　フラグ判定　偽
		if (now) {
			now->Update();
		}
		else {
			object.Loop();
			for (auto i = manager().begin(); i != manager().end(); ++i) {
				(*i)->Loop();
			}
			Loop();
		}
	}
}

void suken::CScene::Loop() {}

void suken::CScene::Graphic() {
	backGround();
	object.Draw();
	for (auto i = manager().begin(); i != manager().end(); ++i) {
		(*i)->Draw();
	}
	Draw();
	if ((flag & isFliping) == 0) {//bit演算　フラグ判定　偽
		if (now) {
			SetDrawMode(now.Get());
			int buf = GetDrawScreen();
			SetDrawScreen(screen);
			ClearDrawScreen();
			now->Graphic();
			SetDrawScreen(buf);
			SetDrawBlendMode(now.Get());
			SetDrawBright(nullptr);
			screen.Draw();
		}
	}
	else {
		if (next && flip->cnt == 0) {
			SetDrawMode(next.Get());
			int buf = GetDrawScreen();
			SetDrawScreen(nextScreen);
			DxLib::ClearDrawScreen();
			next->Graphic();
			SetDrawScreen(buf);
		}
		if (FlipTransition()) {
			delete flip;
			flip = nullptr;
			now.Swap(next);
			next.Reset();
			flag &= ~isFliping;
		}
	}
}

void suken::CScene::Draw() {}

void suken::CScene::LoopEnd() {
	for (auto i = manager().begin(); i != manager().end(); ++i) {
		(*i)->LoopEnd();
	}
	Regist();
	if (now) {
		now->LoopEnd();
	}
	if (flag & isNextFlip) {//bit演算　フラグ判定
		System.GoLoading();
		if (now) {
			now->End();
		}
		if (flip != nullptr) {
			flag |= isFliping;//bit演算　フラグオン
		}
		else {
			now.Swap(next);
			next.Reset();
			if (now) {
				now->Start();
				now->Regist();
			}
		}
		if (next) {
			next->Start();
			next->Regist();
		}
		flag &= ~isNextFlip;//bit演算　フラグオフ
		System.EndLoad();
	}
}

void suken::CScene::End() {}

void suken::CScene::Regist() {
	object.Regist();
	for (auto i = manager().begin(); i != manager().end(); ++i) {
		(*i)->Regist();
	}
}

void suken::CScene::SetDrawMode(CScene* obj) {
	if (obj != nullptr && obj->mode != nullptr) {
		DxLib::SetDrawBlendMode(obj->mode->blendMode, obj->mode->param);
		DxLib::SetDrawBright(obj->mode->red, obj->mode->green, obj->mode->blue);
	}
	else {
		DxLib::SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		DxLib::SetDrawBright(255, 255, 255);
	}
}

void suken::CScene::SetDrawBlendMode(CScene* obj) {
	if (obj != nullptr && obj->mode != nullptr) {
		DxLib::SetDrawBlendMode(obj->mode->blendMode, obj->mode->param);
	}
	else {
		DxLib::SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}
}

void suken::CScene::SetDrawBright(CScene* obj) {
	if (obj != nullptr && obj->mode != nullptr) {
		DxLib::SetDrawBright(obj->mode->red, obj->mode->green, obj->mode->blue);
	}
	else {
		DxLib::SetDrawBright(255, 255, 255);
	}
}

bool suken::CScene::FlipTransition() {
	SetDrawBright(nullptr);
	bool flagBuf = false;
	if (now) {
		if (next) {
			flagBuf = flip->Draw(screen, nextScreen, now->mode, next->mode);
		}
		else {
			flagBuf = flip->DrawDisappear(screen, now->mode);
		}
	}
	else {
		flagBuf = flip->DrawAppear(nextScreen, next->mode);
	}
	return flagBuf;
}

suken::Flip::Flip(Type type, const char* ruleGraph, const char* ruleGraph2, unsigned char speed, unsigned char gradate) {
	this->type = type;
	this->graph = ruleGraph == "" ? -1 : LoadBlendGraph(ruleGraph);
	this->graph2 = ruleGraph2 == "" ? -1 : LoadBlendGraph(ruleGraph2);
	if (gradate < 1) {
		gradate = 1;
	}
	else if (gradate < 64) {
		gradate = 64;
	}
	else if (gradate < 128) {
		gradate = 128;
	}
	else {
		gradate = 255;
	}
	this->gradate = gradate;
	this->speed = speed > 0 ? speed : 1;
	this->cnt = 0;
}

void suken::Flip::SetDrawMode(DrawMode* drawMode) {
	if (drawMode != nullptr) {
		SetDrawBlendMode(drawMode->blendMode, drawMode->param);
	}
	else {
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}
}

bool suken::Flip::Draw(Graph now, Graph next, DrawMode* dNow, DrawMode* dNext) {
	int x = System.GetWindowX(), y = System.GetWindowY();//よく使うので変数短い
	double rad;
	switch (type) {
	default:
	case DEFAULT:
		if (graph != 0) {
			if (graph2 != 0) {
				if (speed*cnt < maxCount/2) {
					SetDrawMode(dNow);
					DrawBlendGraph(0, 0, now, true, graph, speed*cnt * 2, gradate);
				}
				else {
					SetDrawMode(dNext);
					DrawBlendGraph(0, 0, next, true, graph2, (255 - speed*cnt) * 2, gradate);
				}
			}
			else {
				SetDrawMode(dNext);
				DrawGraph(0, 0, next, true);
				SetDrawMode(dNow);
				DrawBlendGraph(0, 0, now, true, graph, speed*cnt, gradate);
			}
		}
		break;
	case CROSS_FADE:
		SetDrawMode(dNow);
		DrawGraph(0, 0, now, true);
		if (dNext != nullptr) {
			SetDrawBlendMode(dNext->blendMode == DX_BLENDMODE_NOBLEND ? DX_BLENDMODE_ALPHA : dNext->blendMode, speed*cnt);
		}
		else {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, speed*cnt);
		}
		DrawGraph(0, 0, next, true);
		break;
	case FADE_OUT_IN:
		if (speed*cnt < maxCount/2) {
			if (dNow != nullptr) {
				SetDrawBlendMode(dNow->blendMode == DX_BLENDMODE_NOBLEND ? DX_BLENDMODE_ALPHA : dNow->blendMode, 255 - speed*cnt * 2);
			}
			else {
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - speed*cnt * 2);
			}
			DrawGraph(0, 0, now, true);
		}
		else {
			if (dNext != nullptr) {
				SetDrawBlendMode(dNext->blendMode == DX_BLENDMODE_NOBLEND ? DX_BLENDMODE_ALPHA : dNext->blendMode, (speed*cnt - 128) * 2);
			}
			else {
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, (speed*cnt - 128) * 2);
			}
			DrawGraph(0, 0, next, true);
		}
		break;
	case SLIDE_UP:
		SetDrawMode(dNext);
		DrawGraph(0, 0, next, true);
		SetDrawMode(dNow);
		DrawGraph(0, -(speed*cnt*y) / 255, now, true);
		break;
	case SLIDE_DOWN:
		SetDrawMode(dNext);
		DrawGraph(0, 0, next, true);
		SetDrawMode(dNow);
		DrawGraph(0, (speed*cnt*y) / 255, now, true);
		break;
	case SLIDE_RIGHT:
		SetDrawMode(dNext);
		DrawGraph(0, 0, next, true);
		SetDrawMode(dNow);
		DrawGraph((speed*cnt*x) / 255, 0, now, true);
		break;
	case SLIDE_LEFT:
		SetDrawMode(dNext);
		DrawGraph(0, 0, next, true);
		SetDrawMode(dNow);
		DrawGraph(-(speed*cnt*x) / 255, 0, now, true);
		break;
	case SCALEDOWN_ROTATION_RIGHT:
		SetDrawMode(dNext);
		DrawGraph(0, 0, next, true);
		SetDrawMode(dNow);
		if (speed*cnt >= maxCount/2) {
			if (dNow != nullptr) {
				SetDrawBlendMode(dNow->blendMode == DX_BLENDMODE_NOBLEND ? DX_BLENDMODE_ALPHA : dNow->blendMode, 255 - (speed*cnt - 128) * 2);
			}
			else {
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - (speed*cnt - 128) * 2);
			}
		}
		DrawRotaGraph(x / 2, y / 2, ((double)(255 - speed*cnt)) / 255, ((double)(speed*cnt)) * DX_PI * 2 / 255, now, true);
		break;
	case SCALEDOWN_ROTATION_LEFT:
		SetDrawMode(dNext);
		DrawGraph(0, 0, next, true);
		SetDrawMode(dNow);
		if (speed*cnt >= maxCount/2) {
			if (dNow != nullptr) {
				SetDrawBlendMode(dNow->blendMode == DX_BLENDMODE_NOBLEND ? DX_BLENDMODE_ALPHA : dNow->blendMode, 255 - (speed*cnt - 128) * 2);
			}
			else {
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - (speed*cnt - 128) * 2);
			}
		}
		DrawRotaGraph(x / 2, y / 2, ((double)(255 - speed*cnt)) / 255, -((double)(speed*cnt)) * DX_PI * 2 / 255, now, true);
		break;
	case PUSH_UP:
		SetDrawMode(dNext);
		DrawGraph(0, -(speed*cnt*y) / 255 + y, next, true);
		SetDrawMode(dNow);
		DrawGraph(0, -(speed*cnt*y) / 255, now, true);
		break;
	case PUSH_DOWN:
		SetDrawMode(dNext);
		DrawGraph(0, (speed*cnt*y) / 255 - y, next, true);
		SetDrawMode(dNow);
		DrawGraph(0, (speed*cnt*y) / 255, now, true);
		break;
	case PUSH_RIGHT:
		SetDrawMode(dNext);
		DrawGraph((speed*cnt*x) / 255 - x, 0, next, true);
		SetDrawMode(dNow);
		DrawGraph((speed*cnt*x) / 255, 0, now, true);
		break;
	case PUSH_LEFT:
		SetDrawMode(dNext);
		DrawGraph(-(speed*cnt*x) / 255 + x, 0, next, true);
		SetDrawMode(dNow);
		DrawGraph(-(speed*cnt*x) / 255, 0, now, true);
		break;
	case ROTATION_RIGHT:
		rad = ((double)(speed*cnt)) * DX_PI / 255;
		if (speed*cnt < 128) {
			SetDrawMode(dNow);
			now.DrawModi((int)(x / 2 - x / 2 * cos(rad)), (int)(-y / 4 * sin(rad)), (int)(x / 2 + x / 2 * cos(rad)), (int)(y / 4 * sin(rad)), (int)(x / 2 + x / 2 * cos(rad)), (int)(y - y / 4 * sin(rad)), (int)(x / 2 - x / 2 * cos(rad)), (int)(y + y / 4 * sin(rad)));
		}
		else {
			SetDrawMode(dNext);
			next.DrawModi((int)(x / 2 + x / 2 * cos(rad)), (int)(y / 4 * sin(rad)), (int)(x / 2 - x / 2 * cos(rad)), (int)(-y / 4 * sin(rad)), (int)(x / 2 - x / 2 * cos(rad)), (int)(y + y / 4 * sin(rad)), (int)(x / 2 + x / 2 * cos(rad)), (int)(y - y / 4 * sin(rad)));
		}
		break;
	case ROTATION_LEFT:
		rad = ((double)(speed*cnt)) * DX_PI / 255;
		if (speed*cnt < 128) {
			SetDrawMode(dNow);
			now.DrawModi((int)(x / 2 - x / 2 * cos(rad)), (int)(y / 4 * sin(rad)), (int)(x / 2 + x / 2 * cos(rad)), (int)(-y / 4 * sin(rad)), (int)(x / 2 + x / 2 * cos(rad)), (int)(y + y / 4 * sin(rad)), (int)(x / 2 - x / 2 * cos(rad)), (int)(y - y / 4 * sin(rad)));
		}
		else {
			SetDrawMode(dNext);
			next.DrawModi((int)(x / 2 + x / 2 * cos(rad)), (int)(-y / 4 * sin(rad)), (int)(x / 2 - x / 2 * cos(rad)), (int)(y / 4 * sin(rad)), (int)(x / 2 - x / 2 * cos(rad)), (int)(y - y / 4 * sin(rad)), (int)(x / 2 + x / 2 * cos(rad)), (int)(y + y / 4 * sin(rad)));
		}
		break;
	case ROTATION_UP:
		rad = ((double)(speed*cnt)) * DX_PI / 255;
		if (speed*cnt < maxCount/2) {
			SetDrawMode(dNow);
			now.DrawModi((int)(-x / 4 * sin(rad)), (int)(y / 2 - y / 2 * cos(rad)), (int)(x + x / 4 * sin(rad)), (int)(y / 2 - y / 2 * cos(rad)), (int)(x - x / 4 * sin(rad)), (int)(y / 2 + y / 2 * cos(rad)), (int)(x / 4 * sin(rad)), (int)(y / 2 + y / 2 * cos(rad)));
		}
		else {
			SetDrawMode(dNext);
			next.DrawModi((int)(x / 4 * sin(rad)), (int)(y / 2 + y / 2 * cos(rad)), (int)(x - x / 4 * sin(rad)), (int)(y / 2 + y / 2 * cos(rad)), (int)(x + x / 4 * sin(rad)), (int)(y / 2 - y / 2 * cos(rad)), (int)(-x / 4 * sin(rad)), (int)(y / 2 - y / 2 * cos(rad)));
		}
		break;
	case ROTATION_DOWN:
		rad = ((double)(speed*cnt)) * DX_PI / 255;
		if (speed*cnt < maxCount / 2) {
			SetDrawMode(dNow);
			now.DrawModi((int)(x / 4 * sin(rad)), (int)(y / 2 - y / 2 * cos(rad)), (int)(x - x / 4 * sin(rad)), (int)(y / 2 - y / 2 * cos(rad)), (int)(x + x / 4 * sin(rad)), (int)(y / 2 + y / 2 * cos(rad)), (int)(-x / 4 * sin(rad)), (int)(y / 2 + y / 2 * cos(rad)));
		}
		else {
			SetDrawMode(dNext);
			next.DrawModi((int)(-x / 4 * sin(rad)), (int)(y / 2 + y / 2 * cos(rad)), (int)(x + x / 4 * sin(rad)), (int)(y / 2 + y / 2 * cos(rad)), (int)(x - x / 4 * sin(rad)), (int)(y / 2 - y / 2 * cos(rad)), (int)(x / 4 * sin(rad)), (int)(y / 2 - y / 2 * cos(rad)));
		}
		break;
	case DOOR_DEPTH_VERTICAL:
		rad = ((double)(speed*cnt)) * DX_PI / 255;
		SetDrawMode(dNext);
		next.Draw();
		SetDrawMode(dNow);
		DrawRectModiGraph(0, 0, (int)(x / 4 + x / 4 * cos(rad)), (int)(y / 8 - y / 8 * cos(rad)), (int)(x / 4 + x / 4 * cos(rad)), (int)(y / 8 * 7 + y / 8 * cos(rad)), 0, y, 0, 0, x / 2, y, now, true);
		DrawRectModiGraph((int)(x / 4 * 3 - x / 4 * cos(rad)), (int)(y / 8 - y / 8 * cos(rad)), x, 0, x, y, (int)(x / 4 * 3 - x / 4 * cos(rad)), (int)(y / 8 * 7 + y / 8 * cos(rad)), x / 2, 0, x / 2, y, now, true);
		break;
	case DOOR_COME_VERTICAL:
		rad = ((double)(speed*cnt)) * DX_PI / 255;
		SetDrawMode(dNext);
		next.Draw();
		SetDrawMode(dNow);
		DrawRectModiGraph(0, 0, (int)(x / 4 + x / 4 * cos(rad)), (int)(-y / 8 + y / 8 * cos(rad)), (int)(x / 4 + x / 4 * cos(rad)), (int)(y / 8 * 9 - y / 8 * cos(rad)), 0, y, 0, 0, x / 2, y, now, true);
		DrawRectModiGraph((int)(x / 4 * 3 - x / 4 * cos(rad)), (int)(-y / 8 + y / 8 * cos(rad)), x, 0, x, y, (int)(x / 4 * 3 - x / 4 * cos(rad)), (int)(y / 8 * 9 - y / 8 * cos(rad)), x / 2, 0, x / 2, y, now, true);
		break;
	case DOOR_DEPTH_HORIZONTAL:
		rad = ((double)(speed*cnt)) * DX_PI / 255;
		SetDrawMode(dNext);
		next.Draw();
		SetDrawMode(dNow);
		DrawRectModiGraph(0, 0, x, 0, (int)(x / 8 * 7 + x / 8 * cos(rad)), (int)(y / 4 + y / 4 * cos(rad)), (int)(x / 8 - x / 8 * cos(rad)), (int)(y / 4 + y / 4 * cos(rad)), 0, 0, x, y / 2, now, true);
		DrawRectModiGraph((int)(x / 4 - x / 4 * cos(rad)), (int)(y / 4 * 3 - y / 4 * cos(rad)), (int)(x / 4 * 3 + x / 4 * cos(rad)), (int)(y / 4 * 3 - y / 4 * cos(rad)), x, y, 0, y, 0, y / 2, x, y / 2, now, true);
		break;
	case DOOR_COME_HORIZONTAL:
		rad = ((double)(speed*cnt)) * DX_PI / 255;
		SetDrawMode(dNext);
		next.Draw();
		SetDrawMode(dNow);
		DrawRectModiGraph(0, 0, x, 0, (int)(x / 8 * 9 - x / 8 * cos(rad)), (int)(y / 4 + y / 4 * cos(rad)), (int)(-x / 8 + x / 8 * cos(rad)), (int)(y / 4 + y / 4 * cos(rad)), 0, 0, x, y / 2, now, true);
		DrawRectModiGraph((int)(-x / 8 + x / 8 * cos(rad)), (int)(y / 4 * 3 - y / 4 * cos(rad)), (int)(x / 8 * 9 - x / 8 * cos(rad)), (int)(y / 4 * 3 - y / 4 * cos(rad)), x, y, 0, y, 0, y / 2, x, y / 2, now, true);
		break;
	}

	if ((int)speed*cnt + speed >= maxCount) {
		return true;
	}
	else {
		++cnt;
		return false;
	}
}

bool suken::Flip::DrawAppear(Graph screen, DrawMode* mode) {
	int x = System.GetWindowX(), y = System.GetWindowY();//よく使うので変数短い
	double rad;
	switch (type) {
	default:
	case DEFAULT:
		if (graph != 0) {
			SetDrawMode(mode);
			DrawBlendGraph(0, 0, screen, true, graph, 255-speed*cnt, gradate);
		}
		else if (graph2 != 0) {
			SetDrawMode(mode);
			DrawBlendGraph(0, 0, screen, true, graph2, 255 - speed*cnt, gradate);
		}
		break;
	case CROSS_FADE:
	case FADE_OUT_IN:
		if (mode != nullptr) {
			SetDrawBlendMode(mode->blendMode == DX_BLENDMODE_NOBLEND ? DX_BLENDMODE_ALPHA : mode->blendMode, speed*cnt);
		}
		else {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, speed*cnt);
		}
		DrawGraph(0, 0, screen, true);
		break;
	case SLIDE_UP:
	case PUSH_UP:
		SetDrawMode(mode);
		DrawGraph(0, -(speed*cnt*y) / 255 + y, screen, true);
		break;
	case SLIDE_DOWN:
	case PUSH_DOWN:
		SetDrawMode(mode);
		DrawGraph(0, (speed*cnt*y) / 255 - y, screen, true);
		break;
	case SLIDE_RIGHT:
	case PUSH_RIGHT:
		SetDrawMode(mode);
		DrawGraph((speed*cnt*x) / 255 - x, 0, screen, true);
		break;
	case SLIDE_LEFT:
	case PUSH_LEFT:
		SetDrawMode(mode);
		DrawGraph(-(speed*cnt*x) / 255 + x, 0, screen, true);
		break;
	case SCALEDOWN_ROTATION_RIGHT:
		if (speed*cnt < maxCount / 2) {
			if (mode != nullptr) {
				SetDrawBlendMode(mode->blendMode == DX_BLENDMODE_NOBLEND ? DX_BLENDMODE_ALPHA : mode->blendMode, speed*cnt * 2);
			}
			else {
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, speed*cnt * 2);
			}
		}
		DrawRotaGraph(x / 2, y / 2, ((double)(speed*cnt)) / 255, ((double)(speed*cnt)) * DX_PI * 2 / 255, screen, true);
		break;
	case SCALEDOWN_ROTATION_LEFT:
		if (speed*cnt < maxCount / 2) {
			if (mode != nullptr) {
				SetDrawBlendMode(mode->blendMode == DX_BLENDMODE_NOBLEND ? DX_BLENDMODE_ALPHA : mode->blendMode, speed*cnt * 2);
			}
			else {
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, speed*cnt * 2);
			}
		}
		DrawRotaGraph(x / 2, y / 2, ((double)(speed*cnt)) / 255, -((double)(speed*cnt)) * DX_PI * 2 / 255, screen, true);
		break;
	case ROTATION_RIGHT:
		rad = ((double)(255 - speed*cnt)) * DX_PI / 510;
		SetDrawMode(mode);
		screen.DrawModi((int)(x / 2 - x / 2 * cos(rad)), (int)(-y / 4 * sin(rad)), (int)(x / 2 + x / 2 * cos(rad)), (int)(y / 4 * sin(rad)), (int)(x / 2 + x / 2 * cos(rad)), (int)(y - y / 4 * sin(rad)), (int)(x / 2 - x / 2 * cos(rad)), (int)(y + y / 4 * sin(rad)));
		break;
	case ROTATION_LEFT:
		rad = ((double)(255-speed*cnt)) * DX_PI / 510;
		SetDrawMode(mode);
		screen.DrawModi((int)(x / 2 - x / 2 * cos(rad)), (int)(y / 4 * sin(rad)), (int)(x / 2 + x / 2 * cos(rad)), (int)(-y / 4 * sin(rad)), (int)(x / 2 + x / 2 * cos(rad)), (int)(y + y / 4 * sin(rad)), (int)(x / 2 - x / 2 * cos(rad)), (int)(y - y / 4 * sin(rad)));
		break;
	case ROTATION_UP:
		rad = ((double)(255 - speed*cnt)) * DX_PI / 510;
		SetDrawMode(mode);
		screen.DrawModi((int)(-x / 4 * sin(rad)), (int)(y / 2 - y / 2 * cos(rad)), (int)(x + x / 4 * sin(rad)), (int)(y / 2 - y / 2 * cos(rad)), (int)(x - x / 4 * sin(rad)), (int)(y / 2 + y / 2 * cos(rad)), (int)(x / 4 * sin(rad)), (int)(y / 2 + y / 2 * cos(rad)));
		break;
	case ROTATION_DOWN:
		rad = ((double)(255 - speed*cnt)) * DX_PI / 510;
		SetDrawMode(mode);
		screen.DrawModi((int)(x / 4 * sin(rad)), (int)(y / 2 - y / 2 * cos(rad)), (int)(x - x / 4 * sin(rad)), (int)(y / 2 - y / 2 * cos(rad)), (int)(x + x / 4 * sin(rad)), (int)(y / 2 + y / 2 * cos(rad)), (int)(-x / 4 * sin(rad)), (int)(y / 2 + y / 2 * cos(rad)));
		break;
	case DOOR_DEPTH_VERTICAL:
		rad = ((double)(255 - speed*cnt)) * DX_PI / 255;
		SetDrawMode(mode);
		DrawRectModiGraph(0, 0, (int)(x / 4 + x / 4 * cos(rad)), (int)(y / 8 - y / 8 * cos(rad)), (int)(x / 4 + x / 4 * cos(rad)), (int)(y / 8 * 7 + y / 8 * cos(rad)), 0, y, 0, 0, x / 2, y, screen, true);
		DrawRectModiGraph((int)(x / 4 * 3 - x / 4 * cos(rad)), (int)(y / 8 - y / 8 * cos(rad)), x, 0, x, y, (int)(x / 4 * 3 - x / 4 * cos(rad)), (int)(y / 8 * 7 + y / 8 * cos(rad)), x / 2, 0, x / 2, y, screen, true);
		break;
	case DOOR_COME_VERTICAL:
		rad = ((double)(255 - speed*cnt)) * DX_PI / 255;
		SetDrawMode(mode);
		DrawRectModiGraph(0, 0, (int)(x / 4 + x / 4 * cos(rad)), (int)(-y / 8 + y / 8 * cos(rad)), (int)(x / 4 + x / 4 * cos(rad)), (int)(y / 8 * 9 - y / 8 * cos(rad)), 0, y, 0, 0, x / 2, y, screen, true);
		DrawRectModiGraph((int)(x / 4 * 3 - x / 4 * cos(rad)), (int)(-y / 8 + y / 8 * cos(rad)), x, 0, x, y, (int)(x / 4 * 3 - x / 4 * cos(rad)), (int)(y / 8 * 9 - y / 8 * cos(rad)), x / 2, 0, x / 2, y, screen, true);
		break;
	case DOOR_DEPTH_HORIZONTAL:
		rad = ((double)(255 - speed*cnt)) * DX_PI / 255;
		SetDrawMode(mode);
		DrawRectModiGraph(0, 0, x, 0, (int)(x / 8 * 7 + x / 8 * cos(rad)), (int)(y / 4 + y / 4 * cos(rad)), (int)(x / 8 - x / 8 * cos(rad)), (int)(y / 4 + y / 4 * cos(rad)), 0, 0, x, y / 2, screen, true);
		DrawRectModiGraph((int)(x / 4 - x / 4 * cos(rad)), (int)(y / 4 * 3 - y / 4 * cos(rad)), (int)(x / 4 * 3 + x / 4 * cos(rad)), (int)(y / 4 * 3 - y / 4 * cos(rad)), x, y, 0, y, 0, y / 2, x, y / 2, screen, true);
		break;
	case DOOR_COME_HORIZONTAL:
		rad = ((double)(255 - speed*cnt)) * DX_PI / 255;
		SetDrawMode(mode);
		DrawRectModiGraph(0, 0, x, 0, (int)(x / 8 * 9 - x / 8 * cos(rad)), (int)(y / 4 + y / 4 * cos(rad)), (int)(-x / 8 + x / 8 * cos(rad)), (int)(y / 4 + y / 4 * cos(rad)), 0, 0, x, y / 2, screen, true);
		DrawRectModiGraph((int)(-x / 8 + x / 8 * cos(rad)), (int)(y / 4 * 3 - y / 4 * cos(rad)), (int)(x / 8 * 9 - x / 8 * cos(rad)), (int)(y / 4 * 3 - y / 4 * cos(rad)), x, y, 0, y, 0, y / 2, x, y / 2, screen, true);
		break;
	case CROSS_SLIDE_HORIZONTAL:
		SetDrawMode(mode);
		DrawRectGraph((speed*cnt*x) / 255 - x, 0,0,0,x,y/2, screen, true,false);
		DrawRectGraph(-(speed*cnt*x) / 255 + x, y/2,0,y/2,x,y/2, screen, true,false);
		break;
	}

	if ((int)speed*cnt + speed >= maxCount) {
		return true;
	}
	else {
		++cnt;
		return false;
	}
}

bool suken::Flip::DrawDisappear(Graph screen, DrawMode* mode) {
	int x = System.GetWindowX(), y = System.GetWindowY();//よく使うので変数短い
	double rad;
	switch (type) {
	default:
	case DEFAULT:
		if (graph != 0) {
			SetDrawMode(mode);
			DrawBlendGraph(0, 0, screen, true, graph, speed*cnt, gradate);
		}
		else if (graph2 != 0) {
			SetDrawMode(mode);
			DrawBlendGraph(0, 0, screen, true, graph2, speed*cnt, gradate);
		}
		break;
	case CROSS_FADE:
	case FADE_OUT_IN:
		if (mode != nullptr) {
			SetDrawBlendMode(mode->blendMode == DX_BLENDMODE_NOBLEND ? DX_BLENDMODE_ALPHA : mode->blendMode, 255-speed*cnt);
		}
		else {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255-speed*cnt);
		}
		DrawGraph(0, 0, screen, true);
		break;
	case SLIDE_UP:
	case PUSH_UP:
		SetDrawMode(mode);
		DrawGraph(0, -(speed*cnt*y) / 255, screen, true);
		break;
	case SLIDE_DOWN:
	case PUSH_DOWN:
		SetDrawMode(mode);
		DrawGraph(0, (speed*cnt*y) / 255, screen, true);
		break;
	case SLIDE_RIGHT:
	case PUSH_RIGHT:
		SetDrawMode(mode);
		DrawGraph((speed*cnt*x) / 255, 0, screen, true);
		break;
	case SLIDE_LEFT:
	case PUSH_LEFT:
		SetDrawMode(mode);
		DrawGraph(-(speed*cnt*x) / 255, 0, screen, true);
		break;
	case SCALEDOWN_ROTATION_RIGHT:
		SetDrawMode(mode);
		if (speed*cnt >= maxCount / 2) {
			if (mode != nullptr) {
				SetDrawBlendMode(mode->blendMode == DX_BLENDMODE_NOBLEND ? DX_BLENDMODE_ALPHA : mode->blendMode, 255 - (speed*cnt - 128) * 2);
			}
			else {
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - (speed*cnt - 128) * 2);
			}
		}
		DrawRotaGraph(x / 2, y / 2, ((double)(255 - speed*cnt)) / 255, ((double)(speed*cnt)) * DX_PI * 2 / 255, screen, true);
		break;
	case SCALEDOWN_ROTATION_LEFT:
		SetDrawMode(mode);
		if (speed*cnt >= maxCount / 2) {
			if (mode != nullptr) {
				SetDrawBlendMode(mode->blendMode == DX_BLENDMODE_NOBLEND ? DX_BLENDMODE_ALPHA : mode->blendMode, 255 - (speed*cnt - 128) * 2);
			}
			else {
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - (speed*cnt - 128) * 2);
			}
		}
		DrawRotaGraph(x / 2, y / 2, ((double)(255 - speed*cnt)) / 255, -((double)(speed*cnt)) * DX_PI * 2 / 255, screen, true);
		break;
	case ROTATION_RIGHT:
		rad = ((double)(speed*cnt)) * DX_PI / 510;
		SetDrawMode(mode);
		screen.DrawModi((int)(x / 2 - x / 2 * cos(rad)), (int)(-y / 4 * sin(rad)), (int)(x / 2 + x / 2 * cos(rad)), (int)(y / 4 * sin(rad)), (int)(x / 2 + x / 2 * cos(rad)), (int)(y - y / 4 * sin(rad)), (int)(x / 2 - x / 2 * cos(rad)), (int)(y + y / 4 * sin(rad)));
		break;
	case ROTATION_LEFT:
		rad = ((double)(speed*cnt)) * DX_PI / 510;
		SetDrawMode(mode);
		screen.DrawModi((int)(x / 2 - x / 2 * cos(rad)), (int)(y / 4 * sin(rad)), (int)(x / 2 + x / 2 * cos(rad)), (int)(-y / 4 * sin(rad)), (int)(x / 2 + x / 2 * cos(rad)), (int)(y + y / 4 * sin(rad)), (int)(x / 2 - x / 2 * cos(rad)), (int)(y - y / 4 * sin(rad)));
		break;
	case ROTATION_UP:
		rad = ((double)(speed*cnt)) * DX_PI / 510;
		SetDrawMode(mode);
		screen.DrawModi((int)(-x / 4 * sin(rad)), (int)(y / 2 - y / 2 * cos(rad)), (int)(x + x / 4 * sin(rad)), (int)(y / 2 - y / 2 * cos(rad)), (int)(x - x / 4 * sin(rad)), (int)(y / 2 + y / 2 * cos(rad)), (int)(x / 4 * sin(rad)), (int)(y / 2 + y / 2 * cos(rad)));
		break;
	case ROTATION_DOWN:
		rad = ((double)(speed*cnt)) * DX_PI / 510;
		SetDrawMode(mode);
		screen.DrawModi((int)(x / 4 * sin(rad)), (int)(y / 2 - y / 2 * cos(rad)), (int)(x - x / 4 * sin(rad)), (int)(y / 2 - y / 2 * cos(rad)), (int)(x + x / 4 * sin(rad)), (int)(y / 2 + y / 2 * cos(rad)), (int)(-x / 4 * sin(rad)), (int)(y / 2 + y / 2 * cos(rad)));
		break;
	case DOOR_DEPTH_VERTICAL:
		rad = ((double)(speed*cnt)) * DX_PI / 255;
		SetDrawMode(mode);
		DrawRectModiGraph(0, 0, (int)(x / 4 + x / 4 * cos(rad)), (int)(y / 8 - y / 8 * cos(rad)), (int)(x / 4 + x / 4 * cos(rad)), (int)(y / 8 * 7 + y / 8 * cos(rad)), 0, y, 0, 0, x / 2, y, screen, true);
		DrawRectModiGraph((int)(x / 4 * 3 - x / 4 * cos(rad)), (int)(y / 8 - y / 8 * cos(rad)), x, 0, x, y, (int)(x / 4 * 3 - x / 4 * cos(rad)), (int)(y / 8 * 7 + y / 8 * cos(rad)), x / 2, 0, x / 2, y, screen, true);
		break;
	case DOOR_COME_VERTICAL:
		rad = ((double)(speed*cnt)) * DX_PI / 255;
		SetDrawMode(mode);
		DrawRectModiGraph(0, 0, (int)(x / 4 + x / 4 * cos(rad)), (int)(-y / 8 + y / 8 * cos(rad)), (int)(x / 4 + x / 4 * cos(rad)), (int)(y / 8 * 9 - y / 8 * cos(rad)), 0, y, 0, 0, x / 2, y, screen, true);
		DrawRectModiGraph((int)(x / 4 * 3 - x / 4 * cos(rad)), (int)(-y / 8 + y / 8 * cos(rad)), x, 0, x, y, (int)(x / 4 * 3 - x / 4 * cos(rad)), (int)(y / 8 * 9 - y / 8 * cos(rad)), x / 2, 0, x / 2, y, screen, true);
		break;
	case DOOR_DEPTH_HORIZONTAL:
		rad = ((double)(speed*cnt)) * DX_PI / 255;
		SetDrawMode(mode);
		DrawRectModiGraph(0, 0, x, 0, (int)(x / 8 * 7 + x / 8 * cos(rad)), (int)(y / 4 + y / 4 * cos(rad)), (int)(x / 8 - x / 8 * cos(rad)), (int)(y / 4 + y / 4 * cos(rad)), 0, 0, x, y / 2, screen, true);
		DrawRectModiGraph((int)(x / 4 - x / 4 * cos(rad)), (int)(y / 4 * 3 - y / 4 * cos(rad)), (int)(x / 4 * 3 + x / 4 * cos(rad)), (int)(y / 4 * 3 - y / 4 * cos(rad)), x, y, 0, y, 0, y / 2, x, y / 2, screen, true);
		break;
	case DOOR_COME_HORIZONTAL:
		rad = ((double)(speed*cnt)) * DX_PI / 255;
		SetDrawMode(mode);
		DrawRectModiGraph(0, 0, x, 0, (int)(x / 8 * 9 - x / 8 * cos(rad)), (int)(y / 4 + y / 4 * cos(rad)), (int)(-x / 8 + x / 8 * cos(rad)), (int)(y / 4 + y / 4 * cos(rad)), 0, 0, x, y / 2, screen, true);
		DrawRectModiGraph((int)(-x / 8 + x / 8 * cos(rad)), (int)(y / 4 * 3 - y / 4 * cos(rad)), (int)(x / 8 * 9 - x / 8 * cos(rad)), (int)(y / 4 * 3 - y / 4 * cos(rad)), x, y, 0, y, 0, y / 2, x, y / 2, screen, true);
		break;
	case CROSS_SLIDE_HORIZONTAL:
		SetDrawMode(mode);
		DrawRectGraph(-(speed*cnt*x) / 255, y / 2, 0, y / 2, x, y / 2, screen, true, false);
		DrawRectGraph((speed*cnt*x) / 255, 0,  0, 0, x, y / 2, screen, true, false);
		break;
	}

	if ((int)speed*cnt + speed >= maxCount) {
		return true;
	}
	else {
		++cnt;
		return false;
	}
}