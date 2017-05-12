#pragma once

#include "../../Manager.h"
#include "../Object/Object.h"
#include "../Scene.h"
#include <algorithm>
#include <functional>

namespace suken {
	/**
	*	マネージャーに登録されたオブジェクトに対して、処理を行える、アルゴリズムの構造体
	*/
	struct Algorithm {
		Algorithm(CScene* scene):scene(scene){}

		template<class Object>
		bool all_of(std::function<bool(Object*)> func) {
			CManager<Object>* list = scene->GetManager<Object>();
			if (list == nullptr || list->m_object.size() == 0)return true;//コードの最適化により、nullptrの時は通らない...はず
			for (auto i = list->m_object.begin(); i != list->m_object.end(); ++i) {
				if (i->Get() != nullptr && !func(i->Get())) {
					return false;
				}
			}
			return true;
		}

		template<class Object>
		bool any_of(std::function<bool(Object*)> func) {
			CManager<Object>* list = scene->GetManager<Object>();
			if (list == nullptr || list->m_object.size() == 0)return false;//コードの最適化により、nullptrの時は通らない...はず
			for (auto i = list->m_object.begin(); i != list->m_object.end(); ++i) {
				if (i->Get() != nullptr && func(i->Get())) {
					return true;
				}
			}
			return false;
		}

		template<class Object>
		bool none_of(std::function<bool(Object*)> func) {
			CManager<Object>* list = scene->GetManager<Object>();
			if (list == nullptr || list->m_object.size() == 0)return true;//コードの最適化により、nullptrの時は通らない...はず
			for (auto i = list->m_object.begin(); i != list->m_object.end(); ++i) {
				if (i->Get() != nullptr && func(i->Get())) {
					return false;
				}
			}
			return true;
		}

		template<class Object>
		bool for_each(std::function<void(Object*)> func) {
			CManager<Object>* list = scene->GetManager<Object>();
			if (list == nullptr || list->m_object.size() == 0)return false;//コードの最適化により、nullptrの時は通らない...はず
			for (auto i = list->m_object.begin(); i != list->m_object.end(); ++i) {
				if(i->Get() != nullptr)func(i->Get());
			}
			return true;
		}

		template<class Object>
		Object* find(std::function<bool(Object*)> func) {
			CManager<Object>* list = scene->GetManager<Object>();
			if (list == nullptr || list->m_object.size() == 0)return nullptr;//コードの最適化により、nullptrの時は通らない...はず
			for (auto i = list->m_object.begin(); i != list->m_object.end(); ++i) {
				if (i->Get() != nullptr && func(i->Get()))return i->Get();
			}
			return nullptr;
		}

		template<class Object>
		bool If(std::function<bool(Object*)> If, std::function<void(Object*)> Do) {
			CManager<Object>* list = scene->GetManager<Object>();
			if (list == nullptr || list->m_object.size() == 0)return false;//コードの最適化により、nullptrの時は通らない...はず
			for (auto i = list->m_object.begin(); i != list->m_object.end(); ++i) {
				if (i->Get() != nullptr && If(i->Get()))Do(i->Get());
			}
			return true;
		}

		template<class Object>
		int count(std::function<bool(Object*)> func) {
			CManager<Object>* list = scene->GetManager<Object>();
			if (list == nullptr || list->m_object.size() == 0)return 0;//コードの最適化により、nullptrの時は通らない...はず
			int cnt = 0;
			for (auto i = list->m_object.begin(); i != list->m_object.end(); ++i) {
				if (i->Get() != nullptr && func(i->Get()))++cnt;
			}
			return cnt;
		}

		template<class Object>
		bool Collision(std::function<void(Object*,Object*)> func) {
			CManager<Object>* list = scene->GetManager<Object>();
			if (list == nullptr || list->m_object.size() == 0)return false;//コードの最適化により、nullptrの時は通らない...はず
			it1 = list->m_object.begin();
			it2 = it1;
			++it2;
			for (int i = 0; i < list->m_object.size(); ++i) {
				for (int j = i + 1; j < list->m_object.size(); ++j) {
					if(i->Get() != nullptr && j->Get() != nullptr)func(it1->Get(), it2->Get());
					++it2;
				}
				++it1;
				it2 = it1;
				++it2;
			}
			return true;
		}

		template<class Object1,class Object2>
		bool Collision(std::function<void(Object1*, Object2*)> func) {
			CManager<Object1>* list1 = scene->GetManager<Object1>();
			if (list1 == nullptr || list1->m_object.size() == 0)return false;//コードの最適化により、nullptrの時は通らない...はず
			CManager<Object2>* list2 = scene->GetManager<Object2>();
			if (list2 == nullptr || list2->m_object.size() == 0)return false;//コードの最適化により、nullptrの時は通らない...はず
			for (auto i = list1->m_object.begin(); i != list1->m_object.end(); ++i) {
				for (auto j = list2->m_object.begin(); j != list2->m_object.end(); ++j) {
					if (i->Get() != nullptr && j->Get() != nullptr)func(i->Get(), j->Get());
				}
			}
			return true;
		}

		template<class Object>
		bool sort(std::function<bool(Object*, Object*)> func) {
			CManager<Object>* list = scene->GetManager<Object>();
			if (list == nullptr || list->m_object.size() == 0)return false;//コードの最適化により、nullptrの時は通らない...はず
			list->m_object.sort([func](UniquePtr<Object> p1, UniquePtr<Object> p2) {
				return func(p1.Get(), p2.Get());
			});
			return true;
		}

		private:
			CScene* scene;
	};
}