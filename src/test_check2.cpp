#include <concepts>
#include <iostream>

struct A{};
struct B{ float f; };
struct C{ void f(){} };
struct D{ void f(int){} };
struct E{ int f(){return 0;} };
struct F{ private:float f; };

template<typename T>
concept t1 = requires(int T::* t){ t; };
template<typename T>
concept t2 = requires(T t){ &T::f; };
template<typename T>
concept t3 = requires(T t){ T::f; };
template<typename T>
concept t4 = requires(T t){ t.f(); };
template<typename T>
concept t5 = requires(T t){ { t.f() } -> std::same_as<int>; };
template<typename T>
concept container = requires(T t){
    typename T::value_type;
    typename T::size_type;
    typename T::allocator_type;
    typename T::iterator;
    typename T::const_iterator;
    t.size();
    t.begin();
    t.end();
    t.cbegin();
    t.cend();
};

template<typename T>
void check(const char name[]){
    std::cout << name << " " << t1<T> << t2<T> << t3<T> << t4<T> << t5<T> << std::endl;
}

int main(){
    check<int>("i");
    check<A>("A");
    check<B>("B");
    check<C>("C");
    check<D>("D");
    check<E>("E");
    check<F>("F");
}