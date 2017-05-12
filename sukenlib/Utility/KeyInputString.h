#pragma once
#include"../Manager.h"
#include <DxLib.h>
#include <string>

namespace suken {

	class CKeyInput {
	public:
		CKeyInput();

		~CKeyInput();

		void Draw(int x, int y, bool activeOnly = false);

		void Active();

		int GetWidth();

		bool GetActive();

		bool IsEscaped();

		virtual void SetString();

		void SetFont(const char* font, int thick = 1, bool ItalicFlag = false, int fontType = -1, int edgeSize = -1);

		static void SetColor(unsigned int color, unsigned int edgeColor = 0, unsigned int backColor = 0xFFFFFF, unsigned int backEdgeColor = 0);

		static bool CheckAnyActive();
	protected:
		std::string str;
		int size;
		int width, height;
		int font;
		int num;
		bool fActive;
		bool isEscaped;

		static bool fActiveElse;
		static unsigned int color, edgeColor, backColor, backEdgeColor;

		virtual void KeyInput();
		void Add(const char* c);
	};

	class CKeyInputNum : public CKeyInput {
	public:
		CKeyInputNum();
		CKeyInputNum(int* link, char size, int height, const char* font = nullptr);

		void SetString();

	private:
		int* link;

		void KeyInput();
	};

	class CKeyInputNumF : public CKeyInput {
	public:
		CKeyInputNumF();
		CKeyInputNumF(double* link, char size, int height, const char* font = nullptr);

		void SetString();

	private:
		double* link;

		void KeyInput();
	};

	class CKeyInputString : public CKeyInput {
	public:
		CKeyInputString();
		CKeyInputString(std::string* link, char size, int height, const char* font = nullptr);

		void SetString();

	private:
		std::string* link;

		void KeyInput();
	};
}