#ifndef CONFIGDEFINE_H
#define CONFIGDEFINE_H

#include <thread>

namespace thpool {

static const int CPU_NUM = (int)std::thread::hardware_concurrency();



// 线程池配置信息
static const int DEFAULT_THREAD_SIZE = (CPU_NUM > 0) ? CPU_NUM : 8;           // 默认主线程个数
static const int MAX_THREAD_SIZE = (DEFAULT_THREAD_SIZE * 2) + 1;             // 最大线程个数

} // thpool




#endif // CONFIGDEFINE_H