#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <future>
#include <stdexcept> // 异常处理所需的头文件

#include "func.h"

using namespace std;


int main() {
    //warmup
    for(int i = 0; i<100; ++i){
        func2(i);  
    }
    //cout << "Running multi-threaded test with " << numThreads << " threads..." << endl;
    auto startTime = chrono::steady_clock::now();
    std::vector<std::future<std::uint64_t>> futures;
    futures.reserve(numtasks);
    // 创建并启动指定数量的线程
    //thread threads[numtasks];
    for (int i = 0; i < numtasks; ++i) {
        futures.emplace_back(std::async(std::launch::async, Fibonacci, i%10+20));
    }
    // 等待所有线程完成
    for(int i = 0; i<numtasks; i++){
        //std::cout << "thread "<< i << "is " << futures[i].get() << std::endl;
        futures[i].get();  
    }
    auto endTime = chrono::steady_clock::now();
    cout << "Multi-threaded test took: " << chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count() << " milliseconds" << endl;
    return 0;
}