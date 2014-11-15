#include "recurses.hpp"
#include "std.hpp"

int main() try {
    recurses::screen scr;
    scr.addstr("Goodbye, cruel C programming!");
    scr.refresh();
    scr.getch();
} catch (std::exception const& x) {
    std::cerr << "error: " << x.what() << '\n';
    return -1;
}
