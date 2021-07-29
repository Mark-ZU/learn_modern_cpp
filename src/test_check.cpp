#include <iostream>
#include <type_traits>

struct A{};
struct B{ float f; };
struct C{ void f(){} };
struct D{ void f(int){} };
struct E{ int f(){return 0;} };
struct F{ private:float f; };

namespace {
    template<typename T,typename=int T::*>        std::true_type  test1(int);
    template<typename T>                          std::false_type test1(...);
    template<typename T,typename=decltype(&T::f)> std::true_type  test2(int);
    template<typename T>                          std::false_type test2(...);
    template<typename T,typename=decltype(T::f)>  std::true_type  test3(int);
    template<typename T>                          std::false_type test3(...);
    template<typename T,typename=decltype(std::declval<T>().f())>     
                                                  std::true_type  test4(int);
    template<typename T>                          std::false_type test4(...);
    template<typename T,typename U=std::decay_t<decltype(std::declval<T>().f())>
    ,typename=std::enable_if_t<std::is_same_v<int,U>>> 
                                                  std::true_type  test5(int);
    template<typename T>                          std::false_type test5(...);
}

template<typename T>
inline constexpr bool check1_v = decltype(::test1<T>(0))::value;
template<typename T>
inline constexpr bool check2_v = decltype(::test2<T>(0))::value;
template<typename T>
inline constexpr bool check3_v = decltype(::test3<T>(0))::value;
template<typename T>
inline constexpr bool check4_v = decltype(::test4<T>(0))::value;
template<typename T>
inline constexpr bool check5_v = decltype(::test5<T>(0))::value;

template<typename T>
void check_f(const char name[]){
    std::cout << name << " " << check1_v<T> << check2_v<T> << check3_v<T> << check4_v<T> << check5_v<T> << std::endl;
}

int main(){
    check_f<A>("A");
    check_f<B>("B");
    check_f<C>("C");
    check_f<D>("D");
    check_f<E>("E");
    check_f<F>("F");
}