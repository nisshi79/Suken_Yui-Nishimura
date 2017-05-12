#pragma once
#include "Suken.h"

class CSTitle :public CScene {
	void Start();
	
	void Loop();
	
	void Draw();
	
	void End();
};


struct Rect {
	float left, right, top, bottom;
	Rect(float left, float right, float top, float bottom) {
		this->left = left;
		this->right = right;
		this->top = top;
		this->bottom = bottom;
	}
	Rect() {}
	
	void Set(int left,int right,int top,int bottom){
		this->left = left;
		this->right = right;
		this->top = top;
		this->bottom = bottom;
	}
	Rect Add(int x, int y)const{
		return Rect(left + x, right + x, top + y, bottom + y);
	}
};


void DrawBox(Rect size, int color, bool fill_flag);


struct Bullet {
	int x, y, vx;
	bool flag;
	static const int width = 15, hight = 15;
	const Rect size;
	Bullet(int left, int top) :size(left, left + width, top, top + hight) {}
	Bullet() {}
	void Draw() {
		DrawBox(size.Add(x,y), BLACK, true);
	}
	void Set(int x,int y) {
		this->x = x;
		this->y = y;
		
	}
};


struct Killer{
	int x, y;
	int graph = LoadGraph("pic/k.png");
	Bullet b[10];
	const Rect size;
	Killer(int x,int y):size(0,50,0,300),x(x),y(y){}
	Killer():size(0, 50, 0, 300) {}
	void Draw() {
	//	DrawGraph(700,300/*size.Add(x,y)*/,graph,TRUE);
	}
	void Set(int x, int y) {
		this->x = x;
		this->y = y;
	}
};


struct Shield {
	int x, y;
	const Rect size;
	Shield(int x, int y):size(0,30,0,55),x(x),y(y){}
	Shield():size(0,30,0,55){}
	void Draw() {
		DrawBox(size.Add(x, y), BLACK, true);
	}
	void Set(int x,int y){
		this->x = x;
		this->y = y;
		size.Add(x, y);
	}
	Rect rect() {
		return size.Add(x, y);
	} 
};



class CSGame :public CScene {
	float x;
	int y;
	float vx;
	int vy;
	int kbt;
	Killer killer;
	int vxk;
	float fric;
	float fric_a;
	Bullet bullet;
	Shield shield;
	Graph block[3];
	int map[16][12];

	void Start();
	
	void Loop();
	
	void Draw();
	
	void End();

};


class CSOver:public CScene{
	
	void Start();
	
	void Loop();
	
	void Draw();
	
	void End();
};