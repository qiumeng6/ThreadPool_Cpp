#include <string>
#include <functional>

#include <chrono>

#include "threadpool_cpp/threadpool/threadpool.h"
#include "func.h"


// 参考一下  http://purecpp.cn/detail?id=2286

using namespace thpool;

int main(){
    //warmup
    for(int i = 0; i<100; ++i){
        func2(i);  
    }
    auto startTime = std::chrono::steady_clock::now();
    auto pool = std::make_unique<ThreadPool>();
    std::vector<std::future<std::uint64_t>> futures;
    //std::vector<std::future<int>> futures;
    futures.reserve(numtasks);
    //auto startTime1 = std::chrono::steady_clock::now();
    for(int i = 0; i<numtasks; ++i){
        // lamada 表达式和bind得到的速度不同
        futures[i] = pool.get()->commit(std::bind(Fibonacci, i%10), i%17); //i%17
        //futures[i] = pool.get()->commit(std::bind(func4, 10));
    }
    //auto startTime2 = std::chrono::steady_clock::now();
    for(int i = 0; i<numtasks; i++){
        //std::cout << "thread "<< i << " is " << futures[i].get() << std::endl;  
        futures[i].get(); 
    }
    auto endTime = std::chrono::steady_clock::now();
    //std::cout << "Multi-threaded test took: " << std::chrono::duration_cast<std::chrono::milliseconds>(startTime2 - startTime1).count() << " milliseconds" << std::endl;
    std::cout << "Multi-threaded test took: " << std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count() << " milliseconds" << std::endl;
    return 0;
}