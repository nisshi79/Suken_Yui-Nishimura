#pragma once

/**
*	@file	Game.h
*	@brief	CSceneを継承したら、コード量が超減った
*	@author	Photon
*/

#include "Scene.h"

namespace suken {
	/**
	*	@brief　すべてのシーンの親です　new CGame() をFlipSceneに入れる奴は、呪い殺されます
	*/
	class CGame :private CScene{
	public:
		CGame();

		/**
		*	@brief　シーン切り替えします　どこで使っても呪われることはありません
		*/
		void FlipScene(CScene* scene);

		/**
		*	@brief　シーン切り替えします　トランシジョンします　どこで使っても呪われることはありません
		*/
		void FlipScene(CScene* scene, const char* ruleGraph, unsigned char speed = 10, unsigned char gradate = 1);

		/**
		*	@brief　シーン切り替えします　トランシジョンします　どこで使っても呪われることはありません
		*/
		void FlipScene(CScene* scene, const char* ruleGraph, const char* ruleGraph2, unsigned char speed = 10, unsigned char gradate = 1);

		/**
		*	@brief　シーン切り替えします　トランシジョンします　どこで使っても呪われることはありません
		*/
		void FlipScene(CScene* scene, Flip::Type flipType, unsigned char speed = 10);

		/**
		*	@brief	デバッグウインドウから実行できる関数　　Awakeで関数ごとに一度使う
		*/
		void DebugRegistFunc(const char* name, std::function<void()> func);

		/**
		*	@brief	デバッグウインドウから実行できる関数　　Awakeで関数ごとに一度使う
		*/
//		void DebugRegistFuncInt(const char* name, std::function<void(int)> func);

		/**
		*	@brief	デバッグウインドウから実行できる関数　　Awakeで関数ごとに一度使う
		*/
//		void DebugRegistFuncDouble(const char* name, std::function<void(double)> func);

	private:
		Anim loadingAnim;
		char loadingFlipTime;
		int loadingPosX;
		int loadingPosY;

		void DrawNowLoading();

		bool FlipTransition();

		/**
		*	@brief　初期設定です
		*/
		void Init(CScene* scene);

		/**
		*	@brief　初期設定です
		*/
		void Init(CScene* scene, Flip flip);

		friend class CSystem;
		friend class CDebug;
	};

	extern CGame Game;
}