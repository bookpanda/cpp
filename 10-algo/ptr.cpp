#include <iostream>
#include <memory>

class Widget {
  public:
    void execute() {}
};

void process() {
    // modern cpp: no new, and normal pointers
    auto widget = std::make_unique<Widget>();
    widget->execute();

    // No 'delete' required. Memory is freed automatically here,
    // even if an exception is thrown above.
}

class Texture {
  public:
    void render() { std::cout << "Rendering...\n"; }
};

// std::shared_ptr is for shared ownership, specifically when a resource has multiple owners, and it is impossible to
// predict which owner will finish using it last
int main() {
    // Single allocation for both object and control block
    std::shared_ptr<Texture> texture1 = std::make_shared<Texture>();

    {
        std::shared_ptr<Texture> texture2 = texture1; // Count is now 2
        texture2->render();
    } // texture2 goes out of scope. Count drops to 1. Object stays alive.

    texture1->render();
} // texture1 goes out of scope. Count drops to 0. Object is destroyed.