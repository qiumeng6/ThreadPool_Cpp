#include "functional"
#include "iostream"
#include "threadpool/task/task.h"

float func(float a, float b){
    return a + b;
}

int main(){
    // auto function = std::bind(func, 1.0f, 2.0f);
    thpool::Task task(std::bind(func, 1.0f, 2.0f));
    float t = task.test();
    std::cout << t << std::endl;
    return 0;
}