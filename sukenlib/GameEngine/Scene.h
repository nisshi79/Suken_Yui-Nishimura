#pragma once

/**
*	@file	Scene.h
*	@brief	色々詰め込みすぎた　反省はしている　後悔はしていない　cppは半分以上シーン切り替え効果だよ
*	@author	Photon
*/

#include "../Utility/Graph.h"
#include "Object\Transform.h"
#include "Object\Object.h"
#include "../Utility/UniquePtr.h"
#include "../Utility/safe_vector.h"
#include <string>
#include <list>
#include <queue>
#include <map>
#include <typeinfo>
#include <functional>

namespace suken {
	/**
	*	@brief　内部構造体　気にしなくていいよ
	*/
	struct DrawMode {
		unsigned char blendMode, param;
		unsigned char red, green, blue;
		DrawMode(unsigned char blendMode, unsigned char param, unsigned char red, unsigned char green, unsigned char blue);
	};

	/**
	*	@brief　内部構造体　フリップアニメーションは　Flip::～　のように指定するよ
	*/
	struct Flip {
		enum Type {
			CROSS_FADE,
			FADE_OUT_IN,
			SLIDE_UP,
			SLIDE_DOWN,
			SLIDE_RIGHT,
			SLIDE_LEFT,
			SCALEDOWN_ROTATION_RIGHT,
			SCALEDOWN_ROTATION_LEFT,
			PUSH_UP,
			PUSH_DOWN,
			PUSH_RIGHT,
			PUSH_LEFT,
			ROTATION_RIGHT,
			ROTATION_LEFT,
			ROTATION_UP,
			ROTATION_DOWN,
			DOOR_DEPTH_VERTICAL,
			DOOR_COME_VERTICAL,
			DOOR_DEPTH_HORIZONTAL,
			DOOR_COME_HORIZONTAL,
			CROSS_SLIDE_HORIZONTAL,
			DEFAULT
		};
	private:
		enum {
			maxCount = 256
		};

		Flip(Type type = DEFAULT,const char* ruleGraph = "", const char* ruleGraph2 = "", unsigned char speed = 10,unsigned char gradate = 1);

		void SetDrawMode(DrawMode* drawMode);

		bool Draw(Graph now, Graph next, DrawMode* dNow, DrawMode* dNext);

		bool DrawAppear(Graph screen,DrawMode* mode);

		bool DrawDisappear(Graph screen, DrawMode* mode);

		Type type;
		Graph graph, graph2;
		unsigned char gradate;
		unsigned char speed;
		unsigned char cnt;//countの事。使用率ランキング上位に入るので、三字略変数に殿堂入り

		friend class CGame;
		friend class CScene;
		friend struct SystemSetting;
	};

	/**
	*	@brief　シーンクラスだよ　FlipSceneにはこれの継承クラスを入れたらいいよ　子シーンを追加できるよ
	*/
	class CScene {
	public:
		/**
		*	@brief　既定のコンストラクタ
		*/
		CScene();

		/**
		*	@brief　最初から子シーンを持ちたいときに使う
		*/
		CScene(CScene* scene);

		/**
		*	@brief　最初から子シーンを持ちたいときに使う　ルール画像使用トランシジョン
		*/
		CScene(CScene* scene, const char* ruleGraph, unsigned char speed = 10, unsigned char gradate = 1);

		/**
		*	@brief　最初から子シーンを持ちたいときに使う　ルール画像二つ使用トランシジョン
		*/
		CScene(CScene* scene, const char* ruleGraph, const char* ruleGraph2, unsigned char speed = 10, unsigned char gradate = 1);

		/**
		*	@brief　最初から子シーンを持ちたいときに使う　Flip.～で指定するやつ
		*/
		CScene(CScene* scene, Flip::Type flipType, unsigned char speed = 10);

		/**
		*	@brief　デストラクタ
		*/
		virtual ~CScene();

		/**
		*	@brief　子シーン切り替え
		*/
		void FlipScene(CScene* scene);

		/**
		*	@brief　子シーン切り替え　ルール画像使用トランシジョン
		*/
		void FlipScene(CScene* scene, const char* ruleGraph, unsigned char speed = 10, unsigned char gradate = 1);

		/**
		*	@brief　子シーン切り替え　ルール画像二つ使用トランシジョン
		*/
		void FlipScene(CScene* scene, const char* ruleGraph, const char* ruleGraph2, unsigned char speed = 10, unsigned char gradate = 1);

		/**
		*	@brief　子シーン切り替え　Flip.～で指定するやつ
		*/
		void FlipScene(CScene* scene, Flip::Type flipType, unsigned char speed = 10);

		/**
		*	@brief　子シーン削除
		*/
		void RemoveScene();

		/**
		*	@brief　子シーン削除　ルール画像使用トランシジョン
		*/
		void RemoveScene(const char* ruleGraph, unsigned char speed = 10, unsigned char gradate = 1);

		/**
		*	@brief　子シーン削除　Flip.～で指定するやつ
		*/
		void RemoveScene(Flip::Type flipType, unsigned char speed = 10);

		/**
		*	@brief　クラス専用のマネージャーの使用宣言
		*/
		template<typename Object>
		void UseManager() {
			if (managerKey.count(typeid(Object).raw_name()) > 0)return;
			managerKey.insert(std::map<std::string, const char>::value_type(std::string(typeid(Object).raw_name()),manager().size()));
			manager().push_back(new CManager<Object>());
		}

		/**
		*	@brief　クラス専用のマネージャーの使用宣言 コンストラクタ使用バージョン
		*/
		template<typename Object>
		void UseManager(CManager<Object>* ptr) {
			if (managerKey.count(typeid(Object).raw_name()) > 0)return;
			managerKey.insert(std::map<std::string, const char>::value_type(std::string(typeid(Object).raw_name()), manager().size()));
			manager().push_back(ptr);
		}

		/**
		*	@brief　普通にオブジェクト追加
		*/
		void AddObject(CObject* object);

		/**
		*	@brief　クラス専用のマネージャーにオブジェクト追加　存在しないならfalse　使用宣言しましょう
		*/
		template<class Object>
		bool AddObjectToManager(Object* object) {
			auto it = managerKey.find(typeid(Object).raw_name());
			if (it == managerKey.end())return false;
			object->SetScene(this);
			(static_cast<CManager<Object>*>(manager()[it->second]))->AddObject(object);
			return true;
		}

		/**
		*	@brief　クラス専用のマネージャー取得　存在しないならnullptr Algorithm使うだけならいらない　特殊化されたマネージャー向け
		*/
		template<class Object>
		CManager<Object>* GetManager() {
			auto it = managerKey.find(typeid(Object).raw_name());
			if (it == managerKey.end())return nullptr;
			return static_cast<CManager<Object>*>(manager()[it->second]);//コードさえ間違っていなかったら、確実にキャストでき、仮想継承ではないので、問題ない
		}

		/**
		*	@brief　スクロール値指定　スクロールは手動です　シーンごとに共有管理できるから、十分だろう
		*/
		void SetScrol(float x = 0, float y = 0);

		/**
		*	@brief　スクロール値取得　スクロールは手動です　シーンごとに共有管理できるから、十分だろう
		*/
		Twin<float> GetScrol();

		/**
		*	@brief　スクロール値取得　スクロールは手動です　シーンごとに共有管理できるから、十分だろう
		*/
		float GetScrolX();

		/**
		*	@brief　スクロール値取得　スクロールは手動です　シーンごとに共有管理できるから、十分だろう
		*/
		float GetScrolY();

		/**
		*	@brief　シーンのブレンドモードを設定　詳しくはDxLibのSetDrawBlendModeのリファレンスを参照
		*/
		void SetBlendMode(unsigned char blendMode = DX_BLENDMODE_NOBLEND,unsigned char param = 255);

		/**
		*	@brief　シーンの描画輝度を設定　詳しくはDxLibのSetDrawBrightのリファレンスを参照
		*/
		void SetBright(unsigned char red,unsigned char green,unsigned char blue);

		/**
		*	@brief　描画モードを取得　nullptrに注意
		*/
		DrawMode* GetDrawMode();

		/**
		*	@brief	背景画像設定　使うならどうぞ
		*/
		void SetBackGround(const char* fileName);

		/**
		*	@brief	デバッグウインドウに文字列出力　使ったフレームだけ
		*/
		void DebugPrint(const char* name, const char* string);

		/**
		*	@brief	デバッグウインドウにフラグ出力　使ったフレームだけ
		*/
		void DebugPrintFlag(const char* name, bool flag);

		/**
		*	@brief	デバッグウインドウから実行できる関数　　Startで関数ごとに一度使う
		*/
		void DebugRegistFunc(const char* name, std::function<void()> func);

		/**
		*	@brief	デバッグウインドウから実行できる関数　　Startで関数ごとに一度使う
		*/
//		void DebugRegistFuncInt(const char* name, std::function<void(int)> func);

		/**
		*	@brief	デバッグウインドウから実行できる関数　　Startで関数ごとに一度使う
		*/
//		void DebugRegistFuncDouble(const char* name, std::function<void(double)> func);

		/**
		*	@brief	デバッグウインドウに変数出力　Startで変数ごとに一度使う　シーン中に消すならRemove使う
		*/
//		void DebugRegist(const char* name, unsigned char* value);

		/**
		*	@brief	デバッグウインドウに変数出力　Startで変数ごとに一度使う　シーン中に消すならRemove使う
		*/
		void DebugRegist(const char* name, int* value);

		/**
		*	@brief	デバッグウインドウに変数出力　Startで変数ごとに一度使う　シーン中に消すならRemove使う
		*/
	//	void DebugRegist(const char* name, unsigned int* value);

		/**
		*	@brief	デバッグウインドウに変数出力　Startで変数ごとに一度使う　シーン中に消すならRemove使う
		*/
		void DebugRegist(const char* name, float* value);

		/**
		*	@brief	デバッグウインドウに変数出力　Startで変数ごとに一度使う　シーン中に消すならRemove使う
		*/
		void DebugRegist(const char* name, double* value);

		/**
		*	@brief	デバッグウインドウに変数出力　Startで変数ごとに一度使う　シーン中に消すならRemove使う
		*/
		void DebugRegist(const char* name, bool* value);

		/**
		*	@brief	動的確保した変数、オブジェクトの変数は消去時に使う
		*/
//		void DebugRemove(unsigned char* value);

		/**
		*	@brief	動的確保した変数、オブジェクトの変数は消去時に使う
		*/
		void DebugRemove(int* value);

		/**
		*	@brief	動的確保した変数、オブジェクトの変数は消去時に使う
		*/
//		void DebugRemove(unsigned int* value);

		/**
		*	@brief	動的確保した変数、オブジェクトの変数は消去時に使う
		*/
		void DebugRemove(float* value);

		/**
		*	@brief	動的確保した変数、オブジェクトの変数は消去時に使う
		*/
		void DebugRemove(double* value);

		/**
		*	@brief	動的確保した変数、オブジェクトの変数は消去時に使う
		*/
		void DebugRemove(bool* value);

	private:
		CScene(bool fake);

		/**
		*	@brief　FlipScene時に実行される。初期化用　仮想関数　
		*/
		virtual void Start();

		void Update();

		/**
		*	@brief　毎フレーム実行　仮想関数
		*/
		virtual void Loop();

		void Graphic();

		/**
		*	@brief　毎フレーム実行　描画用　仮想関数
		*/
		virtual void Draw();

		/**
		*	@brief　毎フレームの最後に実行　オブジェクトの削除処理
		*/
		void LoopEnd();

		/**
		*	@brief　シーンが上書きされたときに実行。後処理用　仮想関数
		*/
		virtual void End();

		void Regist();

		void SetDrawMode(CScene* obj);

		void SetDrawBlendMode(CScene* obj);

		void SetDrawBright(CScene* obj);

		UniquePtr<CScene> now, next;
		Graph screen, nextScreen, backGround;
		Twin<float> scrol;
		Flip* flip;
		DrawMode* mode;
		unsigned char flag;

		CManager<CObject> object;
		safe_vector<CManagerBase> manager;//削除が起きないのでvector
		std::map<std::string, const char> managerKey;//検索を要するのでmap

#ifdef DEBUG 
		std::list<std::pair<std::string, std::string>> debugStr;
		std::list<std::pair<std::string, bool>> debugFlag;
//		std::list<std::pair<std::string, unsigned char*>> debugUchar;
		std::list<std::pair<std::string, int*>> debugInt;
//		std::list<std::pair<std::string, unsigned int*>> debugUint;
		std::list<std::pair<std::string, float*>> debugFloat;
		std::list<std::pair<std::string, double*>> debugDouble;
		std::list<std::pair<std::string, bool*>> debugBool;
		std::list<std::pair<std::string, std::function<void()>>> debugFuncVoid;
//		std::list<std::pair<std::string, std::function<void(int)>>> debugFuncInt;
//		std::list<std::pair<std::string, std::function<void(double)>>> debugFuncDouble;
#endif 


		/**
		*	@brief　これをオーバーライドする人は呪い殺されます　独自のシーン切り替え効果を作りたい人は、コードを完全に理解したうえでオーバーライドすればいいと思います　バグっても責任は取りません
		*/
		virtual bool FlipTransition();

		enum {
			isFliping = 1 << 0,
			isNextFlip = 1 << 1
		};

		friend class CGame;
		friend class CSystem;
		friend class CDebug;
	};
}