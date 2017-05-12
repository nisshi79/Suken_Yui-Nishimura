#include "Memory.h"

#include <fstream>
#include <string>
#include <sys/stat.h>

suken::Memory::Memory(const char* fileName, unsigned int hashKey):flag(0),fileName(fileName),hashKey(hashKey*hashKey) {
	if (!Read())flag |= 0x2;
}

bool suken::Memory::Read() {
	Clear();
	{
		struct stat s;
		if (stat(fileName.c_str(), &s)) return Write();
	}
	std::ifstream ifs(fileName);
	if (ifs.fail()) return false;
	std::string key, val;
	flag &= ~0x1;
	
	unsigned int fileHash=0;

	try {
		std::getline(ifs, key);
		if (ifs.eof())throw true;
		std::getline(ifs, val);
		if (key.size() == 0) throw true;
		if (val.size() == 0) throw true;
		fileHash = std::atoi(key.c_str());
		numData.reserve(std::atoi(val.c_str()));
	}
	catch (bool isReturn) {
		flag |= 0x1;
		if (isReturn)return false;
	}

	while (!ifs.eof()) {
		std::getline(ifs, key);
		if (ifs.eof())break;
		std::getline(ifs, val);
		if (key.size() == 0) continue;
		if (val.size() == 0) continue;
		if (key.c_str()[0] == '#') {
			if (val.c_str()[0] == '#') {
				Set(key.c_str()+1, val.substr(1, val.size() - 1));
			}
			else {
				Set(key.c_str()+1, std::atoi(val.c_str()));
			}
		}
		else {
			Set(std::atoi(key.c_str()), std::atoi(val.c_str()));
		}
	}

	if (hashKey != 0 && fileHash != GetHash()) {
		flag |= 0x1;
	}
	return true;
}

bool suken::Memory::Write() {
	for (auto i = hashStrData.begin(); i != hashStrData.end(); ++i) {
		Normalize(i->second);
	}

	std::ofstream ofs(fileName, std::ios::trunc);
	if (ofs.fail()) return false;

	if (hashKey != 0) {
		ofs << GetHash() << '\n'
			<< numData.size() << '\n';
	}
	else {
		ofs << 0 << '\n'
			<< numData.size() << '\n';
	}

	for (int i = 0; i < numData.size(); ++i) {
		ofs << i << '\n'
			<< numData[i] << '\n';
	}
	for (auto i = hashNumData.begin(); i != hashNumData.end(); ++i) {
		ofs << '#' << GetNormalize(i->first)
			<< '\n' << i->second << '\n';
	}
	for (auto i = hashStrData.begin(); i != hashStrData.end(); ++i) {
		ofs << '#' << GetNormalize(i->first)
			<< '\n' << '#' << GetNormalize(i->second) << '\n';
	}

	return true;
}

void suken::Memory::Clear() {
	numData.clear();
	hashNumData.clear();
	hashStrData.clear();
}

int suken::Memory::GetHash() {
	int hash = hashKey;
	for (auto i = numData.begin(); i != numData.end(); ++i) {
		hash += *i % 7777;
		hash %= 7777;
	}
	for (auto i = hashNumData.begin(); i != hashNumData.end(); ++i) {
		hash += i->second % 7777;
		hash %= 7777;
	}
	for (auto i = hashStrData.begin(); i != hashStrData.end(); ++i) {
		hash += i->second.back() % 77;
		hash %= 7777;
	}
	return hash*7777;
}

std::string suken::Memory::GetNormalize(std::string str) {
	for (auto found = str.find('\n');
		found != std::string::npos;
		found = str.find('\n', found + 1)) {
		str.replace(found, 1, " ");
	}
	return str;
}

void suken::Memory::Normalize(std::string &str) {
	for (auto found = str.find('\n');
		found != std::string::npos;
		found = str.find('\n', found + 1)) {
		str.replace(found, 1, " ");
	}
}

bool suken::CSV::Read(const char* fileName) {
	{
		struct stat s;
		if (stat(fileName, &s)) return false;
	}
	std::ifstream ifs(fileName);
	if (ifs.fail()) return false;
	std::string str;
	int buf = 0,termNum=1;

	std::getline(ifs, str);
	if (ifs.eof())return false;
	
	for (auto i = str.begin(); i != str.end(); ++i) {
		if (*i == ',') {
			++termNum;
		}
	}
	int line = 0,term = 0;
	while (!ifs.eof()) {
		term = 0;
		value.push_back(std::vector<Data>(termNum,""));
		std::getline(ifs, str);
		for (auto i = str.begin(); (term < termNum) && i != str.end(); ++i) {
			if (*i != ',') {
				value[line][term].str += *i;
			}
			else {
				++term;
			}
		}
		++line;
	}
	return true;
}