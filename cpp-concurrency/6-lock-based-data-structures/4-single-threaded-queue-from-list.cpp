#include <memory>

template <typename T> class queue {
  private:
    struct node {
        T data;
        std::unique_ptr<node> next;
        node(T data_) : data(std::move(data_)) {}
    };
    std::unique_ptr<node> head;
    node *tail;

  public:
    queue() : tail(nullptr) {}
    queue(const queue &other) = delete;
    queue &operator=(const queue &other) = delete;
    std::shared_ptr<T> try_pop() {
        if (!head) {
            return std::shared_ptr<T>();
        }
        std::shared_ptr<T> const res(std::make_shared<T>(std::move(head->data)));
        std::unique_ptr<node> const old_head = std::move(head);
        head = std::move(old_head->next);
        if (!head)
            tail = nullptr;
        return res;
    }
    void push(T new_value) {
        std::unique_ptr<node> p(new node(std::move(new_value)));
        node *const new_tail = p.get(); // save raw pointer before p is moved (becomes nullptr)
        if (tail) {
            // unique_ptr cannot be copied, only moved.
            // before:  p owns the new node, tail->next is empty/old
            // after:   tail->next owns the new node, p is nullptr
            tail->next = std::move(p);

            // tail->next = p;  // ERROR — unique_ptr copy assignment is deleted
        } else {
            head = std::move(p);
        }
        tail = new_tail;
    }
};