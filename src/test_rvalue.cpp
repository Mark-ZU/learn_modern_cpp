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

int main(){
    test();
    test2();
    return 0;
}