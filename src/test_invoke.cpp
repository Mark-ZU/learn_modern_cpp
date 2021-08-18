#include <iostream>
#include <functional>

int f(const int i){
    return i+5;
}

struct S{
    int f(const int i){ return i+5; }
};

int main(){
    std::cout << std::invoke(f, 5) << std::endl;
    std::cout << std::invoke(&f, 4) << std::endl;

    S s;
    std::cout << s.f(3) << std::endl;
    auto fp = &S::f;
    std::cout << (s.*fp)(2) << std::endl;
    std::cout << std::invoke(fp,s,1) << std::endl;
}