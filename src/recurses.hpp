#ifndef INCLUDED_RECURSES
#define INCLUDED_RECURSES

#include <chrono>       // milliseconds
#include <cstdint>      // uint32_t
#include <stdexcept>    // runtime_error

namespace recurses {

    struct error: std::runtime_error {
        error(char const* what): std::runtime_error(what) { }
    };

    struct chtype {
        std::uint32_t _value;

        chtype(char c): _value(c) { }
    };

    struct screen {
        screen();
        ~screen();

        void addch(chtype);
        void addstr(char const*);
        void clear();
        int getch();
        void move(int y, int x);
        void nap(std::chrono::milliseconds);
        // void napms(int); use `nap` instead; e.g., `scr.nap(100ms)`
        void refresh();
    };

    struct window: screen {


    };
}

#endif
