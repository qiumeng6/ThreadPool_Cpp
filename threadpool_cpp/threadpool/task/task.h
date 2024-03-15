#ifndef TASK_H
#define TASK_H

#include <memory>
#include <iostream>

namespace thpool {

/**
 * @brief avoid using template when TaskImpl is used as member variable
 * in the Task class.
*/
class TaskImplBase {
public:
    explicit TaskImplBase() = default;
    virtual ~TaskImplBase() = default;
    virtual void call() = 0;
};

template<typename F>
class TaskImpl : public TaskImplBase{
public:
    /**
     * @brief 
     * 1. 这里不确定是不是万能引用，但是当左值传过来的时候编译没有报错
     * 2. cannot bind non-const lvalue reference of type ..... to an rvalue of type 原因：
     *    当左值传入时，F是左值引用，即func_变量为左值引用类型，但是std::move把func变成右值后再赋值是被编译器禁止的
     *    所以，直接将func 赋值给 func_ 也是对的
    */
    explicit TaskImpl(F&& func) 
        : func_(std::move(func)) {}
    // explicit TaskImpl(F& func) : func_(func) { std::cout << "2" << std::endl;}

    void call() override {func_();}

private:
    F func_;     // 回调函数
};

class Task {
public:
    Task() = default;
    
    /**
     * @brief 使用F&& 保持原本的右值属性
     * && && -> &&
     * & && -> &
     * & & -> &
     * && & -> &
     * 1. f即使以右值引用形式传递近来，到了构造函数中，会变为左值
     * 2. 所以使用完美转发，保持其左值或右值的性质
     * 3. new TaskImpl<F&&>(std::forward<F>(f)) 会触发调用处的万能折叠
    */
    template<typename F>
    Task(F&& f, int priority = 0)
        : impl_(new TaskImpl<F>(std::forward<F>(f)))
        , priority_(priority) {}

    Task(Task&& t)
        : impl_(std::move(t.impl_))
        , priority_(t.priority_) {}
    
    Task& operator=(Task&& t){
        impl_ = std::move(t.impl_);
        priority_ = t.priority_;
        return *this;
    }

    void operator()(){
        if(impl_){
            impl_->call();
        }
    }

    Task(Task& t) = delete;
    Task& operator=(Task& t) = delete;


private:
    int priority_ = 0;     // 任务优先级
    std::unique_ptr<TaskImplBase> impl_ = nullptr;

};

} // thpool



#endif // TASK_H