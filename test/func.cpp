#include "func.h"

#include <iostream>
#include <cmath>


double func1(int id){
    double result = 0;
    for (int i = 0; i < 2000000000; ++i) {
        result = sqrt(i) * sqrt(i) - i + (i+1)/2;
    }
    //std::this_thread::sleep_for(std::chrono::seconds(2));
    //std::cout << "Thread " << id << " finished." << std::endl;
    return result;
}

double func2(int id){
    double result = 0;
    for (int i = 0; i < 2000; ++i) {
        result = sqrt(i) - i + (i+1)/2;
    }
    //std::this_thread::sleep_for(std::chrono::seconds(2));
    //std::cout << "Thread " << id << " finished." << std::endl;
    return result;
}

double func3(int id){
    double result = 0;
    for (int i = 0; i < 2000000000; ++i) {
        result = i*i - i - (i+1)/2;
    }
    //std::this_thread::sleep_for(std::chrono::seconds(2));
    //std::cout << "Thread " << id << " finished." << std::endl;
    return result;
}

std::uint64_t Fibonacci(std::uint64_t number) {
  return number < 2 ? 1 : Fibonacci(number - 1) + Fibonacci(number - 2);
}

int func4(int reps_o){
    int x = 0;
    int reps = reps_o + (reps_o +(rand()%5));
    for(size_t j = 0; j<reps; j++){
        x = x + reps;
    }
    return x; 
}