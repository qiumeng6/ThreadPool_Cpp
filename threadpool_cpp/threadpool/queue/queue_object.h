#ifndef QUEUE_OBJECT_H
#define QUEUE_OBJECT_H

#include <mutex>
#include <condition_variable>

namespace thpool {

class QueueBase {
protected:
    std::mutex mutex_;
    std::condition_variable cv_;
};

} // thpool



#endif // QUEUE_OBJECT_H