#pragma once

#include <vector>

template<typename Ty>
class safe_vector{
public:
	safe_vector() {}

	template<typename Iter>
	safe_vector(Iter First,Iter Last):v(First, Last) {}

	safe_vector(std::vector<Ty*> &&Right):v(Right){}

	safe_vector(const std::vector<Ty*> &Right) :v(Right) {}

	safe_vector(const std::allocator<Ty*> &Al) :v(Al) {}

	template<typename Iter>
	safe_vector(Iter First, Iter Last, const std::allocator<Ty*> &Al) : v(First, Last, Al) {}

	safe_vector(std::size_t Count):v(Count){}

	safe_vector(std::size_t Count, Ty* const Val) :v(Count,Val) {}

	safe_vector(std::size_t Count, Ty* const Val, const std::allocator<Ty*> &Al) :v(Count, Val,Al) {}

	std::vector<Ty*>& operator ()() {
		return v;
	}

	operator std::vector<Ty*>&() {
		return v;
	}

	~safe_vector() {
		for (auto i = v.begin(); i != v.end(); ++i) {
			if ((*i) != nullptr) {
				delete *i;
			}
		}
	}

private:
	std::vector<Ty*> v;
};