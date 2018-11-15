
#include "StrBlob.h"
#include<iostream>

template<typename T>
inline StrBlob<T>::StrBlob(){
    data = nullptr;
}

template<typename T>
inline StrBlob<T>::StrBlob(initializer_list<T>il){
    data = make_shared<vector<T> >(il);
}

template<typename T>
inline void StrBlob<T>::push(const T &s) &{
    data->push_back(s);
}

template<typename T>
inline void StrBlob<T>::push(T &&s) &&{
    data->push_back(std::move(s));
}

template<typename T>
inline void StrBlob<T>::pop() {
    data->pop_back();
}

template<typename T>
inline T& StrBlob<T>::front(){
    return data -> front();
}

template<typename T>
inline const T& StrBlob<T>::front () const{
    return data -> front();
}

template<typename T>
inline T& StrBlob<T>::back(){
    return data -> back();
}

template<typename T>
inline const T& StrBlob<T>::back () const{
    return data -> back();
}

template<typename T>
inline T& StrBlob<T>::operator[] (size_t t) {
    return (*data)[t];
}

template<typename T>
inline const T& StrBlob<T>::operator[] (size_t t) const  {
    return (*data)[t];
}

template <typename T>
inline void StrBlob<T>::check(size_t i){
    if (i >= data->size()){
        throw out_of_range("Out of range");
    }
}

template<typename T>
inline T& StrBlobptr<T>::operator *() {
    auto it = check(cnt);
    return (*it)[cnt];
}

template<typename T>
inline StrBlobptr<T>& StrBlobptr<T>::operator ++(){
    check(cnt);
    ++cnt;
    return *this;
}

template<typename T>
inline shared_ptr<vector<T> > StrBlobptr<T>:: check(size_t i){
    auto ret = weak_data.lock();
    if (!ret)   throw runtime_error("vector does not exist !");
    if (i >= ret->size())   throw out_of_range ("Out of range");
    return ret;
}

template<typename T>
inline StrBlobptr<T>& StrBlobptr<T>::operator --(){
    --cnt;
    check(-1);
    return *this;
}

template<typename T>
bool equal(const StrBlobptr<T> &a,const StrBlobptr<T> &b){
    auto c = a.weak_data.lock();
    auto d = b.weak_data.lock();
    if (c == d) return (!c||a.cnt==b.cnt);
        else return false;
}

template<typename T>
bool no_equal(const StrBlobptr<T> &a,const StrBlobptr<T> &b){
    return !equal(a,b);
}

template<typename T>
bool operator ==(const StrBlobptr<T> &a,const StrBlobptr<T> &b){
    return equal(a,b);
}

template<typename T>
bool operator !=(const StrBlobptr<T> &a,const StrBlobptr<T> &b){
    return !equal(a,b);
}

template<typename T>
StrBlobptr<T> StrBlob<T>::begin(){
    return StrBlobptr<T>(*this);
}

template<typename T>
StrBlobptr<T> StrBlob<T>::end(){
    return StrBlobptr<T>(*this,data->size());
}
