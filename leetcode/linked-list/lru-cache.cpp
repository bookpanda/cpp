#include <iostream>
#include <unordered_map>

class Node {
  public:
    int value;
    Node *prev;
    Node *next;
    Node(int val) {
        value = val;
        prev = nullptr;
        next = nullptr;
    }
};

class LRUCache {
  public:
    int capacity;
    int size;
    Node *head;
    Node *tail;
    std::unordered_map<int, std::pair<Node *, int>> map;
    LRUCache(int capa) {
        capacity = capa;
        size = 0;
        head = new Node(0);
        tail = new Node(0);
        head->next = tail;
        tail->prev = head;
    }

    int get(int key) {
        auto it = map.find(key);
        if (it == map.end())
            return -1;

        Node *node = it->second.first;
        int value = it->second.second;
        extractNode(node);
        putNodeAfterHead(node);

        return value;
    }

    void put(int key, int value) {
        auto it = map.find(key);
        if (it != map.end()) {
            // existing key, just update value
            it->second.second = value;
            Node *node = it->second.first;
            extractNode(node);
            putNodeAfterHead(node);

            return;
        }
        if (size == capacity) {
            // remove last node + its key from map
            Node *toRemove = tail->prev;
            extractNode(toRemove);
            map.erase(toRemove->value);
            delete toRemove;
            size--;
        }

        // add key to map + node to right after head
        Node *newNode = new Node(key);
        putNodeAfterHead(newNode);
        map[key] = {newNode, value};
        size++;

        return;
    }

  private:
    void extractNode(Node *node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
    void putNodeAfterHead(Node *node) {
        Node *oldFirst = head->next;
        oldFirst->prev = node;
        node->prev = head;
        node->next = oldFirst;
        head->next = node;
    }
    void printList() {
        Node *curr = head;
        while (curr) {
            std::cout << curr->value << "->";
            curr = curr->next;
        }
        std::cout << "\n";
        curr = tail;
        while (curr) {
            std::cout << curr->value << "->";
            curr = curr->prev;
        }
        std::cout << "\n";
    }
};
// doubly-linked list: LRU element at tail of list (key is node's val)
// map[key] = pair<node of list, value>

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */