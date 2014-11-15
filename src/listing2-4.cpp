#include "recurses.hpp"
#include "std.hpp"

using namespace std::chrono_literals;
using namespace std::string_literals;

struct application: recurses::screen { void main(); };

void application::main() {
    addstr("Oh give me a clone!\n");
    addstr("Yes a clone of my own!");
    move(2, 0);
    addstr("With the Y chromosome changed to the X.");
    getch();
}

int main() try {
    application().main();
} catch (std::exception const& x) {
    std::cerr << "error: " << x.what() << '\n';
    return -1;
}
