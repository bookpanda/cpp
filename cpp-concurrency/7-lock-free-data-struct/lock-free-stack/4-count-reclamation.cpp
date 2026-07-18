#include <atomic>

template <typename T> class lock_free_stack {
  private:
    struct node {
        T data;
        node *next;
        node(T const &data_) : data(data_) {}
    };
    std::atomic<node *> to_be_deleted;
    std::atomic<unsigned> threads_in_pop;
    static void delete_nodes(node *nodes) {
        while (nodes) {
            node *next = nodes->next;
            delete nodes;
            nodes = next;
        }
    }
    void try_reclaim(node *old_head) {
        if (threads_in_pop == 1) { // it's the last thread calling pop
            node *nodes_to_delete = to_be_deleted.exchange(nullptr);
            if (!--threads_in_pop) { // may also be safe to delete pending nodes
                delete_nodes(nodes_to_delete);
            } else if (nodes_to_delete) { // not safe to reclaim nodes, chain them back to pending list
                // can happen e.g. T2 calls pop() when T1 between checking threads_in_pop==1 and !--threads_in_pop
                chain_pending_nodes(nodes_to_delete);
            }
            // can delete old_head now
            delete old_head;
        } else { // chain node to pending list
            chain_pending_node(old_head);
            --threads_in_pop;
        }
    }
    void chain_pending_nodes(node *nodes) {
        node *last = nodes;
        while (node *const next = last->next) {
            last = next;
        }
        chain_pending_nodes(nodes, last);
    }
    void chain_pending_nodes(node *first, node *last) {
        last->next = to_be_deleted;
        while (!to_be_deleted.compare_exchange_weak(last->next, first))
            ;
    }
    void chain_pending_node(node *n) { chain_pending_nodes(n, n); }
};