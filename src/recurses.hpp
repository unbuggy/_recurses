#ifndef INCLUDED_RECURSES
#define INCLUDED_RECURSES

#include <chrono>       // milliseconds
#include <cstdint>      // uint32_t
#include <stdexcept>    // runtime_error

namespace recurses {

    struct error: std::runtime_error {
        error(char const* what): std::runtime_error(what) { }
    };

    // Indicates receipt of a POSIX signal.
    struct signal: error {
        int value;
        signal(char const* s, int i): error(s), value(i) { }
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
        void printw(char const* fmt, ...);
        void napms(int);
        void refresh();
        int scanw(char* fmt, ...);

        // The `*get*str` methods throw `signal` on SIGWINCH.
        void getnstr(char* s, int n);
        void getstr(char* s);

        // Additions relative to NCurses.
        void nap(std::chrono::milliseconds);
        int scanw(char const* fmt, ...);
    };

    struct window: screen {


    };
}

#endif
