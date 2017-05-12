#include"MCE.h"
#include <sys/stat.h>

suken::MCE::MCE() {
	chip = nullptr;
	width = 0;
	height = 0;
}

suken::MCE::MCE(const char* file){
	{
		struct stat s;
		if (stat(file, &s)) return;
	}
	CData data(file);
	data.ReadAll();
	width = data.GetInt("width");
	height = data.GetInt("height");
	edge = data.GetInt("edge");
	graph[0] = data.GetString("graphA");
	graph[1] = data.GetString("graphB");
	graph[2] = data.GetString("graphC");
	chip = new int[3 * width*height];
	for (int i = 0; i < 3 * width*height; i++) {
		chip[i] = data.GetInt(i);
	}
}

suken::MCE::MCE(const char* file, unsigned int index) {
	
	CData custom(std::string(file) + "/mcepic/custom.mce");
	custom.ReadAll();

	std::string buf = custom.GetString(index).c_str();
	if (buf == "")return;
	buf += ".mce";
	struct stat s;
	if (stat(buf.c_str(), &s)) return;
	
	CData data(buf.c_str());
	data.ReadAll();
	width = data.GetInt("width");
	height = data.GetInt("height");
	edge = data.GetInt("edge");
	graph[0] = data.GetString("graphA");
	graph[1] = data.GetString("graphB");
	graph[2] = data.GetString("graphC");
		chip = new int[3 * width*height];
	for (int i = 0; i < 3 * width*height; i++) {
		chip[i] = data.GetInt(i);
	}
}

suken::MCE::~MCE() {
	delete[] chip;
}

void suken::MCE::Set(const char* file) {
	if (chip != nullptr) {
		this->~MCE();
	}
	{
		struct stat s;
		if (stat(file, &s)) return;
	}
	CData data(file);
	data.ReadAll();
	width = data.GetInt("width");
	height = data.GetInt("height");
	edge = data.GetInt("edge");
	graph[0] = data.GetString("graphA");
	graph[1] = data.GetString("graphB");
	graph[2] = data.GetString("graphC");
	chip = new int[3 * width*height];
	for (int i = 0; i < 3 * width*height; i++) {
		chip[i] = data.GetInt(i);
	}
}

suken::MCE& suken::MCE::operator =(const char* file) {
	if (chip != nullptr) {
		this->~MCE();
	}
	{
		struct stat s;
		if (stat(file, &s)) return *this;
	}
	CData data(file);
	data.ReadAll();
	width = data.GetInt("width");
	height = data.GetInt("height");
	edge = data.GetInt("edge");
	graph[0] = data.GetString("graphA");
	graph[1] = data.GetString("graphB");
	graph[2] = data.GetString("graphC");
	chip = new int[3 * width*height];
	for (int i = 0; i < 3 * width*height; i++) {
		chip[i] = data.GetInt(i);
	}
	return *this;
}

int& suken::MCE::Get(Layer::LayerData layer,int x,int y){
	return chip[Array(layer, x, y)];
}

int suken::MCE::GetWidth() {
	return width;
}

int suken::MCE::GetHeight() {
	return height;
}

int suken::MCE::GetEdge() {
	return edge;
}

std::string suken::MCE::GetGraph(Layer::LayerData layer) {
	return graph[layer];
}

int& suken::MCE::operator()(Layer::LayerData layer, int x, int y) {
	return chip[Array(layer, x, y)];
}

int suken::MCE::Array(char layer, int x, int y) {
//#ifdef DEBUG
//	if (layer >= 3 || x >= width || y >= height) {
//		WarningSK("MCE-警告：数値が大きすぎます。強制終了します");
//		exit(1);
//
//	}
//	else {
//		return layer * width * height + x * height + y;
//	}
//#else
	return layer * width * height + x * height + y;
//#endif
}