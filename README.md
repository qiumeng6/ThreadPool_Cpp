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

2024/04/13

完成thread_loacl队列，即多线程多队列，但是测试后性能不及v1版本，目前还没有找到问题。

以下为可能的思考

1. commit的时候比较耗时
2. 学习一下c++性能分析软件
3. 测试用例的问题
4. 需要结合偷盗机制

2024/04/25

1. 参考nndeploy中线程池的设计进行thread_loacl的微调，发现有效，后面需要对比这个版本和上个版本区别在哪里？
2. 修改后的代码似乎在析构时出现问题，程序计算完成后退出很慢，目前不知道为什么？
3. 经过测试后，速度比std::async 和 线程池初始版略快，但是仍存在两个问题：（1）运行性能不稳定，第一次可能很快下一次可能就很慢（2）任务时间稍长时，对比std::async就完全没有优势。

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

## v1.1 版本的测试总结（thread_local）


| 调用方法     | 2048tasks | 1024tasks | 512tasks | 256tasks |
| ------------ | --------- | --------- | -------- | -------- |
| std::async   | 38ms      | 20ms      | 10ms     | 2ms      |
| threadpool   | 7ms       | 7ms       | 4ms      | 1ms      |
| thread_local | 2ms       | 1ms       | ----     | ------   |

1. 仍然测试用例计算时间稍长性能不佳的问题
2. thread_local 性能不稳定，有时会跳出102ms/101ms的时间
3. 需要对code再仔细检查一下，develop分支的代码存在问题，暂时性提交

## TODO

* [ ]  异常处理优化
* [ ]  thread_local机制优化
* [ ]  lock-free机制优化
* [ ]  work-stealing机制优化
* [X]  测试用例   -----> 寻找更科学的线程池测试方法
* [ ]  在master分支，整理一下代码
