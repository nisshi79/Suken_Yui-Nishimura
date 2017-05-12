#pragma once

/**
*	@file	System.h
*	@brief	初期設定や、システム的なことをやるよ
*	@author Photon
*/

#include "../Manager.h"
#include "../GameEngine/Game.h"
#include "../DebugWindow/Debug.h"
#include "../Utility/Graph.h"
#include <DxLib.h>
#include <string>

namespace suken {
	/**
	*	@brief　初期設定用構造体だよ　WinMainで使ってるよ
	*/
	struct SystemSetting {
		unsigned char WindowSyle;//!>	ウインドウスタイル　1：普通　２：タイトルバーなし、縁あり　３：タイトルバー、縁なし
		bool isWindow;
		std::string WindowText;//!>	左上のタイトル
		unsigned char iconID;//!>アイコンのID　基本触らない
		int windowWidth;//!>　ウインドウ幅
		int windowHeight;//!>　ウインドウ高さ
		float targetFps;//!>　目標fps
		float startLoadingMinTime;//!>　最初のロード時間
		std::string startGraphPath;//!>　最初の画面
		std::string loadingGraphPath;//!>　ローディング中のアニメーション画像
		int loadingSizeX;//!>　ローディング画像の横幅
		int loadingSizeY;//!>　ローディング画像の高さ
		unsigned char loadingFlipTime;//!>　ローディング画像の表示切替時間
		int loadingPosX;//!>　ローディング画像の表示位置
		int loadingPosY;//!>　ローディング画像の表示位置
		bool isUseLoading;//!>　ローディングアニメーションを使うかどうか
		bool isLaunchar;//!>　自身がランチャーかどうか

		int debugWindowWidth;
		int debugWindowHeight;

		CScene* scene;
		Flip flip;
		bool isTransiton;

		/**
		*	@brief　ウインドウサイズ設定
		*	@param	(width)　横幅
		*	@param	(height)　高さ
		*/
		void SetWindowSize(int width,int hegiht);

		/**
		*	@brief　ローディング画像設定。使わないときは必ず書く
		*/
		void SetLoadingGraph();

		/**
		*	@brief　ローディング画像設定
		*	@param	(filrName)　画像ファイルの位置　
		*	@param	(sizeX)　画像分割後の横幅
		*	@param	(sizeY)　画像分割後の高さ
		*	@param	(flipTime)　アニメーションの切り替え時間
		*	@param	(positionX)　画像の表示座標　　
		*	@param	(positionY)　画像の表示座標　　
		*/
		void SetLoadingGraph(const char* fileName, int sizeX, int sizeY,int flipTime=10, int positionX = 0, int positionY = 0);

		/**
		*	@brief　初期設定です
		*/
		void InitScene(CScene* scene);

		/**
		*	@brief　初期設定です　初期画面からトランシジョンします
		*/
		void InitScene(CScene* scene, const char* ruleGraph, unsigned char speed = 10, unsigned char gradate = 1);

		/**
		*	@brief　初期設定です　初期画面からトランシジョンします
		*/
		void InitScene(CScene* scene, const char* ruleGraph, const char* ruleGraph2, unsigned char speed = 10, unsigned char gradate = 1);

		/**
		*	@brief　初期設定です　初期画面からトランシジョンします
		*/
		void InitScene(CScene* scene, Flip::Type flipType, unsigned char speed = 10);
	};

	/**
	*	@brief　システムクラスだよ　System.～　で出てくる関数は、使ってくれて構わないよ　Escape()は自己責任です
	*/
	class CSystem {
	public:
		/**
		*	@brief　コンストラクタ
		*/
		CSystem();

		/**
		*	@brief　デストラクタ
		*/
		~CSystem();

		/**
		*	@brief　実行すると強制終了できます
		*/
		void Escape();

		/**
		*	@brief　ウインドウ幅取得
		*/
		int GetWindowX()const;

		/**
		*	@brief　ウインドウ高さ取得
		*/
		int GetWindowY()const;

		/**　
		*	@brief　ディスプレイ幅取得
		*/
		int GetDispX()const;

		/**
		*	@brief　ディスプレイ高さ取得
		*/
		int GetDispY()const;

		/**
		*	@brief　exeが始まってからのフレーム数取得
		*/
		int GetFrame()const;

		/**
		*	@brief　現フレームの始まった時間取得（マイクロ秒）
		*/
		int GetNow()const;

		/**
		*	@brief　フレームレート取得
		*/
		float GetFps()const;

		/**
		*	@brief　次にシーン切り替えするときの最低ロード時間を設定できます
		*/
		void SetNextLoadTime(float nextLoadingMinTime);

		/**
		*	@brief　シーン切り替えアニメーションを変更できます
		*/
		void SetDoadAnimation(Anim anim,int positionX,int positionY);

		HINSTANCE GetHInstance();

		int GetNCmdShow();

	private:
		void Awake(SystemSetting setting);

		void Start(HINSTANCE hInstance, HINSTANCE hPreInst, LPSTR lpszCmdLine, int nCmdShow);

		void Update();

		void Loop();

		void GoLoading();

		void EndLoad();

		bool GetIsEscape();

		void Wait();

		void End();

		struct {
			int now;
			int windowWidth;
			int windowHeight;
			int displayX;
			int displayY;
			float fps;
			float targetRate;
			int startTime;
			int refreshRate;
			unsigned char cnt;//countの事。使用率ランキング上位に入るので、三字略変数に殿堂入り
			int frame;
			float loadingMinTime;
			float nextLoadingMinTime;
			unsigned char flag;
		}m;

		HINSTANCE hInstance;
		HINSTANCE hPreInst;
		LPSTR lpszCmdLine;
		int nCmdShow;

		enum {
			isEscape  =		1 << 0,
			isUseLoading =	1 << 1,
			isLoading =		1 << 2,
			isLaunchar =	1 << 3
		};
#ifdef DEBUG
		CDebug debug;
#endif
		friend int Main(HINSTANCE hInstance, HINSTANCE hPreInst, LPSTR lpszCmdLine, int nCmdShow);

		friend class CScene;
	};
}