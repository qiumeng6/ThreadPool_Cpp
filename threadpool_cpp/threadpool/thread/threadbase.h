#ifndef THREADBASE_H
#define THREADBASE_H

#include <thread>

#include "threadpool_cpp/threadpool/threadpoolconfig.h"
#include "threadpool/queue/thread_local_queue.h"
#include "threadpool/queue/safe_queue.h"
#include "threadpool/task/task.h"

#include <iostream>

namespace thpool {

// 对thread进行包装---->异常安全
// 当主线程存在异常处理的问题时，在catch块和正常流程上都需要添加join()函数
// 否则可能会出现主线程异常退出，而没有等待子线程的情况。
// 采用RAII的思想即可以解决忘记添加join函数的问题。
class ThreadBase{
protected:
    //ThreadBase(std::thread thread):thread_(std::move(thread)){}
    ThreadBase(){
        is_init_ = false; 
    }

    void destory(){

    }

    virtual ~ThreadBase(){
        done_ = false;
        if(thread_.joinable()){
            thread_.join();
        }
        
        is_init_ = false;
        //is_running_ = false;
        //total_task_num_ = 0;
    }

protected:
    bool done_;                                                        // 线程状态标记  为true时循环执行获取任务
    bool is_init_;                                                     // 标记初始化状态
    //bool is_running_;                                                  // 是否正在执行
    //unsigned long total_task_num_ = 0;                                 // 处理的任务的数字
    // 当把这个锁放在子类的时候，析构函数会非常慢，目前还不知道为什么？？
    std::mutex thread_mutex_;                       // 主线程锁
    std::condition_variable thread_cv_;
    ThreadPoolConfig* config_ = nullptr;                               // 每个线程都存了config
    std::thread thread_;   //线程
};



} //thpool

#endif // THREADBASE_H