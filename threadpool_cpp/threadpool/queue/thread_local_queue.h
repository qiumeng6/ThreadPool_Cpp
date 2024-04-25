#ifndef THREAD_LOCAL_QUEUE_H
#define THREAD_LOCAL_QUEUE_H


#include <queue>
#include <mutex>
#include <thread>
#include <deque>

#include <sstream>

#include "queue_object.h"
#include "threadpool/task/task.h"


void print_thread_id() {  

    // 获取当前线程的ID  

    std::thread::id current_thread_id = std::this_thread::get_id();  


    std::cout << "Current thread ID: " << current_thread_id << std::endl;  

}  

namespace thpool {

class ThreadLocalQueue : public QueueBase{
public:
    ThreadLocalQueue() = default;

    bool try_push(Task&& task) {
        bool result = false;
        if (mutex_.try_lock()) {
            deque_.emplace_back(std::forward<Task>(task));
            mutex_.unlock();
            result = true;
        }
        return result;
    }

    bool try_pop(Task& task) {
        // 这里不使用raii锁，主要是考虑到多线程的情况下，可能会重复进入
        bool result = false;
        // print_thread_id();
        if (!deque_.empty() && mutex_.try_lock()) {
            if (!deque_.empty()) {
                task = std::move(deque_.front());    // 从前方弹出
                deque_.pop_front();
                result = true;
            }
            mutex_.unlock();
        }
        return result;
    }

private:
    std::deque<Task> deque_;
};




} // thpool





#endif // THREAD_LOCAL_QUEUE_H