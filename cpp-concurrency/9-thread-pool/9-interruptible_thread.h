#ifndef INTERRUPTIBLE_THREAD_H
#define INTERRUPTIBLE_THREAD_H

#include <future>
#include <thread>

class interrupt_flag {
  public:
    void set();
    bool is_set() const;
};

// this implementation doesn’t take account of handling joining with the thread, or detaching it. You need to ensure
// that the flag variable is cleared when the thread exits, or is detached, to avoid a dangling pointer.
thread_local interrupt_flag this_thread_interrupt_flag;

class interruptible_thread {
    std::thread internal_thread;
    interrupt_flag *flag;

  public:
    template <typename FunctionType> interruptible_thread(FunctionType f) {
        std::promise<interrupt_flag *> p;
        // f by value (copy), &p by reference
        internal_thread = std::thread([f, &p] {
            p.set_value(&this_thread_interrupt_flag);
            f();
        });
        // calling thread wait til future is ready
        flag = p.get_future().get();
    }
    void interrupt() {
        if (flag) {
            flag->set();
        }
    }
};

#endif // INTERRUPTIBLE_THREAD_H