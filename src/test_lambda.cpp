#include <iostream>

void test1(){
    std::cout << "test1 : " << std::endl;
    int id = 10;
    auto f1 = [id]() mutable{
        return id++;
    };
    auto f2 = [&id]() mutable{
        return id++;
    };
    id = 40;
    std::cout << id << std::endl << "f : ";
    std::cout << f1() << " " << f2() << " " << f1() << " " << f2() << std::endl;
    std::cout << id << std::endl;
}

void test2(){
    std::cout << "test2 : " << std::endl;
    auto f = [](float a){ 
        return [a]()mutable{
            std::cout << "inside func : " << a << std::endl;
            return a++;
        }; 
    };
    float a = 123.0;
    auto f1 = f(a);
    auto f2 = f(a);
    std::cout << f1() << "\n" << f1() << std::endl;
    std::cout << f2() << std::endl;
}


int main(){
    test1();
    test2();
    return 0;
}