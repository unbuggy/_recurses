#ifndef INCLUDED_RECURSES
#define INCLUDED_RECURSES

#include <cstdint>
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

        void addch(chtype c);
        void addstr(char const* s);
        void refresh();
        int getch();
    };

    struct window: screen {


    };
}

#endif
