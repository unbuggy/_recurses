#include "recurses.hpp"
#include "std.hpp"

using namespace std::chrono_literals;
using namespace std::string_literals;

int main() try {
    recurses::screen scr;
    for (char c : "Greetings from NCurses!"s) {
        scr.addch(c);
        scr.refresh();
        scr.nap(100ms);
    }
    scr.getch();
} catch (std::exception const& x) {
    std::cerr << "error: " << x.what() << '\n';
    return -1;
}
