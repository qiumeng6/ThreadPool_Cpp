#include <string>
#include <functional>

#include "threadpool_cpp/threadpool/threadpool.h"

int add(int i, int j) {
    for(int x=0; x<10000; x++){
        i = i + j ;
        if(x%50 == 0) std::cout << i << std::endl; 
    }
    return i;
}

static float minusBy5(float i) {
    for(int x=0; x<10000; x++){
        i = i - 4.3f;
        if(x%50 == 0) std::cout << i << std::endl; 
    }
    return i;
}


class MyFunction {
public:
    std::string concat(std::string& str) const {
        return info_ + str;
    }

    static int multiply(int i, int j) {
        return i * j;
    }

private:
    std::string info_ = "MyFunction : ";
};



using namespace thpool;

void test_1(ThreadPool* tp){
    int i = 6, j = 3;
    std::string str = "5";
    MyFunction mf;

    auto r1 = tp->commit([i, j] { return add(i, j); });    // 可以通过lambda表达式传递函数
    std::future<float> r2 = tp->commit(std::bind(minusBy5, 8.5f));    // 可以传入任意个数的入参
    auto r3 = tp->commit(std::bind(&MyFunction::concat, mf, str));    // 返回值可以是任意类型
    std::future<int> r4 = tp->commit([i, j] { return MyFunction::multiply(i, j); });    // 返回值实际上是std::future<T>类型

    std::cout << r1.get() << std::endl;    // 返回值可以是int类型
    std::cout << r2.get() << std::endl;    // 等待r2对应函数执行完毕后，再继续执行。不调用get()为不等待
    std::cout << r3.get() << std::endl;    // 返回值也可是string或其他任意类型
    std::cout << r4.get() << std::endl;
    
}

int main(){
    auto pool = std::make_unique<ThreadPool>();
    test_1(pool.get());
    return 0;
}