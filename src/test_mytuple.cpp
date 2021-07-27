#include <iostream>
#include <string>

template<typename... Types> class mytuple;
template<> class mytuple<>{};

template<typename Head,typename... Tail>
class mytuple<Head,Tail...>:private mytuple<Tail...>{
public:
    mytuple(){}
    mytuple(const Head& head,const Tail&... tail):my_head(head),mytuple<Tail...>(tail...){
    }
    Head head(){ return my_head; }
protected:
    Head my_head;
};

template<typename... Types>
auto make_mytuple(const Types&... args){
    return mytuple<Types...>(args...);
}

int main(){
    auto t = make_mytuple(std::string("abc"),123,1.2,1.2f);
    auto t2 = mytuple<int,double,std::string>(123,1.2,"abc");
    std::cout << t.head() << std::endl;
    std::cout << t2.head() << std::endl;
}