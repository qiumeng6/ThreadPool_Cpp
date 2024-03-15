#ifndef THREAD_POOL_CONFIG_H
#define THREAD_POOL_CONFIG_H

#include "configdefine.h"

namespace thpool {

struct ThreadPoolConfig {
    int default_thread_size_ = DEFAULT_THREAD_SIZE;

};

} // thpool






#endif //THREAD_POOL_CONFIG_H