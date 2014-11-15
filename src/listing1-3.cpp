#include "recurses.hpp"
#include "std.hpp"

struct application: recurses::screen { void main(); };

void application::main() {
    addstr("Goodbye, cruel C programming!");
    refresh();
    getch();
}

int main() try {
    application().main();
} catch (std::exception const& x) {
    std::cerr << "error: " << x.what() << '\n';
    return -1;
}
