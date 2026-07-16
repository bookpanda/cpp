#include <memory>
#include <mutex>

template <typename T> class threadsafe_queue {
  private:
    struct node {
        std::shared_ptr<T> data;
        std::unique_ptr<node> next;
    };
    std::mutex head_mutex;
    std::unique_ptr<node> head;
    std::mutex tail_mutex;
    std::condition_variable data_cond;
    node *tail;
    node *get_tail() {
        std::lock_guard<std::mutex> tail_lock(tail_mutex);
        return tail;
    }
    std::unique_ptr<node> pop_head() {
        std::unique_ptr<node> old_head = std::move(head);
        head = std::move(old_head->next);
        return old_head;
    }
    std::unique_lock<std::mutex> wait_for_data() {
        std::unique_lock<std::mutex> head_lock(head_mutex);
        data_cond.wait(head_lock, [&] { return head.get() != get_tail(); });
        return std::move(head_lock);
    }
    std::unique_ptr<node> wait_pop_head() {
        std::unique_lock<std::mutex> head_lock(wait_for_data());
        return pop_head();
    }
    std::unique_ptr<node> wait_pop_head(T &value) {
        std::unique_lock<std::mutex> head_lock(wait_for_data());
        value = std::move(*head->data);
        return pop_head();
    }

  public:
    threadsafe_queue() : head(new node), tail(head.get()) {}
    threadsafe_queue(const threadsafe_queue &other) = delete;
    threadsafe_queue &operator=(const threadsafe_queue &other) = delete;

    std::shared_ptr<T> try_pop() {
        // pop_head() locks both head_lock and tail_lock
        // if a try_pop() on T1 is concurrent with a push() on T2, 2 cases:
        // 1. get_tail() before push(): tail points to old dummy node
        // 2. get_tail() after push(): tail points to new dummy node
        std::unique_ptr<node> old_head = pop_head();
        return old_head ? old_head->data : std::shared_ptr<T>();
    }

    std::shared_ptr<T> wait_and_pop() {
        std::unique_ptr<node> const old_head = wait_pop_head();
        return old_head->data;
    }
    void wait_and_pop(T &value) { std::unique_ptr<node> const old_head = wait_pop_head(value); }

    void push(T new_value) {
        std::shared_ptr<T> new_data(std::make_shared<T>(std::move(new_value)));
        std::unique_ptr<node> p(new node);
        {
            std::lock_guard<std::mutex> tail_lock(tail_mutex);
            tail->data = new_data;
            node *const new_tail = p.get();
            tail->next = std::move(p);
            tail = new_tail;
        }
        // notify AFTER tail_lock released so that waiting threads don't have to wait for tail_lock
        data_cond.notify_one();
    }
};