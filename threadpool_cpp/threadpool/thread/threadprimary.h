#ifndef THREADPRIMARY_H
#define THREADPRIMARY_H

#include <algorithm>

#include "threadbase.h"
#include "../../basic/exception.h"

namespace thpool{

class ThreadPrimary : public ThreadBase{
protected:
    ThreadPrimary(){
        index_ = -1;
        //pool_threads_ = nullptr;
    }

    // ~ThreadPrimary(){
    //     std::cout << "ThreadPrimary has been destory!" << std::endl;
    // }

    void setThreadPoolInfo(int index,
                           std::vector<ThreadPrimary*>* poolThreads,
                           ThreadPoolConfig* config){
        if(is_init_){
            THROW_EXCEPTION("The threadpool has been initialized ! -->ThreadPrimary::setThreadPoolInfo")
        }
        if(poolThreads == nullptr || config == nullptr){
            THROW_EXCEPTION("poolThreads or config == nullptr! -->ThreadPrimary::setThreadPoolInfo")
        }  
        this->index_ = index;   
        this->pool_threads_ = poolThreads; 
        this->config_ = config;
    }

    void init(){
        if(is_init_){
            THROW_EXCEPTION("The threadpool has been initialized ! -->ThreadPrimary::init")
        }
        done_ = true;
        is_init_ = true;
        thread_ = std::move(std::thread(&ThreadPrimary::run, this));
    }

    void run() {
        if(!is_init_){
            THROW_EXCEPTION("The threadpool has not been initialized ! -->ThreadPrimary::run")
        }
        if (std::any_of(pool_threads_->begin(), pool_threads_->end(),
                    [](ThreadPrimary *thd) { return nullptr == thd; })) {
            std::cout << "thread init has error!" << std::endl;
            return;
        }
        while(done_){
            Task task;
            if(poptask(task)){
                task();
            }else{
                std::unique_lock<std::mutex> lk(thread_mutex_);
                thread_cv_.wait_for(lk, std::chrono::milliseconds(100));
            }
        } 
    }

    void pushtask(Task&& task){
        while(!task_queue_per_thread_.try_push(std::forward<Task>(task))){
            std::this_thread::yield();
        }
        thread_cv_.notify_one();   
    }

    bool poptask(Task& task){
        return task_queue_per_thread_.try_pop(task);
    }


private:
    int index_ {-1};                                // 线程index
    ThreadLocalQueue task_queue_per_thread_;        // 线程的loacl队列
    std::vector<ThreadPrimary*>* pool_threads_;   // 每个主线程都存了pool中所有主线程信息

    friend class ThreadPool;    // 可能会出现包含的问题
};



} // thpool





#endif // THREADPRIMARY_H