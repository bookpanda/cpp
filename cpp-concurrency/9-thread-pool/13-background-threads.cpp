#include "12-interruptible-wait-any.h"
#include "9-interruptible_thread.h"
#include <mutex>

std::mutex config_mutex;
std::vector<interruptible_thread> background_threads;
void background_thread(int disk_id) {
    while (true) {
        interruption_point();
        // fs_change fsc = get_fs_changes(disk_id);
        // if (fsc.has_changes()) {
        //     update_index(fsc);
        // }
    }
}

void start_background_processing() {
    background_threads.push_back(interruptible_thread(background_thread));
    background_threads.push_back(interruptible_thread(background_thread));
}
int main() {
    start_background_processing();
    // process_gui_until_exit();
    std::unique_lock<std::mutex> lk(config_mutex);
    // on shutdown of program, interrupt all bg threads before joining any
    // this allows bg threads to cleanup in parallel
    // otherwise, if you interrupt+join threads 1 by 1, the main thread will block until each thread is joined, slower
    for (unsigned i = 0; i < background_threads.size(); ++i) {
        background_threads[i].interrupt();
    }
    for (unsigned i = 0; i < background_threads.size(); ++i) {
        background_threads[i].join();
    }
}