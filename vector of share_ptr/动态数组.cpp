/*************************************************************************
	> File Name: 动态数组.cpp
	> Author: wangshuxiao
	> Mail: wsx1128@outlook.com 
	> Created Time: 六 10/13 10:48:25 2018
 ************************************************************************/

#include<iostream>
#include<string>
#include<new>
#include<utility>
#include<algorithm>

using namespace std;
allocator<string>alloc;

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

int main()
{
    StrVec v ({"list","vector","string","which","do","you","want"});
    v.print();
    string s = "iasdasda";
    v.push_back(s);
    v.print();
    cout<<v.size()<<" "<<v.capacity()<<endl;
    cout<<endl;
    
    v.resize(20);
    v.print();
    cout<<v.size()<<" "<<v.capacity()<<endl;
    
    return 0;
}

