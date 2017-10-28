#include "MyScene.h"
#include "Addons\COButton.h"
bool titlePlayFlag;
Graph ppGraph;
void CSTitle::Start() {
	ppGraph = "pic/t_pp2.png";
	titlePlayFlag = false;
	SetBackGround("pic/title_4.png");
	Music.Load(3, "pic/title.mp3");
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