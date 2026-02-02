#ifndef SHARED_PTR_HPP
#define SHARED_PTR_HPP
#include "shared_ptr.h"

#include <iostream>


template <class T>
class SharedPtr {
public:
    SharedPtr(T* value);
    SharedPtr();
    SharedPtr(const SharedPtr<T>& shared_ptr);
    T* get();
    size_t use_count();
    SharedPtr<T>& operator=(const SharedPtr<T>&other);
    T* operator->();
    T& operator*();
    explicit operator bool() const { return data != nullptr; }
    void reset();
    void reset(T* value);
    ~SharedPtr();

private:
    T* data;
    std::size_t* ref_count;
};

template <class T>
SharedPtr<T>::SharedPtr(T* value) : data(value) {
    if(data){
        ref_count = new size_t(1);
    }
    else{
        ref_count = nullptr;
    }
}

template <class T>
SharedPtr<T>::SharedPtr() {
    data = nullptr;
    ref_count = nullptr;
}

template <class T>
SharedPtr<T>::SharedPtr(const SharedPtr<T>& shared_ptr):data(shared_ptr.data),ref_count(shared_ptr.ref_count){
    if(ref_count){
        (*ref_count)++;
    }
}

template <class T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<T>&other){
    if(this == &other){
        return *this;
    }

    if(ref_count){
        (*ref_count)--;
        if(*ref_count == 0){
            delete(data);
            data = nullptr;
        }
    }

    ref_count = other.ref_count;
    data = other.data;

    if(ref_count)
        (*ref_count)++;

    return *this;
}

template <class T>
T& SharedPtr<T>::operator*(){
    return *get();
}

template <class T>
T* SharedPtr<T>::operator->(){
    return get();
}

template <class T>
T* SharedPtr<T>::get(){
    return data;
}

template <class T>
size_t SharedPtr<T>::use_count(){
    return *ref_count;
}

template <class T>
void SharedPtr<T>::reset(){
    delete(data);
    data = nullptr;
    *ref_count = 0;
}

template <class T>
void SharedPtr<T>::reset(T* value){
    delete(data);
    delete(ref_count);
    data = value;
    ref_count = new size_t(1);
}

template <class T>
SharedPtr<T>::~SharedPtr(){
    if(ref_count){
        (*ref_count)--;
        if((* ref_count) <= 0){
            delete(data);
            data = nullptr;
        }
    }
    
}

template <class T>
SharedPtr<T> make_shared(T data){
    auto ptr = new T(data);
    return SharedPtr<T>(ptr);
}

#endif
