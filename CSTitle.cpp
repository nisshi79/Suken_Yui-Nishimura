#include "MyScene.h"
#include "Addons\COButton.h"
bool titlePlayFlag;
Graph ppGraph;
void CSTitle::Start() {
	ppGraph = "pic/t_pp.png";
	titlePlayFlag = false;
	SetBackGround("pic/title_3.png");
}

void CSTitle::Loop() {
	if (Input.GetKeyEnter(Input.key.X)) {
		titlePlayFlag = true;
		Game.FlipScene(new CSGame(),Flip::FADE_OUT_IN);
	}
}

void CSTitle::Draw() {
	if (titlePlayFlag)ppGraph(0, 0);
}

void CSTitle::End() {
}