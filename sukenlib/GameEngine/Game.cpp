#include "Game.h"

suken::CGame::CGame():CScene(false) {}

void suken::CGame::Init(CScene* scene) {
	flip = nullptr;
	mode = nullptr;
	flag = 0;
	now.Reset(scene);
	if (now) {
		now->Start();
		now->Regist();
	}
}

void suken::CGame::Init(CScene* scene, Flip flip) {
	mode = nullptr;
	flag = 0;
	next.Reset(scene);
	if (next) {
		next->Start();
		next->Regist();
	}
	flag |= isFliping;//bit演算　フラグオン
	this->flip = new Flip(flip);
}

void suken::CGame::FlipScene(CScene* scene) {
	next.Reset(scene);
	flag |= isNextFlip;//bit演算　フラグオン
	flag &= ~isFliping;
	flip = nullptr;
}

void suken::CGame::FlipScene(CScene* scene, const char* ruleGraph, unsigned char speed, unsigned char gradate) {
	next.Reset(scene);
	flag |= isNextFlip;//bit演算　フラグオン
	flip = new Flip(Flip::DEFAULT, ruleGraph, "", speed, gradate);
}

void suken::CGame::FlipScene(CScene* scene, const char* ruleGraph, const char* ruleGraph2, unsigned char speed, unsigned char gradate) {
	next.Reset(scene);
	flag |= isNextFlip;//bit演算　フラグオン
	flip = new Flip(Flip::DEFAULT, ruleGraph, ruleGraph2, speed, gradate);
}

void suken::CGame::FlipScene(CScene* scene, Flip::Type flipType, unsigned char speed) {
	next.Reset(scene);
	flag |= isNextFlip;//bit演算　フラグオン
	flip = new Flip(flipType, "", "", speed);
}

void suken::CGame::DebugRegistFunc(const char* name, std::function<void()> func) {
#ifdef DEBUG
	debugFuncVoid.push_back(std::make_pair(name, func));
#endif // DEBUG
}

//void suken::CGame::DebugRegistFuncInt(const char* name, std::function<void(int)> func) {
//#ifdef DEBUG
//	debugFuncInt.push_back(std::make_pair(name, func));
//#endif // DEBUG
//}
//
//void suken::CGame::DebugRegistFuncDouble(const char* name, std::function<void(double)> func) {
//#ifdef DEBUG
//	debugFuncDouble.push_back(std::make_pair(name, func));
//#endif // DEBUG
//}

void suken::CGame::DrawNowLoading() {
	screen.Draw();
	loadingAnim.Draw(loadingPosX, loadingPosY);
}

bool suken::CGame::FlipTransition() {
	SetDrawBright(nullptr);
	bool flagBuf = false;
	DrawMode buf(DX_BLENDMODE_NOBLEND,255,255,255,255);
	if (now) {
		flagBuf = flip->Draw(screen, nextScreen, now->mode, next->mode);
	}
	else {
		flagBuf = flip->Draw(screen, nextScreen, &buf, next->mode);
	}
	return flagBuf;
}