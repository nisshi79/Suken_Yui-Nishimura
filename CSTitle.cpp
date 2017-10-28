#include "MyScene.h"
#include "Addons\COButton.h"
bool titlePlayFlag;
Graph ppGraph;
void CSTitle::Start() {
	Music.Load(3,"pic/t.mp3");
	ppGraph = "pic/t_pp2.png";
	titlePlayFlag = false;
	SetBackGround("pic/ui15.png");
	
}

void CSTitle::Loop() {
	Music.PlayLoop(3);
	if (Input.GetKeyEnter(Input.key.RETURN)) {
		Music.StopLoop(3);
		titlePlayFlag = true;
		Game.FlipScene(new CSGame(),Flip::FADE_OUT_IN);
	}
}

void CSTitle::Draw() {
	if (titlePlayFlag)ppGraph(0, 0);
}

void CSTitle::End() {
}