#include "Object.h"

suken::CObject::CObject() :deleteFlag(false) {}

suken::CObject::~CObject() {}

suken::CScene *const suken::CObject::GetScene() {
	return scene;
}

void suken::CObject::Start() {}

void suken::CObject::Loop() {}

void suken::CObject::Draw() {}

void suken::CObject::End() {}

void suken::CObject::SetScene(CScene* ptr) {
	scene = ptr;
}

void suken::CObject::Delete() {
	deleteFlag = true;
}

bool suken::CObject::GetDeleteFlag() {
	return deleteFlag;
}