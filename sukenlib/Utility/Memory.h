#pragma once

#include <unordered_map>

namespace suken {
	/**
	*	とにかく、セーブデータなどを保存するのに特化した構造体
	*/
	struct Memory {
	public:
		Memory(const char* fileName,unsigned int hashKey = 0);

		int& operator [](unsigned int index) {
			if (index >= numData.size())numData.resize(index + 1, 0);
			return numData[index];
		}

		int& operator [](const char* key) {
			return hashNumData[key];//読み書き出来るように、ない場合は作成
		}

		std::string& operator ()(const char* key) {
			return hashStrData[key];//読み書き出来るように、ない場合は作成
		}

		int GetInt(unsigned int index) {
			if (index >= numData.size())numData.resize(index + 1, 0);
			return numData[index];
		}

		int GetInt(const char* key) {
			auto buf = hashNumData.find(key);
			return buf == hashNumData.end() ? 0 : buf->second;
		}

		std::string GetStr(const char* key) {
			auto buf = hashStrData.find(key);
			return buf == hashStrData.end() ? "" : buf->second;
		}

		void Set(unsigned int index, int value) {
			if (index >= numData.size())numData.resize(index + 1, 0);
			numData[index] = value;
		}

		void Set(const char* key, int value) {
			hashNumData[key] = value;
		}

		void Set(const char* key, std::string value) {
			hashStrData[key] = value;
		}

		bool Read();

		bool Write();

		void Clear();

		bool IsChanged() {
			return (flag & 0x1) != 0;
		}

		bool IsFailed() {
			return (flag & 0x2) != 0;
		}

	private:
		unsigned char flag;// 0x1:isChanged 0x2:isFailed
		unsigned int hashKey;
		std::string fileName;
		std::vector<int> numData;
		std::unordered_map<std::string, int> hashNumData;
		std::unordered_map<std::string, std::string> hashStrData;

		int GetHash();
		std::string GetNormalize(std::string str);
		void Normalize(std::string &str);
	};

	/**
	*	とにかく、外部からまとまったデータを読み込むのに特化した構造体
	*/
	struct CSV {
		struct Data {
			operator std::string() { return str; }
			operator unsigned char() { return (unsigned char)std::atoi(str.c_str()); }
			operator int() { return std::atoi(str.c_str()); }
			operator unsigned int() { return (unsigned int)std::atoi(str.c_str()); }
			operator float() { return (float)std::atof(str.c_str()); }
			operator double() { return std::atof(str.c_str()); }
			Data(const char* str):str(str){}
		private:
			std::string str;
			friend CSV;
		};

		CSV(const char* fileName) {
			isFailed = !Read(fileName);
		}

		CSV& operator =(const char* fileName) {
			isFailed = !Read(fileName);
			return *this;
		}

		std::vector<Data>& operator [](unsigned int index) {
			return value[index];
		}

		int GetLineNum() {
			return value.size();
		}

		int GetTermNum() {
			return value.size() == 0 ? 0 : value[0].size();
		}

		bool IsFailed() {
			return isFailed;
		}

	private:
		std::vector<std::vector<Data>> value;
		bool isFailed;

		bool Read(const char* fileName);
	};
	/* HowToUse
	CSV csv = "pic/CSV.csv";

	struct {
		int A;
		float B;
		double C;
		std::string D;
		unsigned int E;
	}data[9];

	if (!csv.IsFailed()) {
		for (int i = 0; i < 9; ++i) {
			data[i].A = csv[i][0];
			data[i].B = csv[i][1];
			data[i].C = csv[i][2];
			data[i].D = csv[i][3];
			data[i].E = csv[i][4];
		}
	}
	*/
}