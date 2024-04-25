#include <iostream>

#include "threadpool_cpp/threadpool/threadpool.h"
#include "threadpool_cpp/threadpool/threadpoolconfig.h"
#include "thread/threadbase.h"
#include "task/task.h"
#include "queue/safe_queue.h"

#include "../basic/exception.h"

namespace thpool {


ThreadPool::ThreadPool(const ThreadPoolConfig& config){
    //cur_index_ = 0;
    is_init_ = false;
    //input_task_num_ = 0;
    this->setConfig(config);
    this->init();
}

ThreadPool::~ThreadPool(){
    for(ThreadPrimary*& pr : primary_threads){
        if(pr != nullptr){
            delete pr;
            pr = nullptr;
        }
    }
    primary_threads.clear();
    is_init_ = false;
}


void ThreadPool::init(){
    if(is_init_){
        THROW_EXCEPTION("The threadpool has been initialized and config do not be allowed to revise ! -->ThreadPool::init")
    }
    primary_threads.reserve(config_.default_thread_size_);
    for(int i = 0; i < config_.default_thread_size_; i++){
        ThreadPrimary* th = new ThreadPrimary();
        th->setThreadPoolInfo(i, &primary_threads, &config_);
        th->init();
        primary_threads.emplace_back(th);
    }
}


// 当前用来分配线程号，以后改为将线程分配到不同的任务队列。
// int ThreadPool::dispatch(int origindex){
//     int realindex = 0;
//     realindex = cur_index_++;
//     return realindex;
// }



void ThreadPool::setConfig(const ThreadPoolConfig& config){
    if(is_init_){
        THROW_EXCEPTION("The threadpool has been initialized and config do not be allowed to revise !-->ThreadPool::setConfig")
    }
    this->config_ = config;
}


} //thpool


