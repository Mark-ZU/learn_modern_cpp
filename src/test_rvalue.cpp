#include <iostream>
#include <string>
using namespace std;

class MyString{
public:
    MyString(){
        cout << "mystring default ctor" << endl;
    }
    MyString(const MyString& str){
        cout << "mystring lvalue copy ctor" << endl;
    }
    MyString(MyString&& str){
        cout << "mystring rvalue move ctor" << endl;
    }
    virtual ~MyString(){
        cout << "mystring dtor" << endl;
    }
private:
};

void test(){
    string s1("Hello");
    string s2("World");
    
    s1 + s2 = s2;
    cout << "res - s1 : " << s1 << ",s2 : " << s2 << endl;
    
    string() = s2;
    
    return;
}

void test2(){
    MyString s1;
    MyString s2(s1);
    MyString s3(std::move(s1));
}

struct A{
    int a;
};
void f(A&&){ cout << "f A&&" << endl; }
void f(A&){ cout << "f A&" << endl; }
void f(const A&){ cout << "f const A&" << endl; }
void hello(A&& a){ cout << "hello A&&" << endl; f(std::forward<A>(a)); }
void hello(const A& a){ cout << "hello A&" << endl; f(a); }

void test3(){
    cout << "\ntest3 : " << endl;
    auto a = A{};
    auto&& b = A{};
    cout << "B==A&  " << (std::is_same_v<decltype(b),A&>) << "\n";
    cout << "B==A&& " << (std::is_same_v<decltype(b),A&&>) << "\n";
    hello(a);
    hello(b);
    hello(std::move(a));
    hello(A{});
}

int main(){
    test();
    test2();
    test3();
    return 0;
}