#ifndef INCLUDED_RECURSES
#define INCLUDED_RECURSES

#include <stdexcept>    // runtime_error

namespace recurses {

    struct error: std::runtime_error {
        error(char const* what): std::runtime_error(what) { }
    };

    struct screen {
        screen();
        ~screen();

        void addstr(char const* s);
        void refresh();
        int getch();
    };

    struct window: screen {


    };
}

#endif
