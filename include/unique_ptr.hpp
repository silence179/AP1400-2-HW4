#ifndef UNIQUE_PTR_HPP
#define UNIQUE_PTR_HPP

#include <iostream>
#include <string>

template <typename T>
class UniquePtr {
public:
    explicit UniquePtr(T* p = nullptr) : _p(p) {}

    ~UniquePtr() {
        if (_p) {
            delete _p;
            _p = nullptr; // 养成好习惯：删除后置空
        }
    }

    // 禁用拷贝构造函数
    UniquePtr(const UniquePtr&) = delete;

    // 禁用赋值运算符
    UniquePtr& operator=(const UniquePtr&) = delete;

    T* get() const {
        return _p;
    }

    T& operator*() const {
        return *_p;
    }

    T* operator->() const {
        return _p;
    }

    void reset(T* p = nullptr) {
        if (_p) {
            delete _p;
        }
        _p = p;
    }

    T* release() {
        T* temp = _p;
        _p = nullptr;
        return temp;
    }

    explicit operator bool() const {
        return _p != nullptr;
    }

private:
    T* _p;
};

template <typename T, typename... Args>
UniquePtr<T> make_unique(Args&&... args) {
    return UniquePtr<T>(new T(std::forward<Args>(args)...));
}

#endif
