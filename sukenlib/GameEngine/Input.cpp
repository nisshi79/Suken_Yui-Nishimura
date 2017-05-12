#include "Input.h"
#include "../Manager.h"
#include "../System/System.h"
#include "../Utility/Primitive.h"

suken::CInput::CInput() {
	for (int i = 0; i < 256; ++i) {
		keyInput[i] = 0;
	}
	mouseX = 0;
	mouseY = 0;
	for (int i = 0; i < 3; ++i) {
		mouseInput[i] = false;
		mouseInputLast[i] = false;
	}
}

void suken::CInput::Loop() {
	char buf[256];
	GetHitKeyStateAll(buf);
	for (int i = 0; i < 256; ++i) {
		if (buf[i]) {
			if (keyInput[i] <= 0) {
				keyInput[i] = 1;
			}
			else if(keyInput[i] < 2147483647){
				++keyInput[i];
			}
		}
		else{
			if (keyInput[i] >= 1) {
				keyInput[i] = 0;
			}
			else if (keyInput[i] > -2147483647) {
				--keyInput[i];
			}
		}
	}
	GetMousePoint(&mouseX, &mouseY);
	mouseWheel = GetMouseWheelRotVol();
	for (int i = 0; i < 3; ++i) {
		mouseInputLast[i] = mouseInput[i];
	}
	mouseInput[0] = (GetMouseInput() & MOUSE_INPUT_LEFT) != 0;
	mouseInput[1] = (GetMouseInput() & MOUSE_INPUT_RIGHT) != 0;
	mouseInput[2] = (GetMouseInput() & MOUSE_INPUT_MIDDLE) != 0;
}

bool suken::CInput::GetKeyDown(Key::KeyCode keyCode) {
	return keyInput[keyCode] >= 1;
}

bool suken::CInput::GetKeyDown() {
	for (int i = 0; i < 256; ++i) {
		if (keyInput[i] >= 1)return true;
	}
	return false;
}

bool suken::CInput::GetKeyEnter(Key::KeyCode keyCode) {
	return keyInput[keyCode] == 1;
}

bool suken::CInput::GetKeyEnter() {
	for (int i = 0; i < 256; ++i) {
		if (keyInput[i] == 1)return true;
	}
	return false;
}

bool suken::CInput::GetKeyExit(Key::KeyCode keyCode) {
	return keyInput[keyCode] == 0;
}

bool suken::CInput::GetKeyExit() {
	for (int i = 0; i < 256; ++i) {
		if (keyInput[i] == 0)return true;
	}
	return false;
}

int suken::CInput::GetKeyCount(Key::KeyCode keyCode) {
	return keyInput[keyCode];
}

bool suken::CInput::GetMouseDown(Mouse::MouseCode mouseCode) {
	return mouseInput[mouseCode] && (0 < mouseX && System.GetWindowX() > mouseX && 0 < mouseY && System.GetDispY() > mouseY);
}

bool suken::CInput::GetMouseDown(Mouse::MouseCode mouseCode, int x1, int y1, int x2, int y2) {
	return mouseInput[mouseCode] && (x1 < mouseX && x2 > mouseX && y1 < mouseY && y2 > mouseY);
}

bool suken::CInput::GetMouseDown() {
	if (0 < mouseX && System.GetWindowX() > mouseX && 0 < mouseY && System.GetDispY() > mouseY) {
		for (int i = 0; i < 3; ++i) {
			if (mouseInput[i]) {
				return true;
			}
		}
	}
	return false;
}

bool suken::CInput::GetMouseDown(int x1, int y1, int x2, int y2) {
	if (x1 < mouseX && x2 > mouseX && y1 < mouseY && y2 > mouseY) {
		for (int i = 0; i < 3; ++i) {
			if (mouseInput[i]) {
				return true;
			}
		}
	}
	return false;
}

bool suken::CInput::GetMouseOver() {
	return (0 < mouseX && System.GetWindowX() > mouseX && 0 < mouseY && System.GetDispY() > mouseY);
}

bool suken::CInput::GetMouseOver(int x1, int y1, int x2, int y2) {
	return (x1 < mouseX && x2 > mouseX && y1 < mouseY && y2 > mouseY);
}

bool suken::CInput::GetMouseEnter(Mouse::MouseCode mouseCode) {
	return !mouseInputLast[mouseCode] && mouseInput[mouseCode] && (0 < mouseX && System.GetWindowX() > mouseX && 0 < mouseY && System.GetDispY() > mouseY);
}

bool suken::CInput::GetMouseEnter(Mouse::MouseCode mouseCode, int x1, int y1, int x2, int y2) {
	return !mouseInputLast[mouseCode] && mouseInput[mouseCode] && (x1 < mouseX && x2 > mouseX && y1 < mouseY && y2 > mouseY);
}

bool suken::CInput::GetMouseEnter() {
	if (0 < mouseX && System.GetWindowX() > mouseX && 0 < mouseY && System.GetDispY() > mouseY) {
		for (int i = 0; i < 3; ++i) {
			if (!mouseInputLast[i] && mouseInput[i]) {
				return true;
			}
		}
	}
	return false;
}

bool suken::CInput::GetMouseEnter(int x1, int y1, int x2, int y2) {
	if (x1 < mouseX && x2 > mouseX && y1 < mouseY && y2 > mouseY) {
		for (int i = 0; i < 3; ++i) {
			if (!mouseInputLast[i] && mouseInput[i]) {
				return true;
			}
		}
	}
	return false;
}

bool suken::CInput::GetMouseExit(Mouse::MouseCode mouseCode) {
	return mouseInputLast[mouseCode] && !mouseInput[mouseCode];
}

bool suken::CInput::GetMouseExit(Mouse::MouseCode mouseCode, int x1, int y1, int x2, int y2) {
	return mouseInputLast[mouseCode] && !mouseInput[mouseCode] && (x1 < mouseX && x2 > mouseX && y1 < mouseY && y2 > mouseY);
}

bool suken::CInput::GetMouseExit() {
	if (0 < mouseX && System.GetWindowX() > mouseX && 0 < mouseY && System.GetDispY() > mouseY) {
		for (int i = 0; i < 3; ++i) {
			if (mouseInputLast[i] && !mouseInput[i]) {
				return true;
			}
		}
	}
	return false;
}

bool suken::CInput::GetMouseExit(int x1, int y1, int x2, int y2) {
	if (x1 < mouseX && x2 > mouseX && y1 < mouseY && y2 > mouseY) {
		for (int i = 0; i < 3; ++i) {
			if (mouseInputLast[i] && !mouseInput[i]) {
				return true;
			}
		}
	}
	return false;
}

int suken::CInput::GetMouseX() {
	return mouseX;
}

int suken::CInput::GetMouseY() {
	return mouseY;
}

suken::Twin<int> suken::CInput::GetMouseVector() {
	return Twin<int>(mouseX, mouseY);
}

int suken::CInput::GetMouseWheel() {
	return mouseWheel;
}