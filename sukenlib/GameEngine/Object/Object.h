#pragma once

#include "../../Manager.h"
#include "../../Utility/UniquePtr.h"
#include <queue>
#include <list>

#define OBJECT_CHARM(ObjectName) friend class CScene; friend class CManager< ObjectName >;friend struct Algorithm;

namespace suken {
	class CObject;

	/**
	*	@brief	オブジェクトマネージャーを一元的に扱うためのクラスです。
	*/
	class CManagerBase {
	public:
		/**
		*	コンストラクタ
		*/
		CManagerBase() {}

		/**
		*	@brief	デストラクタ
		*/
		virtual ~CManagerBase() {}
	private:
		/**
		*	@brief オブジェクトの登録を行う
		*/
		virtual void Regist() {}

		/**
		*	@brief シーンが子シーンを所持していないときに、毎フレーム呼ばれる
		*/
		virtual void Loop() {}

		/**
		*	@brief 毎フレーム呼ばれる
		*/
		virtual void Draw() {}

		/**
		*	@brief ここでGetDeleteFlag()して、削除されるか確かめる
		*/
		virtual void LoopEnd() {}

		virtual int GetSize() { return 0; }

		friend class CScene;
		friend class CDebug;
		friend struct Algorithm;
	};

	/**
	*	@brief	CObjectを継承したクラスを登録することができ、分けて扱うことができます　Algorithm関数を用いると、マネージャーに入っているオブジェクトに対して、操作することができます
	*	するべき機能を果たすなら、特殊化して、扱うことを許します。
	*/
	template<class Object>
	class CManager :public CManagerBase {
	public:
		CManager() {}

		virtual ~CManager() {}
	private:
		void AddObject(Object* object) {
			m_queue.push(object);
		}

		void Regist() {
			while (!m_queue.empty()) {
				Object* o = m_queue.front();
				m_queue.pop();
				o->Start();
				m_object.push_back(nullptr);
				m_object.back().Reset(o);
			}
		}

		void Loop() {
			for (auto i = m_object.begin(); i != m_object.end(); ++i) {
				(*i)->Loop();
			}
		}

		void Draw() {
			for (auto i = m_object.begin(); i != m_object.end(); ++i) {
				(*i)->Draw();
			}
		}

		void LoopEnd() {
			for (auto i = m_object.begin(); i != m_object.end();) {
				if ((*i)->GetDeleteFlag()) {
					(*i)->End();
					i = m_object.erase(i);
				}
				else {
					++i;
				}
			}
		}

		int GetSize() {
			return m_object.size();
		}

		std::queue<Object*> m_queue;
		std::list<UniquePtr<Object>> m_object;

		friend class CScene;
		friend class CDebug;
		friend struct Algorithm;
	};

	/**
	*	@brief　すべてのオブジェクトの親です
	*/
	class CObject {
	public:
		/**
		*	@brief　コンストラクタ
		*/
		CObject();

		/**
		*	@brief　デストラクタ
		*/
		virtual ~CObject();
	protected:

		/**
		*	@brief　オブジェクトを所持するシーンのポインタを入手
		*/
		CScene *const GetScene();

		/**
		*	@brief 消すよ　Loop()内で使ってください
		*/
		void Delete();

		/**
		*	@brief 消される直前かどうか、確認
		*/
		bool GetDeleteFlag();
	private:

		/**
		*	@brief　最初に呼ばれる　仮想クラス
		*/
		virtual void Start();

		/**
		*	@brief　子シーン持ってない時に呼ばれる　仮想クラス
		*/
		virtual void Loop();

		/**
		*	@brief　描画する時に呼ばれる　仮想クラス
		*/
		virtual void Draw();

		/**
		*	@brief　終わりの時に呼ばれる　仮想クラス
		*/
		virtual void End();

		CScene* scene;

		bool deleteFlag;

		void SetScene(CScene* ptr);

		friend class CScene; 
		template <class> friend class CManager; 
		friend struct Algorithm;
	};
}