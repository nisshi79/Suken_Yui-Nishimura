#pragma once

namespace suken {
	template<typename T>class SharedPtr {
	public:
		SharedPtr() {
			ptr = nullptr;
			refCnt = nullptr;
			wekCnt = nullptr;
		}

		explicit SharedPtr(T* ptr) {
			this->ptr = ptr;
			refCnt = new unsigned char(0);
			wekCnt = new unsigned char(0);
			AddRef();
		}

		explicit SharedPtr(const SharedPtr<T> &obj) {
			refCnt = obj.refCnt;
			wekCnt = obj.wekCnt;
			ptr = obj.ptr;
			if (refCnt != nullptr) {
				AddRef();
			}
		}

		SharedPtr<T>& operator=(const SharedPtr<T> &obj) {
			if (ptr == obj.ptr){
				return *this;
			}
			Release();
			refCnt = obj.refCnt;
			wekCnt = obj.wekCnt;
			ptr = obj.ptr;
			if (refCnt != nullptr) {
				AddRef();
			}
			return *this;
		}

		void Set(T* ptr = nullptr) {
			Release();
			refCnt = new unsigned char(0);
			wekCnt = new unsigned char(0);
			this->ptr = ptr;
			AddRef();
		}

		void Clear() {
			Release();
			ptr = nullptr;
			refCnt = nullptr;
			wekCnt = nullptr;
		}

		T* Get() {
			return ptr;
		}

		virtual ~SharedPtr() {
			if (refCnt != nullptr) {
				Release();
			}
		}

		T* operator->() {
			return ptr;
		}

		T* operator->()const {
			return ptr;
		}

		T& operator*() {
			return *ptr;
		}

		T& operator*()const {
			return *ptr;
		}

		unsigned char* GetRefCnt(){
			return refCnt;
		}

		unsigned char* GetWekCnt(){
			return wekCnt;
		}

	private:
		T* ptr;
		unsigned char* refCnt;
		unsigned char* wekCnt;

		void AddRef() {
			++(*refCnt);
			++(*wekCnt);
		}
		void Release() {
			--(*refCnt);
			--(*wekCnt);
			if ((*refCnt) == 0) {
				delete ptr;
			}
			if ((*wekCnt) == 0) {
				delete refCnt;
				delete wekCnt;
			}
		}
	};

	template<typename T>class WeekPtr {
	public:
		WeekPtr() {
			refCnt = nullptr;
			wekCnt = nullptr;
			ptr = nullptr;
		}

		WeekPtr(SharedPtr<T>& obj) {
			refCnt = obj.GetRefCnt();
			wekCnt = obj.GetWekCnt();
			ptr = obj.Get();
			AddWek();
		}

		WeekPtr(WeekPtr<T>& obj) {
			refCnt = obj.refCnt;
			wekCnt = obj.wekCnt;
			ptr = obj.ptr;
			if (refCnt != nullptr) {
				AddWek();
			}
		}

		SharedPtr<T>& operator=(const SharedPtr<T> &obj) {
			if (ptr == obj.ptr) {
				return *this;
			}
			Release();
			refCnt = obj.GetRefCnt();
			wekCnt = obj.GetWekCnt();
			ptr = obj.ptr;
			if (refCnt != nullptr) {
				AddRef();
			}
			return *this;
		}

		T* Get() {
			return ptr;
		}

		virtual ~WeekPtr() {
			if (refCnt != nullptr) {
				Release();
			}
		}

		T* operator->() {
			return ptr;
		}

		T& operator*() {
			return *ptr;
		}

	private:
		T* ptr;
		unsigned char* refCnt;
		unsigned char* wekCnt;

		void AddWek() {
			++(*wekCnt);
		}
		void Release() {
			--(*wekCnt);
			if ((*wekCnt) == 0) {
				delete refCnt;
				delete wekCnt;
			}
		}
	};
}