#include <memory>
#include <mutex>

class some_resource {
  public:
    void do_something() {
        // do something
    }
};

// shared read-only resource is expensive to create, so we only create it if it's not already created
std::shared_ptr<some_resource> resource_ptr;
std::mutex resource_mutex;
void foo() {
    std::unique_lock<std::mutex> lk(resource_mutex);
    if (!resource_ptr) {
        resource_ptr.reset(new some_resource);
    }
    lk.unlock();
    resource_ptr->do_something();
}

// call_once is better for this use case because it's more efficient than a mutex
std::once_flag resource_flag;
void init_resource() { resource_ptr.reset(new some_resource); }
void foo2() {
    // Initialization is called exactly once.
    std::call_once(resource_flag, init_resource);
    resource_ptr->do_something();
}

// alt: use static if only single global instance is needed
static some_resource resource;
void foo3() { resource.do_something(); }