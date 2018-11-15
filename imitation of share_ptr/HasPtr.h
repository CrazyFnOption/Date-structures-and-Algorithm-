/*************************************************************************
	> File Name: HasPtr.h
	> Author: wangshuxiao
	> Mail: wsx1128@outlook.com 
	> Created Time: 六 10/13 12:56:21 2018
 ************************************************************************/

#include<iostream>
#include<algorithm>
#include<string>

using namespace std;

template <typename T>
class Hasptr{
private:
    size_t* used;
    T* data;
    void free();
public:
    Hasptr (const T &s= T()):data(new T(s)),used(new size_t(1)){};
    Hasptr (const Hasptr &h);
    Hasptr (Hasptr &&h) noexcept;
    Hasptr& operator=(const Hasptr &h);
    Hasptr& operator=(Hasptr &&h) noexcept;
    Hasptr& operator=(const T& t);
    size_t get(){return *used;};
    T& operator *() {return *data;}
    ~Hasptr(){free();};
};

template<typename T>
Hasptr<T>::Hasptr(const Hasptr& h){
    used = h.used;
    data = h.data;
    ++*used;
}

template<typename T>
Hasptr<T>::Hasptr(Hasptr &&h) noexcept{
    used = h.used;
    data = h.data;
    h.used = h.data = nullptr;
}

template<typename T>
void Hasptr<T>::free(){
    if(--*used==0){
        delete used;
        if (data != nullptr)
            delete data;
    }
}

template<typename T>
Hasptr<T>& Hasptr<T>::operator= (const Hasptr &h){
    free();
    data = h.data;
    used = h.used;
    *used++;
    return *this;
}

template<typename T>
Hasptr<T>& Hasptr<T>::operator= (Hasptr &&h) noexcept{
    free();
    data = h.data;
    used = h.used;
    h.data = h.uesd = nullptr;
    return *this;
}

template<typename T>
Hasptr<T>& Hasptr<T>::operator=(const T& t){
    free();
    data = new T(t);
    used = new size_t(1);
    return *this;
}

int main(){
    Hasptr<string> h{"hallo world"};
    Hasptr<string> h2 =h;
    Hasptr<string> h3 =h;
    h = "jheaf";
    cout<<h.get()<<" "<<h2.get()<<" "<<h3.get()<<endl;
    cout<<*h<<endl;
    cout<<*h2<<endl;
    cout<<*h3<<endl;
}



