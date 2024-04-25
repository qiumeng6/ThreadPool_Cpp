#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <vector>
#include <atomic>
#include <future>

//#include "threadpool/thread/threadbase.h"
#include "threadpool/thread/threadprimary.h"
#include "threadpool/queue/safe_queue.h"
#include "threadpool/task/task.h"
#include "threadpoolconfig.h"

#include <chrono>

namespace thpool {

class ThreadPool {
public:
    explicit ThreadPool(const ThreadPoolConfig& config = ThreadPoolConfig());
    
    void setConfig(const ThreadPoolConfig& config);

    void init();

    //void run();

    int dispatch(int origindex);

    template<typename FunctionType>
    std::future<typename std::result_of<FunctionType()>::type> 
    commit(const FunctionType& func, int index=0){
    typedef typename std::result_of<FunctionType()>::type result_type;
    std::packaged_task<result_type()> task(func);
    std::future<result_type> result(task.get_future());
    // int realindex = dispatch(index);
    // std::cout << index << std::endl;
    //auto startTime1 = std::chrono::steady_clock::now();
    primary_threads[index]->pushtask(std::move(task));
    //auto startTime2 = std::chrono::steady_clock::now();
    //std::cout << "Multi-threaded test "<< flag++ << " : " << std::chrono::duration_cast<std::chrono::milliseconds>(startTime2 - startTime1).count() << " milliseconds" << std::endl;
    return result;
    }

    ~ThreadPool();



private:
    // int flag = 0;
    // std::atomic<bool> done;
    bool is_init_ {false};              // 线程池是否初始化
    // int cur_index_ = 0;                 // 记录放入的线程数量
    // unsigned long input_task_num_ = 0;  // 放入的任务的个数
    // SafeQueue<Task> task_queue_;           // 全局任务队列
    std::vector<ThreadPrimary*> primary_threads;      // 存储线程池中所有的线程
    ThreadPoolConfig config_;            // 线程池配置
};

} // thpool

#endif // THREAD_POOL_H