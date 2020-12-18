#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#define COUNT_OF_PHILOSOPHERS 5

#include <iostream>
#include <thread>
#include <mutex>
#include <ctime>
#include <cstdlib>
#include <string>
#include <sstream>
#include <vector>

class Philosophers {
    std::timed_mutex forks[COUNT_OF_PHILOSOPHERS];
    std::mutex cout_mutex;

    std::vector<std::thread> philosophers;

    void print_msg(const std::string &msg);
    void create_msg(std::ostringstream &ostr, const std::string &id, const std::string &msg);
    bool get_forks(const std::string &id, std::timed_mutex &left_fork, std::timed_mutex &right_fork);
    void get_very_hungry(const std::string &id, std::timed_mutex &left_fork, std::timed_mutex &right_fork);

public:
    Philosophers();
    [[noreturn]] void Phil(size_t idx, const std::string &id);
};


#endif //PHILOSOPHERS_H
