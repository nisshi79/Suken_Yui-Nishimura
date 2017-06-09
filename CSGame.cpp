#include "MyScene.h"
#include <stdlib.h>

const float accel = 0.5;
const int veloMax = 3;
const int dushMax = 6;

bool HitRectRect(const Rect& r1, const Rect& r2) {
	return r1.right > r2.left && r2.right > r1.left && r1.bottom > r2.top && r2.bottom > r1.top;
}
void DrawBox(const Rect& rect, int color, bool fillFlag = true) {
	DrawBox(rect.left, rect.top, rect.right, rect.bottom, color, fillFlag);
}
RectFlag HitMRectRect(float& x, float& y, float& vx, float& vy, const Rect& r1, const Rect& r2, const RectFlag& enable = RectFlag(true), RectFlag& flag = RectFlag()) {//ë¨ìxÇÕë´ÇµçáÇÌÇπÇΩå„ÇëzíË
	Vector2D vec = { x,static_cast<float>(y) };

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
	x = 75;
	y = 500;
	vx = 0;
	vy = 0;
	j.Set(10, 40, 0, 50);
	jumpFlag = false;
	landFlag = true;

	/*debug.Regist("x", &x);
	debug.Regist("y", &y);
	debug.Regist("vx", &vx);
	debug.Regist("vy", &vy);*/
	SetBackGround("pic/BackGround.png");
	bulletGraph = "pic/wood.png";
	soldierGraph = "pic/soldier_2.png";
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
	if (Input.GetKeyDown(Input.key.RIGHT)||Input.GetKeyDown(Input.key.D)) {
		vx += accel;
		if (vx < 0) {
			vx += accel;
		}
	}
	if (Input.GetKeyDown(Input.key.LEFT)||Input.GetKeyDown(Input.key.A)){
		vx -= accel;
		if (vx > 0) {
			vx -= accel;
		}
	}
	
	if ((Input.GetKeyEnter(Input.key.W)||Input.GetKeyEnter(Input.key.UP)) && landFlag) {
		vy = -10;
	}
	//Speed
	x+=vx;
	y+=vy;
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
	
	//blocks
	RectFlag buf(false);
	RectFlag enable(true);
	for (int i = 0; i != 16; ++i) {
		for (int k = 0; k != 12; ++k) {
			if (map[i][k] == 1) {
				r = { static_cast<float>(i) * 50,static_cast<float>(i) * 50 + 50,static_cast<float>(k) * 50,static_cast<float>(k) * 50 + 50 };
				enable.Set(true);
				if (map[i-1][k]==1) {
					enable.left = false;
				}
				if (map[i + 1][k]==1) {
					enable.right = false;
				}
				if (map[i][k - 1] == 1) {
					enable.top = false;
				}
				if (map[i][k + 1] == 1) {
					enable.bottom=false;
				}
			}
			HitMRectRect(x,y, vx, vy, j, r, enable, buf);
		}
	}

	landFlag = buf.bottom;


	
	//Fric
	//On The Ground
	if (landFlag) {
		if (!Input.GetKeyDown(Input.key.RIGHT) && !Input.GetKeyDown(Input.key.LEFT)) {
			if (vx > 0) {
				vx -= accel;
				if (vx < 0)
					vx = 0;
			}
			if (vx < 0) {
				vx += accel;
				if (vx > 0)
					vx = 0;
			}
		}
	}
	
	{
		int max = Input.GetKeyDown(Input.key.Z) ? dushMax : veloMax;
		if (vx > max)
			vx = max;
		if (vx < -max)
			vx = -max;
	}
	//Air
	/*if (vx>0 && y+50>0) {
		vx -= fric_a;
	}
	if (vx<0 && y+50>0) {
		vx += fric_a;
	}*/
	
	
	//Wall
	if(x<0){
		x= 0;
	}	
	
	//Floor
	if (y + 50 >= 600) {
		y=550;
		vy=0;
	}else{
		vy+=1;
	}

	//Bullet
	kbt = 0;
	kbt = GetRand(20);
		
	if(kbt==1){
		for(int i=0;i!=10;++i){
			if(killer.b[i].flag==false){
				killer.b[i].x=bullet.x;
				killer.b[i].y = 600 - 200-15;/*GetRand(150)+(600 - 200 - 20-150);*/
				killer.b[i].vx=-3;
				killer.b[i].flag=true;
				break;
			}
			if(killer.b[i].x<0){
				killer.b[i].flag=false;
			}
			
		}
	}
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
			x = 75;
			y = 500;
		}
	}
	
	
	
	//mudstop
	/*if (map[static_cast<int>(x) / 50 +1][y/ 50] == 1) {
		vx=0 ;
		
	}*/
	/*int tx = x - static_cast<int>(x) % 50;
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
	}*/
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
	
	soldierGraph(x, y,vx<0);


	//Bullet
	for(int i=0;i!=10;++i){
		bulletGraph(killer.b[i].x, killer.b[i].y);
	/*	DrawGraph(700,300, killer.graph, FALSE);*/
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