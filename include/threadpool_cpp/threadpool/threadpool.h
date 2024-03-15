#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <vector>
#include <atomic>
#include <future>

#include "threadpool/thread/threadbase.h"
#include "threadpool/queue/safe_queue.h"
#include "threadpool/task/task.h"
#include "threadpoolconfig.h"

namespace thpool {

class ThreadPool {
public:
    explicit ThreadPool();
    
    // void setConfig(const ThreadPoolConfig& config);

    void init();

    void run();

    template<typename FunctionType>
    std::future<typename std::result_of<FunctionType()>::type> 
    commit(const FunctionType& func){
    typedef typename std::result_of<FunctionType()>::type result_type;
    std::packaged_task<result_type()> task(func);
    std::future<result_type> result(task.get_future());

    task_queue_.push(std::move(task));
    return result;
    }

    ~ThreadPool();



private:
    std::atomic<bool> done;
    // bool is_init_ {false};              // 线程池是否初始化
    // int cur_index_ = 0;                 // 记录放入的线程数量
    // unsigned long input_task_num_ = 0;  // 放入的任务的个数
    SafeQueue<Task> task_queue_;           // 任务队列
    std::vector<ThreadBase*> threads;      // 存储线程池中所有的线程
    ThreadPoolConfig config_;            // 线程池配置
};

} // thpool

#endif // THREAD_POOL_H