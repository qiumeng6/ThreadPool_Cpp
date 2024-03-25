# ThreadPool_Cpp

本项目参考“CThreadPool” 用于一步步学习博客中的相关优化，仅学习目的。

## 线程池库使用

*编译*

```
cd ThreadPool_Cpp
mkdir build
cd build
cmake ..
make
```

*调用*

* test 文件夹中的test.cpp 文件用于测试线程池功能
* 生成的可执行文件位于build/test文件夹下
* 生成的动态库位于build/threadpool

## 更新日志

2024/01/28

已经完成 task class  safe_queue class
调整了项目目录并完成基本的cmakelist框架（仍有改进的地方）
项目目录中，include中只包含对外的头文件
正在完成最基本的 threadpool class 编写

2024/03/15
完成线程池的v1 版本

简单的逻辑  创建线程池--->通过commit函数添加任务 ---> so easy

## v1.0 版本的测试总结


| 调用方法   | 2048tasks | 1024tasks | 512tasks | 256tasks |
| ---------- | --------- | --------- | -------- | -------- |
| std::async | 38ms      | 20ms      | 10ms     | 2ms      |
| threadpool | 7ms       | 7ms       | 4ms      | 1ms      |

1. 在写测试用例时，我们发现每个线程的计算任务较轻时，才会体现出线程池性能。
   在v1版本的测试用例中，demo1为std::async异步第调用的线程,demo2为线程池版本，线程池中线程数量固定为17
   计算1-10的Fibonacci，实验数据如上表。
2. 可以发现，随着task数量的减少，线程池“性价比降低”
3. 注：当每个线程上分配的计算任务计算时间较长时，threadpool性能 < std::async

## TODO

* [ ]  异常处理优化
* [ ]  thread_local机制优化
* [ ]  lock-free机制优化
* [ ]  work-stealing机制优化
* [X]  测试用例   -----> 使用更多的测试例子
* [ ]  在master分支，整理一下代码
