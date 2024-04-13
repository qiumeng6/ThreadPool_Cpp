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

    void push(Task&& task) {
        while (true) {
            if (mutex_.try_lock()) {
                queue_.push(std::move(task));
                mutex_.unlock();
                break;
            } else {
                std::this_thread::yield();
            }
        }
    }

    bool try_pop(Task& task) {
        // 这里不使用raii锁，主要是考虑到多线程的情况下，可能会重复进入
        bool result = false;
        // print_thread_id();
        if (mutex_.try_lock()) {
            if (!queue_.empty()) {
                task = std::move(queue_.front());    // 从前方弹出
                queue_.pop();
                result = true;
            }
            mutex_.unlock();
        }

        return result;
    }

private:
    std::queue<Task> queue_;
};




} // thpool





#endif // THREAD_LOCAL_QUEUE_H