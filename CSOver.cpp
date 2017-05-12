#include "MyScene.h"

void CSOver::Start() {	
	SetBackGround("pic/GAME_OVER.png");
}

void CSOver::Loop() {
	if (Input.GetKeyEnter()) {
		Game.FlipScene(new CSTitle(),Flip::SCALEDOWN_ROTATION_LEFT);
	}
}

void CSOver::Draw() {
	
}


void CSOver::End() {

}