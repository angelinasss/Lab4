#include "iterator.cpp"
#include <cstring>
#include <limits>

template<typename CharT>
class String {
private:
    CharT *arr = nullptr;
    size_t _size = 0;
    size_t _capacity = 0;

public:
    String();
    String(const char *);
    String(const String &);
    String(String &&) noexcept;
    void push_back(const CharT &);
    void append(const String&);
    void append(size_t, CharT);
    void insert(size_t, String);
    void pop_back();
    void erase(size_t, size_t);
    void replace(size_t, size_t, const String &);
    String substr(size_t, size_t);
    size_t size() const;
    size_t capacity();
    size_t length();
    void reserve(size_t);
    void resize(size_t);
    void resize(size_t, CharT);
    size_t max_size();
    void clear();
    bool empty();
    void shrink_to_fit();
    int compare(const String&);
    ~String();
    const CharT *c_str();
    CharT &front() const;
    CharT &back() const;
    CharT* data() const;
    iterator<CharT> begin();
    iterator<CharT> end();
    const_iterator<CharT> cbegin();
    const_iterator<CharT> cend();
    reverse_iterator<CharT> rbegin();
    reverse_iterator<CharT> rend();
    String &operator=(const String &);
    String &operator=(String &&) noexcept;
    String operator+(const String &);
    String &operator+=(const String &);
    CharT &operator[](size_t);
};

template<typename CharT>
String<CharT>::String(const char *str) {
    size_t length = strlen(str);
    reserve(length);
    for (int i = 0; i < length; i++) {
        new (arr + i) CharT(str[i]);
    }
    _size = length;
    _capacity = length;
}

template<typename CharT>
String<CharT>::String() {
    arr = reinterpret_cast<CharT*>(new int8_t[sizeof(CharT)]);
    _capacity = 1;
    _size = 0;
}

template<typename CharT>
String<CharT>::String(const String &other) {
    for (int i = 0; i < _size; i++) {
        (arr + i)->~T();
    }
    reserve(other._capacity);
    _size = other._size;
    for (int i = 0; i < _size; ++i) {
        new (arr + i) CharT(other._base[i]);
    }
}

template<typename CharT>
String<CharT>::String(String &&other) noexcept {
    for (int i = 0; i < _size; i++) {
        (arr + i)->~T();
    }
    arr = other.arr;
    _capacity = other._capacity;
    _size = other._size;
    other.arr = nullptr;
    other._capacity = 0;
    other._size = 0;
}

template<typename CharT>
void String<CharT>::push_back(const CharT &element) {
    if (_size >= _capacity) reserve(_size * 2);
    new (arr + _size) CharT(element);
    _size++;
}

template<typename CharT>
void String<CharT>::append(size_t amount, CharT symbol) {
    if (_capacity <= _size + amount) reserve(_size * 2);
    for (size_t i = _size; i < _size + amount; i++) {
        new (arr + i) CharT(symbol);
    }
    _size += amount;
}

template<typename CharT>
void String<CharT>::append(const String &str) {
    if (_capacity <= _size + str._size) reserve(_size * 2);
    insert(_size, str);
}

template<typename CharT>
void String<CharT>::insert(size_t ind, String str) {
    if (_capacity <= _size + str._size) reserve(_size * 2);
    for (size_t i = _size; i > ind; --i) {
        new (arr + i - 1 + str._size) CharT(arr[i - 1]);
    }
    size_t newind = 0;
    for (size_t i = ind; newind < str._size; i++, ++newind) {
        new (arr + i) CharT(str.arr[newind]);
    }
    _size += str._size;
}

template<typename CharT>
void String<CharT>::pop_back() {
    --_size;
    (arr + _size)->~CharT();
}

template<typename CharT>
void String<CharT>::erase(size_t ind, size_t count) {
    for (size_t i = ind; i < _size; i++) {
        new (arr + i) CharT(arr[i + count]);
    }
    _size -= count;
}

template<typename CharT>
void String<CharT>::replace(size_t ind, size_t amount, const String &newstr) {
    erase(ind, amount);
    insert(ind, newstr);
}

template<typename CharT>
String<CharT> String<CharT>::substr(size_t ind, size_t count) {
    String newstr;
    for (size_t i = ind; i < count; i++) {
        newstr.push_back(arr[i]);
    }
    return newstr;
}

template<typename CharT>
size_t String<CharT>::size() const {
    return _size;
}

template<typename CharT>
size_t String<CharT>::capacity() {
    return _capacity;
}

template<typename CharT>
size_t String<CharT>::length() {
    return _size;
}

template<typename CharT>
void String<CharT>::reserve(size_t count) {
    if (count > _capacity) {
        CharT* newarr = reinterpret_cast<CharT*>(new int8_t[count * sizeof(CharT)]);
        for (size_t i = 0; i < _size; i++) {
            new (newarr + i) CharT(arr[i]);
        }
        for (int i = 0; i < _size; i++) {
            (arr + i)->~T();
        }
        arr = newarr;
        _capacity = count;
    }
    else return;
}

template<typename CharT>
void String<CharT>::resize(size_t n) {
    if (n > _size) {
        if (_capacity <= n) reserve(_size * 2);
    }
    _size = n;
}

template<typename CharT>
void String<CharT>::resize(size_t n, CharT symbol) {
    if (n > _size) {
        if (_capacity <= n) reserve(_size * 2);
        for (size_t i = _size; i < n; i++) {
            arr[i] = symbol;
        }
    }
    _size = n;
}

template<typename CharT>
size_t String<CharT>::max_size() {
    return std::numeric_limits<std::size_t>::max();
}

template<typename CharT>
void String<CharT>::clear() {
    for (int i = 0; i < _size; i++) {
        (arr + i)->~T();
    }
    delete[] reinterpret_cast<int8_t*>(arr);
    arr = nullptr;
    _size = 0;
    String();
}

template<typename CharT>
bool String<CharT>::empty() {
    return _size == 0;
}

template<typename CharT>
void String<CharT>::shrink_to_fit() {
    _capacity = _size;
    CharT *newarr = reinterpret_cast<CharT*>(new int8_t[_size * sizeof(CharT)]);
    for (size_t i = 0; i < _size; i++) {
        new (newarr + i) CharT(arr[i]);
    }
}

template<typename CharT>
int String<CharT>::compare(const String &other) {
    size_t firstsize = _size;
    size_t secondsize = other.size();
    int result = std::char_traits<CharT>::compare(data(), other.data(), std::min(firstsize, secondsize));
    if (result != 0)
        return result;
    if (firstsize < secondsize)
        return -1;
    if (firstsize > secondsize)
        return 1;
    return 0;
}

template<typename CharT>
String<CharT>::~String() {
    for (int i = 0; i < _size; i++) {
        (arr + i)->~T();
    }
    delete[] reinterpret_cast<int8_t*>(arr);
    _capacity = 0;
    _size = 0;
}

template<typename CharT>
const CharT *String<CharT>::c_str() {
    CharT *c_str = reinterpret_cast<CharT*>(new int8_t[(_size + 1) * sizeof(CharT)]);
    for (size_t i = 0; i < _size; i++) {
        c_str[i] = arr[i];
    }
    c_str[_size] = '\0';
    return c_str;
}

template<typename CharT>
CharT &String<CharT>::front() const {
    return *arr;
}

template<typename CharT>
CharT &String<CharT>::back() const {
    return *(arr + _size - 1);
}

template<typename CharT>
CharT *String<CharT>::data() const {
    return arr;
}

template<typename CharT>
iterator<CharT> String<CharT>::begin() {
    return iterator<CharT>(arr);
}

template<typename CharT>
iterator<CharT> String<CharT>::end() {
    return iterator<CharT>(arr + _size);
}

template<typename CharT>
const_iterator<CharT> String<CharT>::cbegin() {
    return const_iterator<CharT>(arr);
}

template<typename CharT>
const_iterator<CharT> String<CharT>::cend() {
    return const_iterator<CharT>(arr + _size);
}

template<typename CharT>
reverse_iterator<CharT> String<CharT>::rbegin() {
    return reverse_iterator<CharT>(arr + _size - 1);
}

template<typename CharT>
reverse_iterator<CharT> String<CharT>::rend() {
    return reverse_iterator<CharT>(arr - 1);
}

template<typename CharT>
String<CharT> &String<CharT>::operator=(const String &other) {
    if (this != other) {
        for (int i = 0; i < _size; i++) {
            (arr + i)->~T();
        }
        reserve(other._capacity);
        _size = other._size;
        for (int i = 0; i < _size; i++) {
            new (arr + i) CharT(other._base[i]);
        }
    }
    return *this;
}

template<typename CharT>
String<CharT> &String<CharT>::operator=(String &&other) noexcept {
    for (int i = 0; i < _size; i++) {
        (arr + i)->~T();
    }
    arr = other.arr;
    _capacity = other._capacity;
    _size = other._size;
    other.arr = nullptr;
    other._capacity = 0;
    other._size = 0;
    return *this;
}

template<typename CharT>
String<CharT> String<CharT>::operator+(const String &other) {
    String newStr(*this);
    newStr.operator+=(other);
    return newStr;
}

template<typename CharT>
String<CharT> &String<CharT>::operator+=(const String &other) {
    size_t newInd = 0;
    if (_size + other._size >= _capacity) reserve(_size * 2);
    for (size_t i = _size; i < _size + other._size; i++) {
        new (arr + i) CharT(other._base[newInd++]);
    }
    _size += other._size;
    return *this;
}

template<typename CharT>
CharT &String<CharT>::operator[](size_t ind) {
    return arr[ind];
}
