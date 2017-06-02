#include "MyScene.h"
#include <stdlib.h>
bool HitRectRect(const Rect& r1, const Rect& r2) {
	return r1.right > r2.left && r2.right > r1.left && r1.bottom > r2.top && r2.bottom > r1.top;
}
void DrawBox(const Rect& rect, int color, bool fillFlag = true) {
	DrawBox(rect.left, rect.top, rect.right, rect.bottom, color, fillFlag);
}
RectFlag HitMRectRect(int& x, int& y, int& vx, int& vy, const Rect& r1, const Rect& r2, const RectFlag& enable = RectFlag(true), RectFlag& flag = RectFlag()) {//ë¨ìxÇÕë´ÇµçáÇÌÇπÇΩå„ÇëzíË
	Vector2D vec = { static_cast<float>(x),static_cast<float>(y) };

	if (HitRectRect(r1.Add(vec.x,vec.y), r2)) {
		vec.x -= vx;
		vec.y -= vy;
		Rect l = r1.Add(vec.x, vec.y);

		if (enable.left && (l.top - r2.bottom <= -(l.right - r2.left)) && (l.bottom - r2.top >= l.right - r2.left)) {
			x = r2.left - r1.right;
			vx = 0;
			flag.right = true;
		}
		if (enable.right && (l.top - r2.bottom <= l.left - r2.right) && (l.bottom - r2.top >= -(l.left - r2.right))) {
			x = r2.right - r1.left;
			vx = 0;
			flag.left = true;
		}
		if (enable.top && (l.bottom - r2.top <= l.right - r2.left) && (l.bottom - r2.top <= -(l.left - r2.right))) {
			y = r2.top - r1.bottom;
			vy = 0;
			flag.bottom = true;
		}
		if (enable.bottom && (l.top - r2.bottom >= -(l.right - r2.left)) && (l.top - r2.bottom >= l.left - r2.right)) {
			y = r2.bottom - r1.top;
			vy = 0;
			flag.top = true;
		}
	}
	return flag;
}
void DrawBox(Rect size, int color, bool fill_flag){
	DrawBox(size.left, size.top, size.right, size.bottom, color, fill_flag);
}
void CSGame::Start() {	
	x = 0;
	y = 0;
	vx = 0;
	vy = 0;
	j.left = 0;
	j.right = 50;
	j.top = 0;
	j.bottom = 50;
	jumpFlag = false;

	r = { 300,400,440,480 };

	/*debug.Regist("x", &x);
	debug.Regist("y", &y);
	debug.Regist("vx", &vx);
	debug.Regist("vy", &vy);*/
	SetBackGround("pic/BackGround.png");
	soldier.Set(125,550);
	
	fric=1.2;
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
	//Move&Jump
	if (Input.GetKeyDown(Input.key.RIGHT)) {
		vx = 5;
	}
	if (Input.GetKeyDown(Input.key.LEFT)) {
		vx = -5;
	}
	if (Input.GetKeyEnter(Input.key.UP) && (soldier.y == 550 || map[static_cast<int>(soldier.x) / 50][soldier.y / 50 + 1] == 1)) {
		vy = -20;
	}
	//Speed
	soldier.x+=vx;
	soldier.y+=vy;
	//for (int i = 0; i != 10; ++i) {
	//	RectFlag f = { true,true,true,true };
	//	if (i != 0) {
	//		f.left = false;
	//	}
	//	if (i != 9) {
	//		f.right = false;
	//	}
	//	HitMRectRect(x, y, vx, vy, j, b[i], f);
	//}
	RectFlag buf;
	
	
	int tvx = static_cast<int>(vx);
	HitMRectRect(soldier.x, y, tvx, vy, j, r, RectFlag(true), buf);
	

	//Fric
	if (vx > 0 && (y + 50 == 600 || map[static_cast<int>(soldier.x) / 50][y / 50 + 1] == 1)) {
		vx-=fric;
		if (vx-fric<=0) {
			vx=0;
		}
	}
	if (vx < 0 && (y + 50 == 600 || map[static_cast<int>(soldier.x) / 50][y / 50 + 1] == 1)) {
		vx+=fric;
		if (vx+fric>=0) {
			vx=0;
		}
	}
	if (vx>0 && soldier.y+50>0) {
		vx -= fric_a;
	}
	if (vx<0 && soldier.y+50>0) {
		vx += fric_a;
	}
	
	//Wall
	if(soldier.x<0){
		x=0;
	}	
	
	//Floor
	if (soldier.y + 50 >= 600) {
		soldier.y=550;
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
	soldier.Draw();
	


	//Bullet
	for(int i=0;i!=10;++i){
		DrawBox(killer.b[i].x, killer.b[i].y, killer.b[i].x + killer.b[i].width, killer.b[i].y + killer.b[i].hight, BLACK, true);
	/*	DrawGraph(700,300, killer.graph, FALSE);*/
	}
	
	
	//enemy_new
	/*killer.Draw();*/
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