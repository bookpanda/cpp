#include <iostream>

enum class Color { red, blue, green };
enum class Traffic_light { green, yellow, red };
Color col = Color::red;
Traffic_light light = Traffic_light::red;

// int i = Color::red; // error: Color::red is not an int
// Color c = 2; // error: 2 is not a Color

Traffic_light &operator++(Traffic_light &t) // prefix increment: ++
{
    switch (t) {
    case Traffic_light::green:
        return t = Traffic_light::yellow;
    case Traffic_light::yellow:
        return t = Traffic_light::red;
    case Traffic_light::red:
        return t = Traffic_light::green;
    }
}

int main(void) {
    Traffic_light light = Traffic_light::green;
    light = ++light;
    std::cout << "Light: " << static_cast<int>(light) << std::endl;
    return 0;
}
