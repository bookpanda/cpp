#include <atomic>
#include <memory>

template <typename T> class lock_free_stack {
  private:
    struct node {
        T data;
        node *next;
        node(T const &data_) : data(data_) {}
    };
    std::atomic<node *> head;
    std::atomic<unsigned> threads_in_pop;
    void try_reclaim(node *old_head);

  public:
    std::shared_ptr<T> pop() {
        ++threads_in_pop;
        node *old_head = head.load();
        while (old_head && !head.compare_exchange_weak(old_head, old_head->next))
            ;
        // node now removed from the stack
        std::shared_ptr<T> res;
        if (old_head) {
            // remove data from node (by moving to res, which will be automatically deleted outside the scope)
            res.swap(old_head->data);
        }
        // called once node has been removed from the stack
        try_reclaim(old_head);
        return res;
    }
};