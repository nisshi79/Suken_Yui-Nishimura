#include "MyScene.h"
#include <stdlib.h>
void DrawBox(Rect size, int color, bool fill_flag){
	DrawBox(size.left, size.top, size.right, size.bottom, color, fill_flag);
}
void CSGame::Start() {	
	SetBackGround("pic/BackGround.png");
	x=125;
	y=550;
	vx=0;
	vy=0;
	fric=0.6;
	fric_a=0.3;
	for(int i=0;i!=10;++i){
		killer.b[i].flag=false;
	}
	killer.Set(700,300);
	bullet.Set(killer.x, killer.y);
	shield.Set(300, 600 - 55);
	LoadDivGraph("pic/blocks.png",3,3,1,50,50,block);
	MCE mce("MCE/Map.mce");
	for (int i = 0; i != 16; ++i) {
		for(int k=0;k!=12;++k){
			map[i][k] = mce.Get(mce.layer.A, i, k);
		}
	}
	/*brx = x + 25;
	bry = y + 25;*/
}

void CSGame::Loop() {
	//Speed
	x+=vx;
	y+=vy;
	
	
	//Fric
	if (vx>0 && y+50==600) {
		vx-=fric;
		if (vx-fric<=0) {
			vx=0;
		}
	}
	if (vx<0 && y+50==600) {
		vx+=fric;
		if (vx+fric>=0) {
			vx=0;
		}
	}
	if (vx>0 && y+50>0) {
		vx -= fric_a;
	}
	if (vx<0 && y+50>0) {
		vx += fric_a;
	}
	
	//Wall
	if(x<0){
		x=0;
	}	
	
	//Floor
	if (y+50>=600) {
		y=550;
		vy=0;
	}else{
		vy+=1;
	}

	//Bullet
	/*kbt = 0;
	
	kbt = GetRand(40);
		
	if(kbt==1){
		for(int i=0;i!=10;++i){
			if(killer.b[i].flag==false){
				killer.b[i].x=bullet.x;
				killer.b[i].y = GetRand(300-15) + 300-15;
				killer.b[i].vx=-10;
				killer.b[i].flag=true;
				break;
			}
			if(killer.b[i].x<0){
				killer.b[i].flag=false;
			}
			
		}
	}*/
	Rect buff = shield.rect();
	//BulletShield
	for (int i = 0; i != 10; ++i) {
		if (killer.b[i].x + killer.b[i].width <= buff.right && killer.b[i].y + killer.b[i].hight >= buff.top) {
			killer.b[i].flag=false;
			killer.b[i].x = bullet.x;
		}
	}
	for(int i=0;i!=10;++i){
		killer.b[i].x+=killer.b[i].vx;
		if(x+50>=killer.b[i].x && x <=killer.b[i].x+killer.b[i].width &&y+50>=killer.b[i].y && y<=killer.b[i].y+killer.b[i].hight && killer.b[i].flag == true){
				Game.FlipScene(new CSOver(),Flip::ROTATION_UP);
		}
	}
	
	
	//Move&Jump
				
	if (Input.GetKeyDown(Input.key.RIGHT)) {
		vx = 5;
	}
	if (Input.GetKeyDown(Input.key.LEFT)) {
		vx = -5;
	}
	if (Input.GetKeyEnter(Input.key.UP) && y == 550 || map[static_cast<int>(x)/50][y/50+1]==1) {
		vy = -20;
	}
	//mudstop
	/*if (map[static_cast<int>(x) / 50 +1][y/ 50] == 1) {
		vx=0 ;
		
	}*/
	int tx = x - static_cast<int>(x) % 50;
	if (map[static_cast<int>(x) / 50+1][y / 50] == 1 && static_cast<int>(x) %50<x+50 && !Input.GetKeyDown(Input.key.LEFT)) {
		vx = 0;
		x = x / 50 * 50;
	}
	if (map[static_cast<int>(x) / 50][y / 50] == 1 && x/50 * 50+50 > x && !Input.GetKeyDown(Input.key.RIGHT)) {
		vx = 0;
		x = x / 50 * 50;
	}
	if (map[static_cast<int>(x) / 50][y / 50 + 1] == 1 && y / 50 * 50 < y) {
		vy = 0;
		y = y / 50 * 50;
	}
	/*for (int i = 0; i != 16; ++i) {
		for (int k = 0; k != 12; ++k) {
			if (map[static_cast<int>(x)/50+1][y/50+1]!=1) {
						}else{

			}
		}
	}*/
}

void CSGame::Draw() {
	
	

	//Soldier
	DrawBox(x,y,x+50,y+50,RED,true);


	//Bullet
	for(int i=0;i!=10;++i){
		DrawBox(killer.b[i].x, killer.b[i].y, killer.b[i].x + killer.b[i].width, killer.b[i].y + killer.b[i].hight, BLACK, true);
		DrawGraph(700,300, killer.graph, FALSE);
	}
	
	
	//enemy_new
	killer.Draw();
	/*Rect r(300, 500, 400, 600);
	r.Draw();*/

	//Shield
	shield.Draw();
	for (int i = 0; i != 16; ++i) {
		for (int k = 0; k != 12; ++k) {
			int c = map[i][k];
			if (c > 0) {
				block[c-1].Draw(i * 50, k * 50);
			}
		}
	}
}



void CSGame::End() {

}