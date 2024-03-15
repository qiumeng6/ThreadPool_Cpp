#ifndef SAFE_QUEUE_H
#define SAFE_QUEUE_H

#include <queue>
#include <memory>

#include "queue_object.h"

namespace thpool {

// ref: 《c++ 并发编程实战》 p185
template<typename T>
class SafeQueue : public QueueBase {
public:

    SafeQueue() = default;

    SafeQueue(const SafeQueue&) = delete;
    const SafeQueue& operator=(const SafeQueue&) = delete;

    /**
     * @brief push the value
    */
    void push(T&& value){
        std::unique_ptr<T> ptr = std::make_unique<T>(std::move(value));
        std::lock_guard<std::mutex> lg(mutex_);
        task_queue_.push(std::move(ptr));
        cv_.notify_one(); 
    }

    /**
     * @brief 阻塞式弹出元素，即当队列内有元素时才会弹出，否则一直阻塞
     * @param 弹出的值通过 value引用的方式传出去
    */
    void wait_and_pop(T& value){
        std::lock_guard<std::mutex> lg(mutex_);
        cv_.wait(lg, [this]{return !task_queue_.empty();});
        value = std::move(*task_queue_.front());
        task_queue_.pop();
    }

    /**
     * @brief 阻塞式弹出元素，即当队列内有元素时才会弹出，否则一直阻塞
     * @param 通过unique_ptr 的方式将队列内的数据弹出
    */
    std::unique_ptr<T> wait_and_pop(){
        std::lock_guard<std::mutex> lg(mutex_);
        cv_.wait(lg, [this]{return !task_queue_.empty();});
        std::unique_ptr<T> ptr = task_queue_.front();
        task_queue_.pop();
        return ptr; 
    }

    /**
     * @brief 非阻塞式弹出，即当队列为empty时，返回false，并不会阻塞线程
     * @param 数据通过value的引用返回，同时pop成功则返回true，失败则返回false
    */
    bool try_pop(T& value){
        std::lock_guard<std::mutex> lg(mutex_);
        if(task_queue_.empty()){
            return false;
        }
        value = std::move(*task_queue_.front());
        task_queue_.pop();
        return true;
    }

    /**
     * @brief 非阻塞式弹出，即当队列为empty时，返回false，并不会阻塞线程
     * @param 数据通过unique_ptr返回，同时pop成功则返回unique_ptr，失败则返回空的unique_ptr
    */
    std::unique_ptr<T> try_pop(){
        std::lock_guard<std::mutex> lg(mutex_);
        if(task_queue_.empty()){
            return std::unique_ptr<T>();
        }
        std::unique_ptr<T> ptr = std::move(task_queue_.front());
        task_queue_.pop();
        return ptr;
    }

    bool empty(){
        std::lock_guard<std::mutex> lg(mutex_);
        return task_queue_.empty();
    }

private:
    std::queue<std::unique_ptr<T>> task_queue_; // 异常安全的

};

} // thpool




#endif // SAFE_QUEUE_H