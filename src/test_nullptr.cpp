#include <iostream>
#include <type_traits>

void foo(char *);
void foo(int);

int main(){
    if(std::is_same<decltype(NULL),decltype(0)>::value)
        std::cout << "NULL == 0" << std::endl;
    if(std::is_same<decltype(NULL),decltype((void*)0)>::value)
        std::cout << "NULL == (void*)0" << std::endl;
    if(std::is_same<decltype(NULL),decltype(nullptr)>::value)
        std::cout << "NULL == nullptr" << std::endl;
    if(std::is_integral<decltype(NULL)>::value)
        std::cout << "NULL is integral" << std::endl;
    if(std::is_integral<decltype(nullptr)>::value)
        std::cout << "nullptr is integral" << std::endl;
    if(std::is_pointer<decltype(nullptr)>::value)
        std::cout << "nullptr is pointer" << std::endl;
    if(std::is_pointer<decltype((void*)0)>::value)
        std::cout << "(void*)0 is pointer" << std::endl;

    foo(0);
    foo(nullptr);
    return 0;
}

void foo(char *){
    std::cout << "foo(char*) is called" << std::endl;
}

void foo(int){
    std::cout << "foo(int) is called" << std::endl;
}