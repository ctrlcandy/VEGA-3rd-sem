#include "Philosophers.h"

Philosophers::Philosophers() {
    srand(time(nullptr));

    philosophers.emplace_back(&Philosophers::Phil, this, 0, "Socrat");
    philosophers.emplace_back(&Philosophers::Phil, this, 1, "Platon");
    philosophers.emplace_back(&Philosophers::Phil, this, 2, "Decart");
    philosophers.emplace_back(&Philosophers::Phil, this, 3, "Popper");
    philosophers.emplace_back(&Philosophers::Phil, this, 4, "Aristotel");

    for (auto &t : philosophers) t.join();
}

void Philosophers::print_msg(const std::string &msg) {
    std::lock_guard<std::mutex> guard(cout_mutex);
    std::cout << msg << std::flush;
}

void Philosophers::create_msg(std::ostringstream &ostr, const std::string &id, const std::string &msg) {
    ostr.str(std::string());
    ostr << id << " " << msg << std::endl;
    print_msg(ostr.str());
}

bool Philosophers::get_forks(const std::string &id, std::timed_mutex &left_fork, std::timed_mutex &right_fork) {
    auto period = std::chrono::milliseconds(10000);
    std::ostringstream ostr;

    if (left_fork.try_lock_for(period)) {
        create_msg(ostr, id, "got left fork!");

        if (right_fork.try_lock_for(period)) {
            create_msg(ostr, id, "got right fork!");
            create_msg(ostr, id, "can eat!");
            std::this_thread::sleep_for(std::chrono::seconds(20));

            left_fork.unlock();
            right_fork.unlock();

            create_msg(ostr, id, "put forks on the table");

            return true;
        } else {
            create_msg(ostr, id, "can't get all forks, put it on the table!!!");
            left_fork.unlock();
        }
    }
    return false;
}

void Philosophers::get_very_hungry(const std::string &id, std::timed_mutex &left_fork, std::timed_mutex &right_fork) {
    std::ostringstream ostr;

    left_fork.lock();
    create_msg(ostr, id, "got left fork!");

    right_fork.lock();
    create_msg(ostr, id, "got right fork!");

    create_msg(ostr, id, "CAN EAT!!!");
    std::this_thread::sleep_for(std::chrono::seconds(3));

    left_fork.lock();
    right_fork.lock();
    create_msg(ostr, id, "put forks on the table");
}

void Philosophers::Phil(size_t idx, const std::string &id) {
    std::timed_mutex &left_fork = forks[idx == 0 ? COUNT_OF_PHILOSOPHERS - 1 : idx - 1];
    std::timed_mutex &right_fork = forks[idx];

    std::ostringstream ostr;

    while (true) {
        // Thinking about...
        create_msg(ostr, id, "is thinking about");
        std::this_thread::sleep_for(std::chrono::seconds(rand() % 7));

        // Got hungry
        create_msg(ostr, id, "got hungry");

        // Waiting for forks
        if (!get_forks(id, left_fork, right_fork)) {
            // Getting very hungry...
            std::this_thread::sleep_for(std::chrono::seconds(rand() % 100));
            create_msg(ostr, id, "getting very hungry!!!");
            get_very_hungry(id, left_fork, right_fork);
        }
    }
}



