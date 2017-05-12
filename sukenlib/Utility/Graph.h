#pragma once

/**
*	@file	Graph.h
*	@brief	なぜこんな便利なものが今まで存在しなかったのか。便利な構造体 Graph と Anim 、LoadDivGraph関数のアレンジ　を追加します
*	@author	Photon
*/

#include "../Manager.h"

namespace suken {
	/**
	*	@brief　画像の扱いがとても楽になる、数研部員の強い味方です　内部構造を理解する必要はありません　DrawGraph()の引数に使えるし、LoadGraph()を代入することもできます
	*/
	struct Graph {
	public:
		/**
		*	@brief　既定のコンストラクタ
		*/
		Graph();

		/**
		*	@brief　コンストラクタ
		*/
		Graph(const int& handle);

		/**
		*	@brief　コンストラクタ
		*/
		Graph(const char* file);

		/**
		*	@brief　コピーコンストラクタ
		*/
		Graph(const Graph& obj);

		/**
		*	@brief　代入演算子
		*/
		Graph& operator=(const Graph& obj);

		/**
		*	@brief　代入演算子
		*/
		Graph& operator=(const char* file);

		/**
		*	@brief　DXライブラリの関数の引数に入れることもできます
		*/
		operator int()const;

		/**
		*	@brief　デストラクタ
		*/
		~Graph();

		void Set(const int& handle);

		void Set(const char* file);

		Graph& operator=(const int& handle);

		/**
		*	@brief　描画　位置は0,0
		*/
		void operator ()()const;

		/**
		*	@brief　描画
		*/
		void operator ()(int x, int y, bool turnFlag = false)const;
		/**
		*	@brief　描画
		*/
		void operator ()(Vector2D v, bool turnFlag = false)const;

		/**
		*	@brief　描画　位置は0,0
		*/
		void Draw()const;

		/**
		*	@brief　描画
		*/
		void Draw(int x,int y, bool turnFlag = false)const;
		/**
		*	@brief　描画
		*/
		void Draw(Vector2D v, bool turnFlag = false)const;

		/**
		*	@brief　描画　回転角度指定
		*/
		void DrawRota(int x, int y,double ExtRate, double angle, bool turnFlag = false)const;
		/**
		*	@brief　描画　回転角度指定
		*/
		void DrawRota(Vector2D v, double ExtRate, double angle, bool turnFlag = false)const;

		/**
		*	@brief　描画　回転角度指定
		*/
		void DrawRota2(int x, int y,int cx,int cy, double ExtRate, double angle, bool turnFlag = false)const;
		/**
		*	@brief　描画　回転角度指定
		*/
		void DrawRota2(Vector2D v, Vector2D center, double angle, double ExtRate, bool turnFlag = false)const;

		/**
		*	@brief　描画　回転角度指定
		*/
		void DrawRota3(int x, int y, int cx, int cy, double ExtRateX, double ExtRateY, double angle, bool turnFlag = false)const;
		/**
		*	@brief　描画　回転角度指定
		*/
		void DrawRota3(Vector2D v, Vector2D center, double angle, Vector2D ExtRate, bool turnFlag = false)const;

		/**
		*	@brief　描画　2点の座標指定
		*/
		void DrawExtend(int x1, int y1, int x2, int y2)const;
		/**
		*	@brief　描画　2点の座標指定
		*/
		void DrawExtend(Vector2D v1, Vector2D v2)const;

		/**
		*	@brief　描画　4点の座標指定
		*/
		void DrawModi(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)const;
		/**
		*	@brief　描画　4点の座標指定
		*/
		void DrawModi(Vector2D v1, Vector2D v2, Vector2D v3, Vector2D v4)const;

		/**
		*	@brief　幅、高さをペアで返す
		*/
		std::pair<int, int> GetSize()const;

	private:
		int handle;
		unsigned char* cnt;

		void AddRef();
		void Release();
	};

	/**
	*	@brief　もう数研部員はアニメーションカウンタを作る必要はないのです　LoadDivGraph()を代入して、変数名に（）をつけるだけで勝手にアニメーションするのです
	*/
	struct Anim {
	public:
		/**
		*	@brief　既定のコンストラクタ
		*/
		Anim();

		/**
		*	@brief　コンストラクタ　設定する
		*/
		Anim(GraphVec graph, unsigned char flipTime=10);

		/**
		*	@brief　設定
		*/
		void Set(GraphVec graph, unsigned char flipTime = 10);

		/**
		*	@brief　画像のvectorをを返す
		*/
		GraphVec& GetVec();

		/**
		*	@brief　切り替え速度を返す
		*/
		const char GetFlipTime();

		/**
		*	@brief　画像を入れるだけ　切り替え速度はデフォルト
		*/
		Anim& operator =(GraphVec& vec);

		/**
		*	@brief　描画
		*/
		void operator ()(int x, int y, bool isTurn = false, bool isPlusCount = true);

		/**
		*	@brief　描画
		*/
		void operator ()(Vector2D vec, bool isTurn = false, bool isPlusCount = true);

		/**
		*	@brief　描画
		*/
		void Draw(int x, int y, bool turnFlag = false, bool isPlusCount = true);
		/**
		*	@brief　描画
		*/
		void Draw(Vector2D v, bool turnFlag = false, bool isPlusCount = true);

		/**
		*	@brief　描画　回転角度指定
		*/
		void DrawRota(int x, int y, double ExtRate, double angle, bool turnFlag = false, bool isPlusCount = true);
		/**
		*	@brief　描画　回転角度指定
		*/
		void DrawRota(Vector2D v, double ExtRate, double angle, bool turnFlag = false, bool isPlusCount = true);

		/**
		*	@brief　描画　回転角度指定
		*/
		void DrawRota2(int x, int y, int cx, int cy, double ExtRate, double angle, bool turnFlag = false, bool isPlusCount = true);
		/**
		*	@brief　描画　回転角度指定
		*/
		void DrawRota2(Vector2D v, Vector2D center, double angle, double ExtRate, bool turnFlag = false, bool isPlusCount = true);

		/**
		*	@brief　描画　回転角度指定
		*/
		void DrawRota3(int x, int y, int cx, int cy, double ExtRateX, double ExtRateY, double angle, bool turnFlag = false, bool isPlusCount = true);
		/**
		*	@brief　描画　回転角度指定
		*/
		void DrawRota3(Vector2D v, Vector2D center, double angle, Vector2D ExtRate, bool turnFlag = false, bool isPlusCount = true);

		/**
		*	@brief　描画　2点の座標指定
		*/
		void DrawExtend(int x1, int y1, int x2, int y2, bool isPlusCount = true);
		/**
		*	@brief　描画　2点の座標指定
		*/
		void DrawExtend(Vector2D v1, Vector2D v2, bool isPlusCount = true);

		/**
		*	@brief　描画　4点の座標指定
		*/
		void DrawModi(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, bool isPlusCount = true);
		/**
		*	@brief　描画　4点の座標指定
		*/
		void DrawModi(Vector2D v1, Vector2D v2, Vector2D v3, Vector2D v4, bool isPlusCount = true);

		/**
		*	@brief　アニメーションカウントを増やします
		*/
		void PlusCount();
	private:
		GraphVec graph;
		unsigned int cnt;
		unsigned char flipTime;
	};

	///** //不具合があるのでコメントアウト
	//*	@brief　画像を分割読み込みするのに、面倒な設定はいりません　要素数はvector.size()で確認してください保証はしません
	//*/
	//GraphVec LoadDivGraph(const char* file,int xSize,int ySize);

	///**
	//*	@brief　引数にとったベクターに、ロードした画像をpush_backしてくれます　要素数はvector.size()で確認してください保証はしません
	//*/
	//void LoadDivGraph(const char* file, int xSize, int ySize, GraphVec& vector);

	///**
	//*	@brief　ベクターを使いたくない頑固な人のために、Graphの配列に入れてくれるバージョンも作りました
	//*/
	//void LoadDivGraph(const char* file, int xSize, int ySize, Graph* handleBuf);

	/**
	*	@brief　画像を分割読み込みするのに、面倒な設定はいりません　要素数はvector.size()で確認してください保証はしません
	*/
	GraphVec LoadDivGraph(const char* file, int allNum, int xNum, int yNum,int xSize,int ySize);

	/**
	*	@brief　引数にとったベクターに、ロードした画像をpush_backしてくれます　要素数はvector.size()で確認してください保証はしません
	*/
	void LoadDivGraph(const char* file, int allNum, int xNum, int yNum, int xSize, int ySize, GraphVec& vector);

	/**
	*	@brief　ベクターを使いたくない頑固な人のために、Graphの配列に入れてくれるバージョンも作りました
	*/
	void LoadDivGraph(const char* file, int allNum, int xNum, int yNum, int xSize, int ySize, Graph* handleBuf);
}