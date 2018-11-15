#ifndef STRBLOB_H_
#define STRBLOB_H_

#include<memory>
#include<vector>
#include<string>
#include<iostream>

using namespace std;

// 底层数据共享的类
template<typename T>
class StrBlobptr;

template <typename T>
class StrBlob{
private:
    shared_ptr<vector<T> > data;
    void check(size_t i);
public:
    friend class StrBlobptr<T>;
    StrBlob();
    explicit StrBlob(initializer_list<T>il);
    size_t size() const {return data->size();};
    bool empty() const {return data->empty();};
    void push(const T &s) & ;
    void push(T && s) && ;
    void pop();
    T& front();
    T& back();
    T& operator[](size_t) ;
    const T& front() const;
    const T& back()  const;
    const T& operator[](size_t) const ;
    
    StrBlobptr<T> begin();
    StrBlobptr<T> end();   
};

//核查数据的类
template <typename T>
class StrBlobptr{
    template <typename u>
    friend bool equal (const StrBlobptr<u> &a,const StrBlobptr<u> &b);
    template <typename u>
    friend bool no_equal (const StrBlobptr<u> &a,const StrBlobptr<u> &b);
    template <typename u>
    friend bool operator == (const StrBlobptr<u> &a,const StrBlobptr<u> &b);
    template <typename u>
    friend bool operator != (const StrBlobptr<u> &a,const StrBlobptr<u> &b);
private:
    weak_ptr<vector<T> > weak_data;
    shared_ptr<vector<T> > check(size_t);
    size_t cnt;
public:
    
    StrBlobptr():cnt(0){ };
    StrBlobptr(const StrBlob<T> &a,size_t c=0):weak_data(a.data),cnt(c){ };
    T & operator *()  ;
    StrBlobptr& operator ++();
    StrBlobptr& operator --();
};

#endif
