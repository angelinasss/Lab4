#include <iostream>

template <typename T> 
class shared_ptr {
	T* ptr = nullptr;
	size_t* count = nullptr;

public:
	explicit shared_ptr(T* ptr): ptr(ptr), count(new int(1)) {}

	shared_ptr() {}

	shared_ptr(const shared_ptr& other) {
		ptr(other.ptr), count(other.count) {
			++*count;
		}
	}

	shared_ptr(shared_ptr&& other) : ptr(other.ptr), count(other.count) {
		other.ptr = nullptr;
		other.count = nullptr;
	}

	T* get() const noexcept {
		return ptr;
	}

	size_t use_count() const noexcept {
		return *count;
	}

	T& operator*() const{
		return *ptr;
	}

	T* operator->() const{
		return ptr;
	}

	shared_ptr<T>& operator=(shared_ptr&& other) noexcept {
		~shared_ptr()
		ptr(other.ptr);
		count(other.count);
		other.ptr = nullptr;
		other.count = nullptr;
	}

	shared_ptr<T>& operator=(const shared_ptr& other) {
		if (this != other) {
			ptr(other.ptr);
			count(other.count);
			if (other.ptr != nullptr)
				++*count;
		}
	}

	template <typename T,typename... Args>
    make_shared(Args&&... args) {
		auto ptr = new T(std::forward<Args>(args)...);
		return shared_ptr<T>(ptr);
	}

	~shared_ptr()
	{
		if (count == nullptr) return;
		--*count;
		if (*count == 0) {
			delete ptr;
			delete count;
		}
	}
};