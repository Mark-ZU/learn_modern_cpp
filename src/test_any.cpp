#include <any>
#include <iostream>
#include <string>
int main(){
    std::any a = 1;
    a = std::string{"Hello"};
    if(a.type() == typeid(1)){
        std::cout << "int" << std::endl;
    }else if(a.type() == typeid(std::string{"abc"})){
        std::cout << "string" << std::endl;
    }
    std::cout << a.type().name() << std::endl;
}
