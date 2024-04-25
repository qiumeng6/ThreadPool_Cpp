#include <iostream>
#include <thread>

int main() {
    unsigned int num_threads = std::thread::hardware_concurrency();
    if (num_threads == 0) {
        std::cout << "Unable to determine the number of concurrent threads supported." << std::endl;
    } else {
        std::cout << "Number of concurrent threads supported: " << num_threads << std::endl;
    }
    return 0;
}