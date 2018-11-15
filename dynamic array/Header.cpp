//
//  Header.cpp
//  草稿
//
//  Created by 王舒啸 on 2018/10/13.
//  Copyright © 2018 王舒啸. All rights reserved.
//

#include "Header.h"
#include<iostream>



allocator<string> StrVec::alloc;

pair<string*,string*> StrVec::alloc_copy(const string *a, const string *b){
    auto newdata = alloc.allocate(b-a);
    return {newdata,uninitialized_copy(a, b, newdata)};
}

pair<string*,string*> StrVec::alloc_move(const string *a, const string *b){
    auto newdata = alloc.allocate(b-a);
    return {newdata,uninitialized_copy(make_move_iterator(a), make_move_iterator(b), newdata)};
}


void StrVec:: free(){
    if (first){
        for (auto p = blank;p != first;){
            alloc.destroy(--p);
        }
        alloc.deallocate(first, last-first);
    }
}

void StrVec::reallocator(){
    auto new_size = 2*size();
    auto new_data = alloc.allocate(new_size);
    auto p =new_data;
    auto q =first;
    for (size_t i =0; i != size();i++)
        alloc.construct(p++, std::move(*q++));
    free();
    first = new_data;
    blank = p;
    last = first + new_size;
}

StrVec::StrVec (initializer_list<string>il){
    auto new_pair =alloc_move(il.begin(),il.end());
    first = new_pair.first;
    blank = last = new_pair.second;
    
}

StrVec::StrVec (const StrVec &s){
    auto new_data = alloc_copy(s.begin(),s.end());
    first = new_data.first;
    blank = last = new_data.second;
}

StrVec::StrVec(StrVec &&s) noexcept :first(s.first),blank(s.blank),last(s.last){
    s.first = s.blank = s.last = nullptr;
}

StrVec& StrVec:: operator=(const StrVec& s){
    auto new_data = alloc_copy(s.begin(),s.end());
    free();
    first = new_data.first;
    blank = last = new_data.second;
    return *this;
}

StrVec& StrVec::operator=(StrVec &&s) noexcept{
    if (this != &s){
        free();
        first = s.first;
        blank = s.blank;
        last = s.last;
        s.first = s.blank = s.last = nullptr;
    }
    return *this;
}

void StrVec:: push_back(const string &s) &{
    check();
    alloc.construct(blank++,s);
}

void StrVec::push_back(string &&s) &&{
    check();
    alloc.construct(blank++, std::move(s));
}

bool StrVec::reserve (size_t n){
    if (n < size()) return false;
    auto new_data = alloc.allocate(n);
    auto new_last = uninitialized_copy(make_move_iterator(begin()), make_move_iterator(end()),new_data);
    free();
    first = new_data;
    blank = new_last;
    last = first + n;
    return true;
}

void StrVec::resize(size_t n){
    if (n > capacity()){
        reserve(n);
        while(size() < n){
            push_back("");
        }
        return ;
    }
    
    if (n > size()){
        while(size() < n){
            push_back("");
        }
    }
    else {
        while(size() >= n){
            alloc.destroy(--blank);
        }
    }
}

void StrVec::resize(size_t n,const string &s){
    if (n > capacity()){
        reserve(n);
        while(size() < n){
            push_back(s);
        }
        return ;
    }
    if (n > size()){
        while(size() < n){
            push_back(s);
        }
    }
    else {
        while(size() >= n){
            alloc.destroy(--blank);
        }
    }
}

void StrVec::print() const{
    for (auto p =first;p != blank;p++)
        cout<<*p<<" ";
    cout<<endl;
}
