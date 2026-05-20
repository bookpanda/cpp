#include <iostream>
#include <string>

void hello_line() {
    std::cout << "Please enter your name\n";
    std::string str;
    // entire line (can accept spaces)
    std::getline(std::cin, str);
    std::cout << "Hello, " << str << "!\n";
}

int main(void) {
    hello_line();

    while (std::cin) {
        for (int i; std::cin >> i;) { // ... use the integer ...
        }
        if (std::cin.eof()) {
            // .. all is well we reached the end-of-file ...
        } else if (std::cin.fail()) { // a potentially recoverable error
            std::cin.clear();         // reset the state to good()

            char ch;
            if (std::cin >> ch) { // look for nesting represented by { ... }
                switch (ch) {
                case '{': // ... start nested structure ...
                    break;
                case '}': // ... end nested structure ...
                    break;
                default:
                    std::cin.setstate(std::ios_base::failbit); // add fail() to cin’s state
                }
            }
        }
        // ...
    }

    return 0;
}