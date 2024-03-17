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

## TODO

* [ ]  异常处理优化
* [ ]  thread_local机制优化
* [ ]  lock-free机制优化
* [ ]  work-stealing机制优化
* [ ]  测试用例
