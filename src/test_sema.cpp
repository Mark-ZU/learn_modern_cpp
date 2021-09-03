#include <semaphore>
#include <iostream>
#include <fmt/core.h>
#include <source_location>
#include <string>
#include <string_view>
#include <thread>
#include <chrono>
using namespace std::chrono_literals;
template<typename... Ts>
struct log{
    log(std::string_view s,Ts&&... ts,const std::source_location& lo=std::source_location::current()){
        fmt::print("{}({}:{})`{}`:",lo.file_name(),lo.line(),lo.column(),lo.function_name());
        fmt::print(s,ts...);
    }
};
template<typename... Ts> log(std::string_view s,Ts&&... ts) -> log<Ts...>;

std::counting_semaphore s(0);

void pong(){
    static int count=0;
    // while(!_t.stop_requested()){
    while(true){
        s.acquire();
        log("get {} from pong\n",count++);
        std::this_thread::sleep_for(500ms);
    }
    log("pong get stop request!\n");
}

int main(){
    std::thread t(pong);
    for(int i=0;i<10;i++){
        std::this_thread::sleep_for(300ms);
        log("send {} from main\n",i);
        s.release();
    }
    std::this_thread::sleep_for(3s);
    t.join();
    return 0;
}