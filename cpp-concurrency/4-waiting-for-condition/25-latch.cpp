#include <future>
#include <iostream>
#include <latch>
#include <vector>

using namespace std;

struct my_data {
    int value;
};

my_data make_data(int i) { return my_data{i}; }
void do_more_stuff() { return; }
void process_data(my_data *data, int thread_count) { return; }

int main() {
    unsigned const thread_count = 2;
    latch done(thread_count);
    my_data data[thread_count];
    std::vector<std::future<void>> threads;

    for (unsigned i = 0; i < thread_count; ++i)
        threads.push_back(std::async(std::launch::async, [&, i] {
            // everything by reference, except i by value
            data[i] = make_data(i);
            done.count_down();
            do_more_stuff();
        }));

    // threads have other work (do_more_stuff) after the data is available, so main thread can start processing right
    // away w/o waiting for all threads to finish 100%.
    done.wait();

    process_data(data, thread_count);
    std::cout << "Done processing" << std::endl;

    return 0;
}