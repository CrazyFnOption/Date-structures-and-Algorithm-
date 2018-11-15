#include "Header.h"
#include<iostream>

using namespace std;

int main()
{
    StrVec v {"list","vector","string","which","do","you","want"};
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
