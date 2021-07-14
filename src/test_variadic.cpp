#include <iostream>
using namespace std;

// func
void func(){}
template<typename T,typename... Types>
void func(const T& firstArg, const Types&... args){
    func(args...);
    cout << sizeof...(args) << " " << firstArg << endl;
}

template<typename T>
T maximum(const T& t){
    return t;
}

template<typename T,typename... Types>
T maximum(const T& t,const Types&... args){
    return std::max(t,maximum(args...));
}

int main(){
    func(1,1.2,"abc");
    cout << endl;
    cout << "max : " << maximum(0,11,2,123,12) << endl;
    cout << "max : " << maximum(-1.0,-2.0,-0.8,-1.3) << endl;
    cout << "max : " << maximum(string("a"),string("acc"),string("abb"),string("acd")) << endl;
    return 0;
}