#include "MyScene.h"
#include "Addons\COButton.h"

void CSTitle::Start() {
	
	SetBackGround("pic/title_2.png");
}

void CSTitle::Loop() {
	if (Input.GetKeyEnter()) {
		Game.FlipScene(new CSGame(),Flip::FADE_OUT_IN);
	}
}

void CSTitle::Draw() {
	printf("—V‚×");
}

void CSTitle::End() {
}