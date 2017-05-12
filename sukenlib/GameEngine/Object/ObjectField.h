#pragma once

#include "Object.h"
#include "../../Utility/safe_vector.h"

namespace suken {
	class CObjectField:public CObject {
	public:
		CObjectField(unsigned char x, unsigned char y):x(x),y(y),num(0){}

		CObjectField(unsigned char x, unsigned char y, unsigned char num) :x(x), y(y), num(num) {}

		~CObjectField(){}

	protected:
		unsigned char x, y, num;
	private:

		/**
		*	@brief　最初に呼ばれる　仮想クラス
		*/
		virtual void Start(){}

		/**
		*	@brief　子シーン持ってない時に呼ばれる　仮想クラス
		*/
		virtual void Loop(){}

		/**
		*	@brief　描画する時に呼ばれる　仮想クラス
		*/
		virtual void Draw(){}

		/**
		*	@brief　終わりの時に呼ばれる　仮想クラス
		*/
		virtual void End() {}

		OBJECT_CHARM(CObjectField)
	};

	template<>
	class CManager<CObjectField> :public CManagerBase {
	public:
		CManager(unsigned char width,unsigned char height):w(width),h(height),m_object(width*height,nullptr) {}

		virtual ~CManager() {}


	private:
		void AddObject(CObjectField* object) {
			m_queue.push(object);
		}

		void Regist() {
			while (!m_queue.empty()) {
				CObjectField* o = m_queue.front();
				m_queue.pop();
				if (m_object[o->x + o->y*w].Get() == nullptr) {
					o->Start();
					m_object[o->x + o->y*w].Reset(o);
				}
			}
		}

		void Loop() {
			for (auto i = m_object.begin(); i != m_object.end(); ++i) {
				if(i->Get() != nullptr)(*i)->Loop();
			}
		}

		void Draw() {
			for (auto i = m_object.begin(); i != m_object.end(); ++i) {
				if (i->Get() != nullptr)(*i)->Draw();
			}
		}

		void LoopEnd() {
			for (auto i = m_object.begin(); i != m_object.end();) {
				if (i->Get() != nullptr && (*i)->GetDeleteFlag()) {
					(*i)->End();
					i->Reset(nullptr);
				}
				else {
					++i;
				}
			}
		}

		std::queue<CObjectField*> m_queue;
		std::vector<UniquePtr<CObjectField>> m_object;

		unsigned char w, h;

		friend class CScene;
		friend struct Algorithm;
	};
}