#pragma once

namespace suken {
	/**
	*	@brief　自作ユニークポインタ　必要だった機能しか入っていない
	*/
	template<typename T>class UniquePtr {
	public:
		UniquePtr() {
			this->ptr = nullptr;
		}

		UniquePtr(T* ptr) {
			this->ptr = ptr;
		}

		~UniquePtr() {
			if (ptr != nullptr) {
				delete ptr;
			}
		}

		T* Release() {
			return ptr;
			ptr = nullptr;
		}

		void Reset(T* ptr = nullptr) {
			if (this->ptr != nullptr) {
				delete this->ptr;
			}
			this->ptr = ptr;
		}

		void Swap(UniquePtr& obj) {
			T* buf = ptr;
			ptr = obj.ptr;
			obj.ptr = buf;
		}

		void Swap(T** obj) {
			T* buf = ptr;
			ptr = *obj;
			*obj = buf;
		}

		T* Get() {
			return ptr;
		}

		T& operator*() {
			return *ptr;
		}

		T& operator*()const {
			return *ptr;
		}

		T* operator->() {
			return ptr;
		}

		T* operator->()const {
			return ptr;
		}

		operator bool() {
			return ptr != nullptr;
		}

		UniquePtr(const UniquePtr& ptr) {
			if (ptr.ptr == nullptr) {
				this->ptr = nullptr;
				return;
			}
			this->ptr = new T(*ptr.ptr);
		}

		UniquePtr& operator=(const UniquePtr&) {
			if (ptr != nullptr)delete this->ptr;
			this->ptr = new T(*ptr.ptr);
			return *this;
		}

	private:
		T* ptr;
	};
}