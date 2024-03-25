#include <iostream>

#include "threadpool_cpp/threadpool/threadpool.h"
#include "threadpool_cpp/threadpool/threadpoolconfig.h"
#include "thread/threadbase.h"
#include "task/task.h"
#include "queue/safe_queue.h"

#include "../basic/exception.h"

namespace thpool {

ThreadPool::ThreadPool():done(false){
    try{
        init();
    }catch(...){
        done = true;
        throw;
    }
}

ThreadPool::~ThreadPool(){
    done = true;
    for(ThreadBase* thread : threads){
        delete thread;
    }
}


void ThreadPool::init(){
    threads.reserve(config_.default_thread_size_);
    for(int i = 0; i < config_.default_thread_size_; i++){
        ThreadBase* th = new ThreadBase(std::move(std::thread(&ThreadPool::run, this)));
        threads.emplace_back(th);
    }
}

void ThreadPool::run(){
    while(!done){
        Task task;
        if(task_queue_.try_pop(task)){
            task();
        }else{
            std::this_thread::yield();
        }
    }
}


// void ThreadPool::setConfig(const ThreadPoolConfig& config){
//     if(is_init_){
//         THROW_EXCEPTION("The threadpool has been initialized and config do not be allowed to revise !")
//     }
//     this->config_ = config;
// }


} //thpool


