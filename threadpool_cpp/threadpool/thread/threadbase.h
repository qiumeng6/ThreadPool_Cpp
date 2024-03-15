#ifndef THREADBASE_H
#define THREADBASE_H

#include <thread>

namespace thpool {

// 对thread进行包装---->异常安全
// 当主线程存在异常处理的问题时，在catch块和正常流程上都需要添加join()函数
// 否则可能会出现主线程异常退出，而没有等待子线程的情况。
// 采用RAII的思想即可以解决忘记添加join函数的问题。
class ThreadBase{
public:
    ThreadBase(std::thread thread):thread_(std::move(thread)){}
    // ThreadBase(){
    //     int a = 1;
    // };

    virtual ~ThreadBase(){
        if(thread_.joinable()){
            thread_.join();
        }
    }

private:
    std::thread thread_;   //线程
};



} //thpool

#endif // THREADBASE_H