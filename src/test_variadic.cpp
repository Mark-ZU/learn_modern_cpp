#include <iostream>
#include <limits>
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

template<typename... Ts>
auto sum(Ts... t){
    typename std::common_type<Ts...>::type res{};
    initializer_list<int>{(res += t, 0)...};
    return res;
}

auto sum2(auto... t){
    return (t+...);
}

template<typename... Ts>
auto min(Ts... t){
    typename std::common_type<Ts...>::type res{numeric_limits<decltype(res)>::max()};
    initializer_list<int>{(res = (res > t)?t:res,0)...};
    return res;
}
int main(){
    func(1,1.2,"abc");
    cout << endl;
    cout << "max : " << maximum(0,11,2,123,12) << endl;
    cout << "max : " << maximum(-1.0,-2.0,-0.8,-1.3) << endl;
    cout << "max : " << maximum(string("a"),string("acc"),string("abb"),string("acd")) << endl;
    cout << endl;
    cout << sum(1, 1.0, 1.12, 3) << endl;
    cout << sum2(1, 1.0, 1.12, 3) << endl;
    cout << min(1.0,2,0,-1.2,-100000) << endl;
    return 0;
}