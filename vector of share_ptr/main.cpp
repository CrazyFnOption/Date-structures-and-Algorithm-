

#include "StrBlob.h"
#include<iostream>

using namespace std;

int main()
{
    StrBlob<string> b1;
    {
        StrBlob<string> b2 {"a","an","the"};
        b1 = b2;
        b2.push("about");
        cout<<b2.size()<<endl;
    }
    cout << b1.size()<<endl;
    cout<<b1.front()<<" "<<b1.back()<<endl;
    
    const StrBlob<string> b3=b1;
    cout<<b3.front()<<" "<<b3.back()<<endl;
    
    for (auto it =b1.begin();it != b1.end();++it){
        cout<< *it <<endl;
    }
    return 0;
}

