#ifndef THREADPRIMARY_H
#define THREADPRIMARY_H

#include "threadbase.h"
#include "../../basic/exception.h"

namespace thpool{

class ThreadPrimary : public ThreadBase{
protected:
    ThreadPrimary(){
        index_ = -1;
        //pool_threads_ = nullptr;
    }

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
        //this->pool_threads_ = poolThreads; 
        this->config_ = config;
    }

    void init(){
        if(is_init_){
            THROW_EXCEPTION("The threadpool has been initialized ! -->ThreadPrimary::init")
        }
        is_init_ = true;
        thread_ = std::move(std::thread(&ThreadPrimary::run, this));
    }

    void run() {
        if(!is_init_){
            THROW_EXCEPTION("The threadpool has not been initialized ! -->ThreadPrimary::run")
        }
        while(done_){
            processTask();
        }
        
    }

    void processTask(){
        Task task;
        if(poptask(task)){
            runTask(task);   
        }else{
            std::this_thread::yield;
        }
    }

    bool poptask(Task& task){
        return task_queue_per_thread_.try_pop(task);
    }


private:
    int index_ {-1};                               // 线程index
    ThreadLocalQueue task_queue_per_thread_;        // 线程的loacl队列
    //std::vector<ThreadPrimary*>* pool_threads_;    // 每个主线程都存了pool中所有主线程信息

    friend class ThreadPool;    // 可能会出现包含的问题
};



} // thpool





#endif // THREADPRIMARY_H