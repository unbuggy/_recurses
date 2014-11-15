#include "recurses.hpp"
#include "std.hpp"

using namespace std::chrono_literals;
using namespace std::string_literals;

struct application: recurses::screen { void main(); };

void application::main() {
    for (char c : "Greetings from NCurses!"s) {
        addch(c);
        refresh();
        nap(100ms);
    }
    getch();
}

int main() try {
    application().main();
} catch (std::exception const& x) {
    std::cerr << "error: " << x.what() << '\n';
    return -1;
}
