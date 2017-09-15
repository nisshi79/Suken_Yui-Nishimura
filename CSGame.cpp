#include "MyScene.h"
#include <stdlib.h>
#include<iostream>
const float accel = 0.5;
const int veloMax = 3;
const int dushMax = 6;
const int RESET_X=100, RESET_Y=300;
const int FONT_SIZE=60;
Graph EDro::graph;
Graph Shot::graph;
Graph Killer::graph;
Graph Tail::graph;
Graph soldierGraph;
Graph bulletGraph;
Graph EDroGraph;
Graph levelupGraph;
Graph statusbarGraph;
Graph jDropGraph;
Graph lightGraph;
Graph redGraph;
Graph backY, backB, backG, backR, backP;
bool HitRectRect(const Rect& r1, const Rect& r2) {
	return r1.right > r2.left && r2.right > r1.left && r1.bottom > r2.top && r2.bottom > r1.top;
}
void DrawBox(const Rect& rect, int color, bool fillFlag = true) {
	DrawBox(rect.left, rect.top, rect.right, rect.bottom, color, fillFlag);
}
RectFlag HitMRectRect(float& x, float& y, float& vx, float& vy, const Rect& r1, const Rect& r2, const RectFlag& enable = RectFlag(true), RectFlag& flag = RectFlag()) {//���x�͑������킹�����z��
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
	AddFontResourceEx("pic/ Reef.otf", FR_PRIVATE, NULL);

	debug.bullet = true;
	debug.eDro = false;
	debug.level = false;

	levelChangeFlag = false;
	SetFontSize(FONT_SIZE);
	ChangeFont("Reef Bold");
	redGraph = "pic/red.png";
	lightGraph = "pic/light.png";
	backG = "pic/green.jpg";
	backY = "pic/yellow.jpg";
	backB = "pic/b.jpg";
	backP = "pic/purple.jpg";
	backR = "pic/red.jpg";
	highScore = 0;
	statusbarGraph = "pic/ui.png";
	x = 125;
	y = 450;
	vx = 0;
	vy = 0;
	j.Set(10,40, 0, 50);
	jb.Set(10, 40, 10,40 );
	Tail::graph = "pic/tail.png";
	jumpFlag = false;
	landFlag = true;
	eDro.flag = false;
	Shot::graph="pic/pb.png";
	Killer::graph= "pic/robot.png";
	EDro::graph = "pic/EDro.png";
	/*debug.Regist("x", &x);
	debug.Regist("y", &y);
	debug.Regist("vx", &vx);
	debug.Regist("vy", &vy);*/
	SetBackGround("pic/blue.jpg");
	bulletGraph = "pic/bamboo.png";
	soldierGraph = "pic/j.png";
	levelupGraph = "pic/levelup.png";
	jDropGraph = "pic/jDrop_2.png";
	fric=1.2;
	fric_a=0.3;
	for(int i=0;i!=10;++i){
		killer.b[i].flag=false;
	}
		for (int i = 0; i != 20; ++i) {
		pb[i].flag = false;
		tail[i].flag = false;
	}
	killer.Set(800,500);
	
	shield.Set(300, 600 - 55);
	LoadDivGraph("pic/blocks.png",3,3,1,50,50,block);
	
	eDroRectJ.Set(0, 50, 0, 50);
	MCE mce("MCE/Map.mce");
	for (int i = 0; i != 16; ++i) {
		for(int k=0;k!=12;++k){
			map[i][k] = mce.Get(mce.layer.A, i, k);
		}
	}
	/*brx = x + 25;
	bry = y + 25;*/
	edc = 0;
	hitFlag = false;
	level = 0;
}

void CSGame::Loop() {
	
	level = 6;
	if (score < 2000)playLevel = 5;
	if (score < 1500)playLevel = 4;
	if (score < 1000)playLevel = 3;
	if (score < 500)playLevel = 2;
	if (score < 200)playLevel = 1;
	if (score < 100)playLevel = 0;
	levelbuf2 = playLevel;
	if (levelbuf2 - levelbuf != 0) {
		levelChangeFlag = true;
	}
	else {
		levelChangeFlag = false;
	}
	levelbuf = playLevel;
	
	count += 1;
	//Move&Jump
	if (Input.GetKeyDown(Input.key.RIGHT) || Input.GetKeyDown(Input.key.D)) {
		vx += accel;
		if (vx < 0) {
			vx += accel;
		}
	}
	if (Input.GetKeyDown(Input.key.LEFT) || Input.GetKeyDown(Input.key.A)) {
		vx -= accel;
		if (vx > 0) {
			vx -= accel;
		}
	}
	jumpPower = -20;
	if (Input.GetKeyDown(Input.key.DOWN))jumpPower = -30;
	if (/*(Input.GetKeyEnter(Input.key.W)||Input.GetKeyDown(Input.key.UP)) &&*/ landFlag) {
		vy = jumpPower;
	}
	//Speed
	x += vx;
	y += vy;
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
				if (map[i - 1][k] == 1) {
					enable.left = false;
				}
				if (map[i + 1][k] == 1) {
					enable.right = false;
				}
				if (map[i][k - 1] == 1) {
					enable.top = false;
				}
				if (map[i][k + 1] == 1) {
					enable.bottom = false;
				}
			}
			HitMRectRect(x, y, vx, vy, j, r, enable, buf);
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
	if (x < 0) {
		x = 0;
	}
	if (x + 50 > 800)x = 750;
	//Floor&Gravity
	if (y + 50 >= 600) {
		y = 550;
		vy = 0;
	}
	else {
		vy += 0.5;
	}

	if (Input.GetKeyDown(Input.key.DOWN))vy += 1;

	//Tail
	for (int i = 0; i != 20; ++i) {
		if (count % 3 == 1) {
			if (tail[i].flag == false) {
				tail[i].flag = true;
				tail[i].vx = -20;
				
				tail[i].x = x ;
				tail[i].y = y + 25-8;
				break;
			}
		}
		if (tail[i].x + 16 < 0 || tail[i].x > 800) {
			tail[i].flag = false;
		}

	}
	for (int i = 0; i != 20; ++i) {
		if (tail[i].flag == true) {
			tail[i].x += tail[i].vx;
		}
	}

		//Bullet
	
		
			if (/*kbt == 1 &&*/ count % 30 == 1) {

				for (int i = 0; i != 10; ++i) {

					if (killer.b[i].flag == false) {
						switch (playLevel)
						{
						case 0: {
							redLong[i] = GetRand(30) + 20;
							bulletSpeed[i] = GetRand(2) + 3;
							break;
						}

						case 1: {
							redLong[i] = (30) + 50;
							bulletSpeed[i] = GetRand(3) + 2;
							break;
						}
						case 2: {
							redLong[i] = (50) + 50;
							bulletSpeed[i] = GetRand(4) + 1;
							break;
						}
						case 3: {
							redLong[i] = GetRand(100) + 100;
							bulletSpeed[i] = GetRand(4) + 1;
							break;
						}
						case 4: {
							redLong[i] = GetRand(150) + 100;
							bulletSpeed[i] = GetRand(4) + 3;
							break;
						}
						case 5: {
							redLong[i] = GetRand(280) + 20;
							bulletSpeed[i] = GetRand(5) + 2;
						}
						case 6: {
							redLong[i] = GetRand(300);
							bulletSpeed[i] = GetRand(6) + 2;
						}
						default:
							break;
						}
						killer.b[i].x = 800;
						killer.b[i].y = 500;/*GetRand(150)+(600 - 200 - 20-150);*/
						killer.b[i].vx = -bulletSpeed[i];
						killer.b[i].flag = true;
					}
					if (killer.b[i].x<0||killer.b[i].x>800) {
						killer.b[i].flag = false;
					}

				}
			
		}
			
			/*	for (int i=0; i != 10; i++) {
					if (killer.b[i].flag) {
					killer.b[i].x += killer.b[i].vx;
				}
			}*/
		//kbt = 0;
		//kbt = GetRand(20);
		//if (kbt == 1 && count / 60 % 8>=5) {
		//	for (int i = 0; i != 10; ++i) {
		//		if (killer.b[i].flag == false) {
		//			killer.b[i].x = 0;
		//			killer.b[i].y = 600 - 100 - 16;/*GetRand(150)+(600 - 200 - 20-150);*/
		//			killer.b[i].vx =10;
		//			killer.b[i].flag = true;
		//			break;
		//		}
		//		if (killer.b[i].x>800) {
		//			killer.b[i].flag = false;
		//		}

		//	}
		//}
		//BulletShield
	
		//BulletRect



		//SoldierShot

		for (int i = 0; i != 20; ++i) {
			if (Input.GetKeyDown(Input.key.X) && count % 6 == 1) {
				if (pb[i].flag == false) {
					pb[i].flag = true;
					if (vx >= 0 && !Input.GetKeyDown(Input.key.LEFT)) {
						pb[i].vx = 20;
					}
					if (vx < 0 || Input.GetKeyDown(Input.key.LEFT)) {
						pb[i].vx = -20;
					}
					pb[i].x = x + 25;
					pb[i].y = y + 25;
					break;
				}
			}
			if (pb[i].x + 16 < 0 || pb[i].x > 800) {
				pb[i].flag = false;
			}

		}
		for (int i = 0; i != 20; ++i) {
			if (pb[i].flag == true) {
				pb[i].x += pb[i].vx;
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

		//EDro
		if (debug.eDro) {

			if (eDro.x + 50 < 0 || eDro.x > 800 || eDro.y > 600) {
				eDro.flag = false;
				eDro.vx = 0;
				eDro.vy = 0;


			}
			if (eDro.flag == false && playLevel > 3) {
				edc += 1;
				if (edc / 60 >= GetRand(3) + 2) {

					int edd = GetRand(3);
					switch (edd) {
					case 0: {

						eDro.x = 0 - 50;
						eDro.y = GetRand(150) + 250;
						eDro.vx = 10;
						eDro.flag = true;
						edc = 0;
						break;
					}
					case 1: {

						eDro.x = GetRand(550) + 200;
						eDro.y = 0 - 50;
						eDro.vy = 10;
						eDro.vx = GetRand(10) + 1;
						eDro.flag = true;
						edc = 0;
						break;
					}
					case 2: {

						eDro.x = 800;
						eDro.y = GetRand(150) + 250;
						eDro.vx = -10;
						eDro.flag = true;
						edc = 0;
						break;
					}
					default:
						break;
					}

				}

			}

			eDro.x += eDro.vx;
			eDro.y += eDro.vy;
			//EDroRect


			float tEDroX = static_cast<float>(eDro.x);
			float tEDroY = static_cast<float> (eDro.y);
			float tEDroVx = static_cast <float>(eDro.vx);
			float tEDroVy = static_cast<float>(eDro.vy);
			eDroRectR = { eDro.x,eDro.x + 50,eDro.y,eDro.y + 50 };




			//SoldierShotHitToEDro
			if (eDro.flag) {
				/*if (HitMRectRect(x, y, vx, vy, j, eDroRectR, enable, buf).top)eDro.flag = false;*/
				for (int i = 0; i != 20; ++i) {
					if (HitRectRect(jb.Add(pb[i].x, pb[i].y), eDroRectR)) {
						eDro.flag = false;
						score += 100;
					}
				}
			}
			//bulletrect
			for (int i = 0; i != 10; ++i) {
				killer.b[i].x += bulletSpeed[i];
				if (x + 50 >= killer.b[i].x && x <= killer.b[i].x + redLong[i] && landFlag&& killer.b[i].flag == true || (HitRectRect(j.Add(x, y), eDroRectR) && eDro.flag)) {
					x = RESET_X;
					y = RESET_Y;
					vx = 0;
					eDro.flag = false;
					killer.b[i].flag = false;
					hitFlag = true;
					Sleep(500);
					hitFlag = false;
					score = 0;
				}
			}
			if (HitRectRect(j.Add(x, y), eDroRectR) && eDro.flag) {
				x = RESET_X;
				y = RESET_Y;
				vx = 0;
				Sleep(500);
			}
			for (int i = 0; i != 10; ++i) {
				if (x + 25 >= killer.b[i].x&&x + 25 <= killer.b[i].x + redLong[i]) {
					score += 1;
				}
			}
			if (score > highScore)highScore = score;
			if (levelChangeFlag) {
				countbuf = count;
			}
		}
	}

void CSGame::Draw() {

	

	
	switch (playLevel) {
	case 0: {
		break;
	}
	case 1: {
		backG(0, 0);
		break;
	}
	case 2: {
		backY(0, 0);
		break;
	}
	case 3: {
		backR(0, 0);
		break;
	}
	case 4: {
		backP(0,0);
		break;
	}
	case 5: {
		backB(0,0);
		break;
	}
		default:
			break;
	}
	


	//enemy_new
	if (playLevel > 3)killer.Draw();
	/*Rect r(300, 500, 400, 600);
	r.Draw();*/

	
	lightGraph();
	
	//Bullet

	

	
	

	
	if (Input.GetKeyDown(Input.key.DOWN)) {
		jDropGraph(x, y, vy < 0 || Input.GetKeyDown(Input.key.LEFT));
	}
	else{
		soldierGraph(x-25, y-25, vx < 0 || Input.GetKeyDown(Input.key.LEFT));
	}	
	//map
	for (int i = 0; i != 16; ++i) {
		for (int k = 0; k != 12; ++k) {
			int c = map[i][k];
			if (c > 0) {
				block[c - 1].Draw(i * 50, k * 50);
			}
		}
	}
	for (int i = 0; i != 20; ++i) {
		if (pb[i].flag)pb[i].Draw();
		
	}
	for (int i = 0; i != 20; ++i) {
		if (tail[i].flag)tail[i].Draw();
	}
	if (eDro.flag) {
		eDro.Draw();
	}
		statusbarGraph();
	if (count % 30 > 15) {
		DxLib::SetDrawBright(0, 0, 0);
	}
	if (count - countbuf < 60&&playLevel>=1&&count>60)levelupGraph();
	DxLib::SetDrawBright(255, 255, 255);
	DrawFormatString(317,68,GetColor(73,58,244),"%d",score);
	DrawFormatString(701, 64, GetColor(73, 58, 244), "%d",highScore);
	SetFontSize(120);
	DrawFormatString(14, 13, GetColor(244, 58, 58), "%d",playLevel);
	SetFontSize(FONT_SIZE);
	for (int i = 0; i != 10; ++i) {


		if (killer.b[i].flag)/*DxLib::DrawRotaGraph3(0, 0, 0,100, redLong[i] / 200, 1.0, 0, redGraph, true);*/DrawBox(killer.b[i].x, killer.b[i].y, killer.b[i].x + redLong[i], killer.b[i].y + 100, RED, true);
		/*	DrawGraph(700,300, killer.graph, FALSE);*/
	}
}



void CSGame::End() {

}