#include <iostream>

template <typename T>
class unique_ptr {
	T* ptr;
public:
	explicit unique_ptr(T* ptr = nullptr): ptr(ptr) {}

	unique_ptr(const unique_ptr& x) = delete;

	unique_ptr(unique_ptr&& other) noexcept: ptr(other.ptr) {
		other.ptr = nullptr;
	}

	T& operator*() const{
		return *ptr;
	}

	T* operator->() const{
		return ptr;
	}

	T* get() const{
		return ptr;
	}

	unique_ptr& operator=(unique_ptr&& other) noexcept{
		if (&other == this) return *this;
		delete ptr;
		ptr = other.ptr;
		other.ptr = nullptr;
		return *this;
	}

	template <typename... Args>
	unique_ptr<T> make_unique(Args&&... args) {
		return unique_ptr<T>(new T(std::forward<Args>(args)...));
	}

	bool isNull() const {
		return ptr == nullptr;
	}

	~unique_ptr() {
		delete ptr;
	}
};