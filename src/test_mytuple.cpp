#include <iostream>
using namespace std;

template<typename Head,typename... Tail>
class mytuple<Head,Tail...>:private mytuple<Tail>{
    typename Head head(){ return my_head; }
    
protected:
    typename Head my_head;
};

template<typename... Types>
mytuple<Types...> make_mytuple(const Types&... args){

}

int main(){

}