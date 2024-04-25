#ifndef FUNCH
#define FUNCH

#include <cstdint>


static int numtasks = 512; // 指定要使用的线程数
double func1(int id);
double func2(int id);
double func3(int id);
int func4(int reps_o);

std::uint64_t Fibonacci(std::uint64_t number);


#endif // FUNCH