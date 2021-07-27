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
    mytuple<Tail...>& tail(){ return *this; }
protected:
    Head my_head;
};

template<typename... Types>
auto make_mytuple(const Types&... args){
    return mytuple<Types...>(args...);
}

template<int index,typename... Types>
struct __get;

template<typename... Types>
struct __get<0,Types...>{
    auto get(mytuple<Types...>& t){
        return t.head();
    }
};

template<int index,typename Head,typename... Tail>
struct __get<index,Head,Tail...>{
    auto get(mytuple<Head,Tail...>& t){
        return __get<index-1,Tail...>().get(t.tail());
    }
};

template<int index,typename... Types>
auto get(mytuple<Types...>& t){
    return __get<index,Types...>().get(t);
}

int main(){
    auto t = make_mytuple(std::string("abc"),123,1.2,1.4f);
    auto t2 = mytuple<int,double,std::string>(123,1.2,"abc");
    std::cout << t.head() << std::endl;
    std::cout << t2.head() << std::endl;
    
    // 胡乱实现的，效率很差
    std::cout << get<0>(t) << " " << get<1>(t) << " " << get<3>(t) << std::endl;
}