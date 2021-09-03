#include <iostream>
#include <string>

template<typename... Types> class mytuple;
template<> class mytuple<>{};

template<typename Head,typename... Tail>
class mytuple<Head,Tail...>:public mytuple<Tail...>{
public:
    mytuple(){}
    mytuple(const Head& head,const Tail&... tail):my_head(head),mytuple<Tail...>(tail...){
    }
    Head& head(){ return my_head; }
    mytuple<Tail...>& tail(){ return *this; }
protected:
    Head my_head;
};

template<typename... Types>
auto make_mytuple(const Types&... args){
    return mytuple<Types...>(args...);
}

template<int index,typename Head,typename... Tail>
struct __get{
    decltype(auto) get(mytuple<Head,Tail...>& t){
        if constexpr(index == 0){
            return t.head();
        }else{
            return __get<index-1,Tail...>().get(t.tail());
        }
    }
};

template<int index,typename... Types>
decltype(auto) get(mytuple<Types...>& t){
    return __get<index,Types...>().get(t);
}

// get2
template<int index,typename Head,typename... Tail>
struct __get_type;

template<typename Head,typename... Tail>
struct __get_type<0,Head,Tail...>{
    using type = mytuple<Head,Tail...>;
};

template<int index,typename Head,typename... Tail>
struct __get_type{
    using type = typename __get_type<index-1,Tail...>::type;
};

template<int index,typename... Types>
decltype(auto) get2(mytuple<Types...>& t){
    return ((typename __get_type<index,Types...>::type&) t).head();
}

int main(){
    auto t = make_mytuple(std::string("hello"),123,1.2,1.4f);
    auto t2 = mytuple<int,double,std::string>(123,1.2,"world");
    
    t.head() = std::string("newstr");
    // bad
    std::cout << "get : " << get<0>(t) << " " << get<1>(t) << " " << get<3>(t) << std::endl;
    // good
    std::cout << "get2 : " << get2<0>(t2) << " " <<  get2<1>(t2) << " " << get2<2>(t2) << std::endl;

    
    get2<2>(t2) = get2<0>(t);
    get<1>(t2) = get<3>(t);
    get2<1>(t2) = 3.1415;

    std::cout << "aftr assign : " << get2<0>(t) << " == " << get2<2>(t2) << std::endl;
    std::cout << "aftr assign : " << get2<1>(t2) << " != " << get2<3>(t) << std::endl;
    std::cout << "size : " << sizeof(mytuple<long,double>) << std::endl;
}