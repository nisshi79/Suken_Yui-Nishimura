#include "Graph.h"
#include "Primitive.h"

suken::Graph::Graph() {
	handle = NULL;
	cnt = nullptr;
}

suken::Graph::Graph(const int& handle) {
	if (handle == -1 || handle == 0) {
		this->handle = NULL;
		cnt = nullptr;
		return;
	}
	this->handle = handle;
	cnt = new unsigned char(0);
	AddRef();
}

suken::Graph::Graph(const char* file) {
	if (file == "") {
		handle = NULL;
		cnt = nullptr;
		return;
	}
	this->handle = LoadGraph(file);
	cnt = new unsigned char(0);
	AddRef();
}

suken::Graph::Graph(const Graph& obj) {
	if (this == &obj || obj.handle == -1 || obj.handle == 0) {
		handle = NULL;
		cnt = nullptr;
		return ;
	}
	handle = obj.handle;
	cnt = obj.cnt;
	AddRef();
}

suken::Graph& suken::Graph::operator=(const Graph& obj) {
	if (this == &obj || obj.handle == -1 || obj.handle == 0) {
		return *this;
	}
	Release();
	handle = obj.handle;
	cnt = obj.cnt;
	AddRef();
	return *this;
}

suken::Graph::operator int()const {
	return handle;
}

suken::Graph::~Graph() {
	Release();
}

void suken::Graph::Set(const int& handle) {
	if (*this == handle) {
		return;
	}
	if (handle == -1 || handle == 0) {
		this->handle = NULL;
		cnt = nullptr;
		return;
	}
	Release();
	this->handle = handle;
	cnt = new unsigned char(0);
	AddRef();
}

void suken::Graph::Set(const char* file) {
	Release();
	if (file == "") {
		handle = NULL;
		cnt = nullptr;
		return;
	}
	handle = LoadGraph(file);
	cnt = new unsigned char(0);
	AddRef();
}

suken::Graph& suken::Graph::operator=(const int& handle) {
	Release();
	if (handle == -1 || handle == 0) {
		this->handle = NULL;
		cnt = nullptr;
		return *this;
	}
	this->handle = handle;
	cnt = new unsigned char(0);
	AddRef();
	return *this;
}

suken::Graph& suken::Graph::operator=(const char* file) {
	Release();
	if (file == "") {
		handle = NULL;
		cnt = nullptr;
		return *this;
	}
	handle = LoadGraph(file);
	cnt = new unsigned char(0);
	AddRef();
	return *this;
}

void suken::Graph::operator ()()const {
	DrawGraph(0, 0, handle, true);
}

void suken::Graph::operator ()(int x, int y, bool turnFlag)const {
	if (!turnFlag) {
		DrawGraph(x, y, handle, true);
	}
	else {
		DrawTurnGraph(x, y, handle, true);
	}
}
void suken::Graph::operator ()(Vector2D v, bool turnFlag)const {
	if (!turnFlag) {
		DrawGraph((int)v.x, (int)v.y, handle, true);
	}
	else {
		DrawTurnGraph((int)v.x, (int)v.y, handle, true);
	}
}

void suken::Graph::Draw()const {
	DrawGraph(0, 0, handle, true);
}

void suken::Graph::Draw(int x, int y, bool turnFlag)const {
	if (!turnFlag) {
		DrawGraph(x, y, handle, true);
	}
	else {
		DrawTurnGraph(x, y, handle, true);
	}
}
void suken::Graph::Draw(Vector2D v, bool turnFlag)const {
	if (!turnFlag) {
		DrawGraph((int)v.x, (int)v.y, handle, true);
	}
	else {
		DrawTurnGraph((int)v.x, (int)v.y, handle, true);
	}
}

void suken::Graph::DrawRota(int x, int y, double ExtRate, double angle, bool turnFlag)const {
	DrawRotaGraph(x, y, ExtRate, angle, handle, true, turnFlag);
}
void suken::Graph::DrawRota(Vector2D v, double ExtRate, double angle, bool turnFlag)const {
	DrawRotaGraph((int)v.x, (int)v.y, ExtRate, angle, handle, true, turnFlag);
}

void suken::Graph::DrawRota2(int x, int y, int cx, int cy, double ExtRate, double angle, bool turnFlag)const {
	DrawRotaGraph2(x, y,cx,cy, ExtRate, angle, handle, true, turnFlag);
}
void suken::Graph::DrawRota2(Vector2D v,Vector2D center, double angle, double ExtRate, bool turnFlag)const {
	DrawRotaGraph2((int)v.x, (int)v.y, (int)center.x, (int)center.y, ExtRate, angle, handle, true, turnFlag);
}

void suken::Graph::DrawRota3(int x, int y, int cx, int cy, double ExtRateX, double ExtRateY, double angle, bool turnFlag)const {
	DrawRotaGraph3(x, y, cx, cy, ExtRateX,ExtRateY, angle, handle, true, turnFlag);
}
void suken::Graph::DrawRota3(Vector2D v, Vector2D center, double angle, Vector2D ExtRate, bool turnFlag)const {
	DrawRotaGraph3((int)v.x, (int)v.y, (int)center.x, (int)center.y, (double)ExtRate.x, (double)ExtRate.y, angle, handle, true, turnFlag);
}

void suken::Graph::DrawExtend(int x1, int y1, int x2, int y2)const {
	DrawExtendGraph(x1, y1, x2, y2, handle, true);
}
void suken::Graph::DrawExtend(Vector2D v1, Vector2D v2)const {
	DrawExtendGraph((int)v1.x, (int)v1.y, (int)v2.x, (int)v2.y, handle, true);
}

void suken::Graph::DrawModi(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)const {
	DrawModiGraph(x1, y1, x2, y2, x3, y3, x4, y4, handle, true);
}
void suken::Graph::DrawModi(Vector2D v1, Vector2D v2, Vector2D v3, Vector2D v4)const {
	DrawModiGraph((int)v1.x, (int)v1.y, (int)v2.x, (int)v2.y, (int)v3.x, (int)v3.y, (int)v4.x, (int)v4.y, handle, true);
}

std::pair<int, int> suken::Graph::GetSize()const {
	std::pair<int, int> buf;
	DxLib::GetGraphSize(handle, &buf.first, &buf.second);
	return buf;
}

void suken::Graph::AddRef() {
	++(*cnt);
}

void suken::Graph::Release() {
	if (cnt != nullptr) {
		--(*cnt);
		if (*cnt == 0) {
			delete cnt;
			cnt = nullptr;
			DeleteGraph(handle);
			handle = 0;
		}
	}
}

suken::Anim::Anim() {
	cnt = 0;
	flipTime = 10;
}

suken::Anim::Anim(GraphVec graph, unsigned char flipTime) {
	this->graph = graph;
	this->flipTime = flipTime < 1 ? 1 : flipTime;
	cnt = 0;
}

suken::Anim& suken::Anim::operator =(GraphVec& vec) {
	this->graph = vec;
	cnt = 0;
	return *this;
}

void suken::Anim::Set(GraphVec graph, unsigned char flipTime) {
	this->graph = graph;
	this->flipTime = flipTime < 1 ? 1 : flipTime;
	cnt = 0;
}

suken::GraphVec& suken::Anim::GetVec() {
	return graph;
}

const char suken::Anim::GetFlipTime() {
	return flipTime;
}

void suken::Anim::operator ()(int x, int y, bool isTurn, bool isPlusCount) {
	graph[(cnt / flipTime) % graph.size()].Draw(x, y);
	cnt += isPlusCount;
}

void suken::Anim::operator ()(Vector2D vec, bool isTurn, bool isPlusCount) {
	graph[(cnt / flipTime) % graph.size()].Draw(vec,isTurn);
	cnt += isPlusCount;
}

void suken::Anim::Draw(int x, int y, bool isTurn, bool isPlusCount) {
	graph[(cnt / flipTime) % graph.size()].Draw(x, y);
	cnt += isPlusCount;
}

void suken::Anim::Draw(Vector2D vec, bool isTurn, bool isPlusCount) {
	graph[(cnt / flipTime) % graph.size()].Draw(vec, isTurn);
	cnt += isPlusCount;
}

void suken::Anim::DrawRota(int x, int y, double ExtRate, double angle, bool turnFlag, bool isPlusCount) {
	DrawRotaGraph(x, y, ExtRate, angle, graph[(cnt / flipTime) % graph.size()], true, turnFlag);
	cnt += isPlusCount;
}
void suken::Anim::DrawRota(Vector2D v, double ExtRate, double angle, bool turnFlag, bool isPlusCount) {
	DrawRotaGraph((int)v.x, (int)v.y, ExtRate, angle, graph[(cnt / flipTime) % graph.size()], true, turnFlag);
	cnt += isPlusCount;
}

void suken::Anim::DrawRota2(int x, int y, int cx, int cy, double ExtRate, double angle, bool turnFlag, bool isPlusCount) {
	DrawRotaGraph2(x, y, cx, cy, ExtRate, angle, graph[(cnt / flipTime) % graph.size()], true, turnFlag);
	cnt += isPlusCount;
}
void suken::Anim::DrawRota2(Vector2D v, Vector2D center, double angle, double ExtRate, bool turnFlag, bool isPlusCount) {
	DrawRotaGraph2((int)v.x, (int)v.y, (int)center.x, (int)center.y, ExtRate, angle, graph[(cnt / flipTime) % graph.size()], true, turnFlag);
	cnt += isPlusCount;
}

void suken::Anim::DrawRota3(int x, int y, int cx, int cy, double ExtRateX, double ExtRateY, double angle, bool turnFlag, bool isPlusCount) {
	DrawRotaGraph3(x, y, cx, cy, ExtRateX, ExtRateY, angle, graph[(cnt / flipTime) % graph.size()], true, turnFlag);
	cnt += isPlusCount;
}
void suken::Anim::DrawRota3(Vector2D v, Vector2D center, double angle, Vector2D ExtRate, bool turnFlag, bool isPlusCount) {
	DrawRotaGraph3((int)v.x, (int)v.y, (int)center.x, (int)center.y, (double)ExtRate.x, (double)ExtRate.y, angle, graph[(cnt / flipTime) % graph.size()], true, turnFlag);
	cnt += isPlusCount;
}

void suken::Anim::DrawExtend(int x1, int y1, int x2, int y2, bool isPlusCount) {
	DrawExtendGraph(x1, y1, x2, y2, graph[(cnt / flipTime) % graph.size()], true);
	cnt += isPlusCount;
}
void suken::Anim::DrawExtend(Vector2D v1, Vector2D v2, bool isPlusCount) {
	DrawExtendGraph((int)v1.x, (int)v1.y, (int)v2.x, (int)v2.y, graph[(cnt / flipTime) % graph.size()], true);
	cnt += isPlusCount;
}

void suken::Anim::DrawModi(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, bool isPlusCount) {
	DrawModiGraph(x1, y1, x2, y2, x3, y3, x4, y4, graph[(cnt / flipTime) % graph.size()], true);
	cnt += isPlusCount;
}
void suken::Anim::DrawModi(Vector2D v1, Vector2D v2, Vector2D v3, Vector2D v4, bool isPlusCount) {
	DrawModiGraph((int)v1.x, (int)v1.y, (int)v2.x, (int)v2.y, (int)v3.x, (int)v3.y, (int)v4.x, (int)v4.y, graph[(cnt / flipTime) % graph.size()], true);
	cnt += isPlusCount;
}

void suken::Anim::PlusCount() {
	++cnt;
}

//std::vector<suken::Graph> suken::LoadDivGraph(const char* file,int xSize, int ySize) {
//	int x, y;
//	int buff = LoadGraph(file);
//	DxLib::GetGraphSize(buff,&x, &y);
//	x = x / xSize;
//	y = y / ySize;
//	int num = x*y;
//	int *buf = new int[num];
//	DxLib::LoadDivGraph(file, num, x, y, xSize, ySize, buf);
//	return GraphVec(buf, buf + num);
//}
//
//void suken::LoadDivGraph(const char* file,int xSize, int ySize, GraphVec& vector) {
//	int x, y;
//	int buff = LoadGraph(file);
//	DxLib::GetGraphSize(buff, &x, &y);
//	x = x / xSize;
//	y = y / ySize;
//	int num = x*y;
//	int *buf = new int[num];
//	DxLib::LoadDivGraph(file, num, x, y, xSize, ySize, buf); 
//	vector.reserve(num+vector.size());
//	for (int i = 0; i < num; ++i) {
//		vector.push_back(Graph(buf[i]));
//	}
//}
//
//void suken::LoadDivGraph(const char* file, int xSize, int ySize, Graph* handleBuf) {
//	int x, y;
//	int buff = LoadGraph(file);
//	DxLib::GetGraphSize(buff, &x, &y);
//	x = x / xSize;
//	y = y / ySize;
//	int num = x*y;
//	int *buf = new int[num];
//	DxLib::LoadDivGraph(file, num, x, y, xSize, ySize, buf);
//	for (int i = 0; i < num; ++i) {
//		handleBuf[i].Set(buf[i]);
//	}
//}

std::vector<suken::Graph> suken::LoadDivGraph(const char* file, int allNum, int xNum, int yNum, int xSize, int ySize) {
	int* buf = new int[allNum];
	DxLib::LoadDivGraph(file, allNum, xNum, yNum, xSize, ySize, buf);
	std::vector<Graph> vector;
	vector.reserve(allNum);
	for (int i = 0; i < allNum; ++i) {
		vector.push_back(Graph(buf[i]));
	}
	return vector;
}

void suken::LoadDivGraph(const char* file, int allNum, int xNum, int yNum, int xSize, int ySize, GraphVec& vector) {
	int* buf = new int[allNum];
	DxLib::LoadDivGraph(file, allNum, xNum, yNum, xSize, ySize, buf);
	vector.reserve(allNum + vector.size());
	for (int i = 0; i < allNum; ++i) {
		vector.push_back(Graph(buf[i]));
	}
}

void suken::LoadDivGraph(const char* file, int allNum, int xNum, int yNum, int xSize, int ySize, Graph* handleBuf) {
	int* buf = new int[allNum];
	DxLib::LoadDivGraph(file, allNum, xNum, yNum, xSize, ySize, buf);
	for (int i = 0; i < allNum; ++i) {
		handleBuf[i] = buf[i];
	}
}