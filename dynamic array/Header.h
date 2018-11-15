//
//  Header.h
//  草稿
//
//  Created by 王舒啸 on 2018/10/13.
//  Copyright © 2018 王舒啸. All rights reserved.
//

#ifndef Header_h

#include<string>
#include<new>
#include<utility>
#include<algorithm>

using namespace std;

class StrVec{
private:
    static allocator<string>alloc;
    void reallocator();
    void check(){ if (size()==capacity()) reallocator();}
    void free();
    pair<string*,string*> alloc_copy(const string * a,const string * b);
    pair<string*,string*> alloc_move(const string * a,const string * b);
    string *first;
    string *blank;
    string *last;
public:
    StrVec ():first(nullptr),blank(nullptr),last(nullptr){};
    StrVec (initializer_list<string>il);
    StrVec (const StrVec &s);
    StrVec (StrVec &&s) noexcept;
    StrVec& operator=(const StrVec& s) ;
    StrVec& operator=(StrVec&& s) noexcept;
    ~StrVec() {free();}
    void push_back(const string &s) &;
    void push_back(string &&s)  &&;
    bool reserve (size_t);
    void print() const;
    void resize(size_t);
    void resize(size_t , const string &);
    size_t capacity() const {return last - first;};
    size_t size() const {return blank-first;};
    string* begin() const {return first;};
    string* end() const {return blank;};
};

#define Header_h


#endif /* Header_h */
