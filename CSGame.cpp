#include "MyScene.h"
#include <stdlib.h>
#include<iostream>
const float accel = 0.5;
const int veloMax = 3;
const int dushMax = 6;
const int RESET_X=100, RESET_Y=300;
const int FONT_SIZE=60;
const int INFINITY_TIME = 120;
const int TUTRIAL_TIME=240;


Graph EDro::graph;
Graph Shot::graph;
Graph Killer::graph;
Graph Tail::graph;
Graph Bullet::graph;
Graph soldierGraph;
Graph bulletGraph;
Graph EDroGraph;
Graph levelupGraph;
Graph statusbarGraph;
Graph jDropGraph;
Graph lightGraph;
Graph redGraph;
Graph backY, backB, backG, backR, backP;
Graph dmgGraph;
Graph heartGraph;
Graph tutrialGraph, shadowGraph;
Graph pauseGraph, pause_kGraph, pause_mGraph, pause_oGraph;
Graph sousaGraph;
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
	Music.Load(8, "pic/SB570835.wav");
	Music.Load(bgm,"pic/hurryup.mp3");
	Music.Load(1, "pic/button79.mp3");
	Music.Load(2, "pic/button80.mp3");
	Music.Load(4, "pic/damage.wav");
	Music.Load(5, "pic/over.wav");
	Music.Load(7, "pic/soundlogo42.mp3");
	AddFontResourceEx("pic/Ikaros-Regular.otf", FR_PRIVATE, NULL);
	downFlag = false;
	pause_kFlag = false;
	pause_oFlag = false;
	pause_mFlag = false;
	sousaGraph = "pic/sousa.png";
	jDropFlag = false;
	GameState = 0;
	debug.bullet = true;
	debug.eDro = false;
	debug.level = false;
	life = 3;
	levelChangeFlag = false;
	SetFontSize(FONT_SIZE);
	ChangeFont("Ikaros-Regular");
	redGraph = "pic/red.png";
	lightGraph = "pic/light.png";
	backG = "pic/g.png";
	backY = "pic/yellow.jpg";
	backB = "pic/b.jpg";
	backP = "pic/purple.jpg";
	backR = "pic/red.jpg";
	highScore = 0;
	statusbarGraph = "pic/st2.png";
	tutrialGraph = "pic/tutrial.png";
	x = 125;
	y = 450;
	vx = 0;
	vy = 0;
	j.Set(10,40, 0, 50);
	jb.Set(10, 40, 10,40 );
	Tail::graph = "pic/tail2.png";
	jumpFlag = false;
	landFlag = true;
	eDro.flag = false;
	Shot::graph="pic/pb.png";
	Killer::graph= "pic/robot.png";
	EDro::graph = "pic/drone.png";
	Bullet::graph = "pic/red.png";
	
	SetBackGround("pic/blue.jpg");
	bulletGraph = "pic/bamboo.png";
	soldierGraph = "pic/j.png";
	levelupGraph = "pic/levelup.png";
	jDropGraph = "pic/jDrop.png";
	heartGraph = "pic/heart.png";
	dmgGraph = "pic/dmg.png";
	pauseGraph = "pic/pause2.png";
	pause_kGraph = "pic/pause_k.png";
	pause_mGraph= "pic/pause_m.png";
	pause_oGraph = "pic/pause_o.png";


	shadowGraph = "pic/shadow2.png";
	fric=1.2;
	fric_a=0.3;
	for(int i=0;i!=10;++i){
		killer.b[i].flag = false; 
			bullet[i].flag = false;
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
	//Pause

	
	
	switch (GameState) {
	
	case 0: {
		
		Music.PlayLoop(bgm);
		if (Input.GetKeyDown(Input.key.DOWN) || Input.GetKeyDown(Input.key.S)) {
			downFlag = true;
		}
		else {
			downFlag = false;
		}
		if (Input.GetKeyEnter(Input.key.P)) {
			GameState = 1;
			Music.Play(1);
		}
		pause_kFlag = false;
		pause_oFlag = false;
		pause_mFlag = false;
		/*if (Input.GetKeyEnter(Input.key.L))score += 100;*/
		level = 6;
		if (score < 5000)playLevel = 5;
		if (score < 3000)playLevel = 4;
		if (score < 2000)playLevel = 3;
		if (score < 1000)playLevel = 2;
		if (score < 500)playLevel = 1;
		if (score < 200)playLevel = 0;
		levelbuf2 = playLevel;
		if (levelbuf2 - levelbuf != 0) {
			levelChangeFlag = true;
		}
		else {
			levelChangeFlag = false;
		}
		levelbuf = playLevel;
		if (levelChangeFlag)Music.Play(7);
		if (levelChangeFlag)life = 3;
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
		if (downFlag)jumpPower = -20;
		if (/*(Input.GetKeyEnter(Input.key.W)||Input.GetKeyDown(Input.key.UP)) &&*/ landFlag) {
			vy = jumpPower;
		}
		//Speed
		x += vx;
		y += vy;
		

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

		if (downFlag&& x > -1) {
			jDropFlag = true;
			vy += 1;
		}
		else {
			jDropFlag = false;
		}
		//Tail
		for (int i = 0; i != 20; ++i) {
			if (count % 3 == 1) {
				if (tail[i].flag == false) {
					tail[i].flag = true;
					tail[i].vx = -20;

					tail[i].x = x;
					tail[i].y = y + 25 - 8;
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


		if (count % 60 == 1 && count >= 360) {

			for (int i = 0; i != 10; ++i) {

				if (bullet[i].flag == false) {
					switch (playLevel)
					{
					case 0: {
						bullet[i].width = GetRand(30) + 20;
						bullet[i].vx = GetRand(2) + 3;
						break;
					}

					case 1: {
						bullet[i].width = (40) + 10;
						bullet[i].vx = GetRand(4) + 2;
						break;
					}
					case 2: {
						bullet[i].width = (30) + 50;
						bullet[i].vx = GetRand(6) + 4;
						break;
					}
					case 3: {
						bullet[i].width = GetRand(30) + 20;
						bullet[i].vx = GetRand(4) + 3;
						break;
					}
					case 4: {
						bullet[i].width = GetRand(30) + 10;
						bullet[i].vx = GetRand(5) + 2;
						break;
					}
					case 5: {
						bullet[i].width = GetRand(50) + 10;
						bullet[i].vx = GetRand(5) + 2;
					}
					case 6: {
						bullet[i].width = GetRand(60) + 10;
						bullet[i].vx = GetRand(6) + 2;
					}
					default:
						break;
					}
					bullet[i].x = 800;
					bullet[i].y = 500;
					bullet[i].flag = true;
					break;
				}


			}

		}

		for (int i = 0; i != 10; ++i) {
			if (bullet[i].x + bullet[i].width < 0 || bullet[i].x>800) {
				bullet[i].flag = false;
			}
		}
		for (int i = 0; i != 10; ++i) {
			bullet[i].x -= bullet[i].vx;
		}

		
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

	

		//eDro
		switch (playLevel)
		{
		case 3: {
			eDroSpeed = 8;
		}
		case 4: {
			eDroSpeed = 10;
		}
		case 5: {
			eDroSpeed = 16;
		}
		default:
			break;
		}

		if (eDro.x + 50 < 0 || eDro.x > 800 || eDro.y > 600) {
			eDro.flag = false;
			eDro.vx = 0;
			eDro.vy = 0;


		}
		if (playLevel >= 3) {
			edc += 1;
			if (edc / 60 >= GetRand(3) + 2) {

				int edd = GetRand(3);
				switch (edd) {
				case 0: {

					eDro.x = 0 - 50;
					eDro.y = GetRand(150) + 250;
					eDro.vx = eDroSpeed;
					eDro.flag = true;
					edc = 0;
					break;
				}
				case 1: {

				
					break;
				}
				case 2: {

					eDro.x = 800;
					eDro.y = GetRand(150) + 250;
					eDro.vx = -eDroSpeed;
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
			
		}
		for (int i = 0; i != 10; ++i) {
			if (count - countbuf2 > INFINITY_TIME) {
				if (bullet[i].x + bullet[i].width > x + 10 && x + 40 > bullet[i].x&&y + 51 >= 500 && bullet[i].flag) {
					countbuf2 = count;
					/*Sleep(100);*/
					life -= 1;
					Music.Play(4);
				}

				if (HitRectRect(j.Add(x, y), eDroRectR) && eDro.flag) {
					life -= 1;
					/*Sleep(100);*/
					countbuf2 = count;
					Music.Play(4);
				}
			}
			if (life == 0) {
				x = RESET_X;
				y = RESET_Y;
				vx = 0;
				eDro.flag = false;
				killer.b[i].flag = false;
				hitFlag = true;
				Music.Play(5);
				Sleep(500);
				hitFlag = false;
				score = 0;
				life = 3;
				for (int j = 0; j != 10; ++j) {
					bullet[j].flag = false;
				}
			}

		}

		for (int i = 0; i != 10; ++i) {
			if (x + 25 >= bullet[i].x&&x + 25 <= bullet[i].x + bullet[i].width) {
				score += 1;
			}
		}
		if (score > highScore)highScore = score;
		if (levelChangeFlag) {
			countbuf = count;
		}
		
		break;
 }
 case 1: {
	 Music.StopLoop(0);
	 if (Input.GetKeyEnter(Input.key.O)) {
		 GameState = 0;
		 pause_oFlag = true;
		 Music.Play(2);
		 Music.ReplayLoop(0);
	 }
	 if (Input.GetKeyDown(Input.key.K)) {
		 Game.FlipScene(new CSTitle(), Flip::FADE_OUT_IN);
		 pause_kFlag = true;
		 Music.Play(8);
	 }
	 if (Input.GetKeyEnter(Input.key.M)) {
		 GameState = 2;
		 Music.Play(8);
	 }
	 break;
 }
 case 2: {
	 if (Input.GetKeyEnter(Input.key.O)) {
		 GameState = 0;
		 Music.Play(8);
	 }
	 if (Input.GetKeyEnter(Input.key.P)) {
		 GameState = 1;
		 Music.Play(8);
	 }
	 if (Input.GetKeyDown(Input.key.K)) {
		 Game.FlipScene(new CSTitle(), Flip::FADE_OUT_IN);
		 Music.Play(8);
	 }
	 break;
 }
 default:
	 break;
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
	

	if (count <= TUTRIAL_TIME)tutrialGraph(0, 0);
	

	
	lightGraph();
	
	//Bullet

	

	
	

	
	if (/*Input.GetKeyDown(Input.key.DOWN)*/jDropFlag) {
		jDropGraph(x-25, y-25, vy < 0 || Input.GetKeyDown(Input.key.LEFT));
	}
	else{
		soldierGraph(x-25, y-25, vx < 0 || Input.GetKeyDown(Input.key.LEFT));
	}	
	//map
	if (count - countbuf2 <= INFINITY_TIME&&count%24<=12&&life!=3) {
		dmgGraph(x, y);
	}
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
	/*	DxLib::SetDrawBlendMode(DX_BLENDMODE_INVSRC, 255);*/
		DxLib::SetDrawBlendMode(DX_BLENDMODE_ADD,255);
		levelupGraphFlag = false;
	}
	else {
		levelupGraphFlag = true;
	}
	if (count - countbuf < 60&&playLevel>=1&&count>60)levelupGraph();
	DxLib::SetDrawBright(255, 255, 255);
	DxLib::SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	DxLib::SetFontSize(60);
	DrawFormatString(320+ 2, 4 + 2, BLACK, "%d", score);
	DrawFormatString(620+2, 4+2, BLACK, "%d", highScore);
	
	DrawFormatString(70+2, 4+2, BLACK, "%d", playLevel);
	SetFontSize(FONT_SIZE);
	levelupGraph = "pic/levelup.png";
	DrawFormatString(320,4,GetColor(243,165,48),"%d",score);
	DrawFormatString(620, 4, GetColor(243, 165, 48), "%d",highScore);
	
	DrawFormatString(70, 4, GetColor(243, 165, 48), "%d",playLevel);
	
	for (int i = 0; i != 10; ++i) {


		if (killer.b[i].flag)DrawBox(killer.b[i].x, killer.b[i].y, killer.b[i].x + redLong[i], killer.b[i].y + 100, GetColor(238, 64, 53)
			, true);
		
	}
	
	for (int i = 0; i < 10; i++)
	{
		if(bullet[i].flag)bullet[i].Draw();
	}
	shadowGraph(0, 0);
	if (life >= 1) {
		heartGraph(10, 100);
	}
	if (life >= 2) {
		heartGraph(10, 100 + 80);
	}
	if (life == 3)heartGraph(10, 100 + 160);
	switch (GameState)
	{
	case 1: {
		pauseGraph(0, 0);
		break;
	}
	case 2: {
		sousaGraph(0, 0);
		break;
	}
	default:
		break;
	}
	if (GameState == 1) {
		
		
	}


}



void CSGame::End() {

}