/*************************************************************************
	> File Name: n_quene.cpp
	> Author: wangshuxiao
	> Mail: wsx1128@outlook.com 
	> Created Time: Wed 31 Oct 16:22:33 2018
 ************************************************************************/

#include<iostream>
#include<algorithm>
#include<vector>
#include<cmath>

using namespace std;

const int maxn = 15;
int n;
int x[maxn];
int sum=0;

bool place (int k)
{
    int i;
    for (i=1;i!=k;i++)
    {
        if (abs(k-i)==abs(x[k]-x[i])||x[k]==x[i])
            return false;
    }
    return true;
}

int queen(int t)
{
    if (t>n) sum++;
    else
    {
        for (int i=1;i!=n+1;i++)
        {
            x[t]=i;
            if (place(t))
                queen(t+1);
        }
    }
    return sum;
}

int main()
{
    while (cin>>n&&n!=0)
    {
        sum=0;
        cout<<queen(1)<<endl;
    }
    return 0;
}

