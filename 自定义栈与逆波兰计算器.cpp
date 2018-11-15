#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<algorithm>
#include<sstream>


using namespace std;

template<typename T>

class Stack{
private:
    vector<T>* data;
    int len;
    void check(size_t);
    void free();
public:
    Stack():data(new vector<T>),len(0){};
    Stack(initializer_list<T>);
    Stack (const Stack &);
    Stack (Stack &&) noexcept;
    Stack & operator =(const Stack &);
    Stack & operator =(Stack &&) noexcept;
    ~Stack(){ free(); }
public:
    T& operator [](size_t);
    T& top() const;
    void clear();
    void push(const T&) ;
    void push (T &&) ;
    void pop() ;
    bool empty() const;
    void print();
    size_t size() const {return len;}
};


class Caculate{
private:
    stringstream ss;
    map<char,int> m;
    Stack <char> s_op;
    Stack <int> s_num;
    void clear();
    void begin_the_caculate();
    void deal_string();
    void op_1(int &a,int &b,const char &ch);
    void op_2();
    int result();
public:
    Caculate();
    Caculate (const Caculate &c) =delete;
    Caculate& operator =(const Caculate &c) =delete;
    
public:
    void start();
    
};

Caculate::Caculate(){
    m['+']=m['-']=1;
    m['*']=m['/']=m['%']=m['(']=m[')']=2;
    clear();
}

void Caculate::begin_the_caculate(){
    string s;
    cin >> s;
    ss.clear();
    ss.str(s);
}

void Caculate::clear(){
    while (!s_num.empty())
        s_num.pop();
    while (!s_op.empty())
        s_op.pop();
}

void Caculate::op_1(int &a, int &b, const char &ch){
    if (ch =='+')    a += b;
    else if (ch == '-') a = b - a;
    else if (ch == '*') a *= b;
    else if (ch == '/') a = b / a;
    else if (ch == '%') a = b % a;
}

void Caculate:: op_2(){
    char ch = s_op.top();
    while (ch !='(' && !s_op.empty()){
        s_op.pop();
        int a = s_num.top();
        s_num.pop();
        int b = s_num.top();
        s_num.pop();
        op_1(a,b,ch);
        s_num.push(a);
        if (!s_op.empty())
            ch = s_op.top();
    }
    if (!s_op.empty() && s_op.top() == '(')
        s_op.pop();
}

void Caculate::deal_string(){
    char tmp;
    while (ss >> tmp){
        if (tmp >= '0' && tmp <= '9'){
            int n = 0;
            do {
                if (m[tmp]) break;
                n = n * 10;
                n = n + (tmp - '0');
            }
            while (ss >> tmp);
            s_num.push(n);
        }
        if (tmp == ')') op_2();
        else if (m[tmp] == 1){
            if (!s_op.empty() && s_op.top() != '(')
                op_2();
            s_op.push(tmp);
        }
        else if (m[tmp] == 2){
            s_op.push(tmp);
        }
    }
}

int Caculate:: result(){
    int res = s_num.top();
    s_num.pop();
    while (!s_num.empty() && !s_op.empty()){
        op_1(res,s_num.top(),s_op.top());
        s_num.pop();
        s_op.pop();
    }
    return res;
}

void Caculate::start(){
    int T;
    cout<<"please input the number that you want to try 。"<<endl;
    cin >> T;
    while (T--){
        begin_the_caculate();                                          //输入将要计算的字符串
        deal_string();
        cout<<result()<<endl;
    }
}


template<typename T>
Stack<T>::Stack(initializer_list<T> it){
    data = new vector<T>(it.begin(),it.end());
    len = it.size();
}

template<typename T>
Stack<T>::Stack(const Stack<T> &s){
    *data = *(s.data);
    len = s.len;
}

template<typename T>
Stack<T>::Stack(Stack<T> &&s) noexcept:data(s.data),len(s.len){
    s.data = nullptr;
    s.len = 0;
}

template<typename T>
void Stack<T>::free(){
    len = 0;
    if (data != nullptr){
        delete data;
    }
}

template<typename T>
Stack<T>& Stack<T>::operator =(const Stack& s){
    free();
    *data = *(s.data);
    len = s.len;
}

template <typename T>
Stack<T>& Stack<T>::operator =(Stack &&s) noexcept{
    if (this == &s){
        free();
        data = s.data;
        len = s.len;
    }
    s.data = nullptr;
    s.len = 0;
}

template <typename T>
void Stack<T>::check(size_t n){
    if (n > len){
        throw out_of_range("out of range");
    }
    return ;
}

template <typename T>
T& Stack<T>::operator[](size_t n){
    check(n);
    return (*data)[n];
}

template <typename T>
void Stack<T>::push(const T& t) {
    data->push_back(t);
    len++;
    return ;
}

template <typename T>
void Stack<T>::push(T&& t) {
    data->push_back(std::move(t));
    len++;
    return ;
}

template <typename T>
void Stack<T>::pop(){
    data->pop_back();
    len--;
    return ;
}

template <typename T>
bool Stack<T>::empty() const{
    if (data->empty())  return true;
    return false ;
}

template<typename T>
T& Stack<T>::top() const{
    return (*data)[len-1];
}

template<typename T>
void Stack<T>::clear(){
    data->clear();
    len = 0;
    return ;
}

template<typename T>
void Stack<T>::print(){
    for (int i=0;i!=len;i++){
        cout<<(*data)[i]<<" ";
    }
    return ;
}


int main()
{
    Caculate c;
    c.start();
}
