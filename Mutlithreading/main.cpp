#include <iostream>
#include <vector>
#include <future>
#include <cstdint>
#include <algorithm>
#include <functional>
#include <cmath>

using const_iterator = std::vector<bool>::const_iterator;
using Function = std::function<uint64_t(std::vector<bool> &, uint64_t)>;

uint64_t num_of_ones(const_iterator first, const_iterator last) {
    uint64_t res = 0;
    std::for_each(first, last, [&res](bool i) { res += i; });
    return res;
}

void set_random_num(std::vector<bool> &num) {
    srand(time(nullptr));
    uint64_t control_value = 0;
    for (auto n : num) {
        n = rand() % 2;
        if (n) ++control_value;
    }
    std::cout << "CONTROL VALUE: " << control_value << std::endl;
    std::cout << std::endl;
}

uint64_t accumulate(std::vector<bool> &num, uint64_t num_of_threads) {
    std::vector<std::future<uint64_t>> threads;
    uint64_t res = 0;

    uint64_t size_of_piece = num.size() / num_of_threads;
    uint64_t remainder = num.size() % num_of_threads;

    auto first = num.cbegin();
    auto last = num.cbegin() + size_of_piece;

    for (std::size_t i = 0; i < num_of_threads; ++i) {
        if (remainder) {
            ++last;
            --remainder;
        }
        threads.emplace_back(std::async(std::launch::async, num_of_ones, first, last));
        first = last;
        last += size_of_piece;
    }

    for (auto &t : threads) {
        res += t.get();
    }

    return res;
}

void print_execution_time(Function f, std::vector<bool> &num, uint64_t num_of_threads) {
    auto start = std::chrono::steady_clock::now();
    auto res = f(num, num_of_threads);
    auto end = std::chrono::steady_clock::now();

    std::chrono::duration<double> time = end - start;

    std::cout << "Count of threads: " << num_of_threads << std::endl;
    std::cout << "Works " << time.count() << " seconds " << std::endl;
    std::cout << "Result: " << res << " ones" << std::endl;
    std::cout << std::endl;
}

int main() {
    std::vector<bool> value(std::pow(10, 6));
    set_random_num(value);

    print_execution_time(accumulate, value, 1);
    print_execution_time(accumulate, value, 2);
    print_execution_time(accumulate, value, 3);
    print_execution_time(accumulate, value, 4);
    print_execution_time(accumulate, value, 5);
    print_execution_time(accumulate, value, 6);
    print_execution_time(accumulate, value, 7);
    print_execution_time(accumulate, value, 8);

    return 0;
}
