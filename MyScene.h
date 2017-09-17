#pragma once
#include "Suken.h"

class CSTitle :public CScene {
	void Start();
	
	void Loop();
	
	void Draw();
	
	void End();
};
struct Int2 {
	int x, y;
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
	int width , hight = 100;
	void Draw() {
		DrawBox(x,y,x+width, y+hight,RED, true);
	}
	void Draw2() {
		/*DxLib::DrawRotaGraph3(x, y, 0, 100, width / 200, 1.0, 0, redGraph, true);*/
	}
	void Set(int x,int y) {
		this->x = x;
		this->y = y;
		
	}
};

struct Killer{
	int x, y;
	static Graph graph;
	Bullet b[10];
	const Rect size;
	Killer(int x,int y):size(0,100,0,500),x(x),y(y){}
	Killer():size(0, 50, 0, 300) {}
	void Draw() {
		graph(0,0);
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
		/*DrawBox(size.Add(x, y), BLACK, true);*/
	}
	void Set(int x,int y){
		this->x = x;
		this->y = y;
		size.Add(x, y);
	}
	Rect rect() {
		return size.Add(x,y);
	} 
};

//struct Soldier {
//	int x, y;
//	const Rect size;
//	Soldier(int x,int y):size(0,50,0,50),x(x),y(y){}
//	Soldier():size(0,50,0,50){}
//		void Draw(){
//			DrawGraph(x, y, soldierGraph, true);
//	}
//	void Set(int x, int y) {
//		this->x=x;
//		this->y=y;
//		size.Add(x, y);
//	}
//	Rect rect(){
//		size.Add(x,y);
//	}
//};



struct RectFlag {
	bool left, right, top, bottom;
	RectFlag() {
		left = false;
		right = false;
		top = false;
		bottom = false;
	}
	RectFlag(bool init) {
		left = init;
		right = init;
		top = init;
		bottom = init;
	}
	void Set(bool init) {
		left = init;
		right = init;
		top = init;
		bottom = init;
	}
};
struct Tail {
	bool flag;
	double x;
	double vx;
	double y;
	int gh;
	static Graph graph;

	
	void Draw() {
		graph(x, y);
	}
	void Set(int x, int y) {
		this->x = x;
		this->y = y;

	}
};
struct Shot{
	bool flag;
	double x;
	double vx;
	double y;
	int gh;
	Rect size;
	static Graph graph;
	Shot(int x, int y) :size(0, 14, 0, 14), x(x), y(y) {}
	Shot() :size(0, 14, 0, 14) {}
	void Draw() {
		graph(x, y);
	}
	void Set(int x, int y) {
		this->x = x;
		this->y = y;

	}
};

struct EDro{
	bool flag;
	float x, y, vx, vy;
	Rect size;
	static Graph graph;
	EDro(int x, int y) :size(0, 50, 0, 50), x(x), y(y) {}
	EDro() :size(0, 50, 0,50) {}
	void Draw() {
		graph(x, y);
	}
	void Set(int x, int y) {
		this->x = x;
		this->y = y;

	}
};

struct Debug {
	bool bullet, eDro, level;
};

class CSGame :public CScene {
	float x;
	float y;
	float vx;
	float vy;
	int kbt;
	int count;
	Killer killer;
	int vxk;
	float fric;
	float fric_a;
	Bullet bullet[10];
	Shield shield;
	Graph block[3];
	/*static Graph soldierGraph,bulletGraph;*/
	int map[16][12];
	int brx;
	int bry;
	void Start();
	int ix;
	int iy;
	bool landFlag;
	Shot shot;
	bool jumpFlag;
	Rect j, r,eDroRectJ,eDroRectR,jb;
	Shot pb[20];
	EDro eDro;
	Tail tail[20];
	int edc;
	int eDroRectBuf[4];
	int bamboSscore,eDroScore;
	int level;
	int redLongLevel[10];
	int redLong[10];
	int font00;
	int score;
	int highScore;
	std::string scoreString,highScoreString,levelString;
	int jumpPower;
	Debug debug;
	bool hitFlag;
	int playLevel;
	

	int bulletSpeed[10];
	bool levelChangeFlag;
	void Loop();
	int levelbuf, levelbuf2;
	void Draw();
	int countbuf;
	void End();

};


class CSOver:public CScene{
	
	void Start();
	
	void Loop();
	
	void Draw();
	
	
	void End();
};