#include "recurses.hpp"

#define NCURSES_NOMACROS
#include <ncursesw/ncurses.h>
    // Includes stdio.h, unctrl.h, stdarg.h, and stddef.h.

#include <csignal>
#include <string>
#include <vector>

/// *Ncurses Void* - Call the NCurses version, and throw if it fails.
#define NV(X) if (ERR == ::X) throw error(#X);

/// *Ncurses* - Return the result of the NCurses version, or throw if it fails.
#define N(X) { \
    auto r = ::X; \
    if (ERR == r) throw error(#X); \
    return r; \
}

/// *WRAP Void*
#define WRAPV0(F) void recurses::screen::F() { NV(F()); }
#define WRAPV1(F, T, x) void recurses::screen::F(T x) { NV(F(x)); }
#define WRAPV2(F, T, x, U, y) \
    void recurses::screen::F(T x, U y) { NV(F(x, y)); }

/// *WRAP*
#define WRAP0(F, R) R recurses::screen::F() { N(F()); }
#define WRAP1(F, T, X, R) R recurses::screen::F(T X) { N(F(X)); }

namespace recurses {
    static attr_t convert(attr a) {
        attr_t r = 0;
        if (a & bold)   r |= A_BOLD;
        if (a & blink)  r |= A_BLINK;
        if (a & normal) r |= A_NORMAL;
        return r;
    }
}

static int screen_depth;

recurses::screen::screen()  { if (++screen_depth == 1) initscr(); }
recurses::screen::~screen() { if (--screen_depth == 0) endwin();  }

void recurses::screen::addch(chtype c) { NV(addch(c._value));       }
void recurses::screen::attroff(attr a) { NV(attroff(convert(a)));   }
void recurses::screen::attron(attr a)  { NV(attron(convert(a)));    }
void recurses::screen::attrset(attr a) { NV(attrset(convert(a)));    }

void recurses::screen::getnstr(char* s, int n) {
    auto r = ::getnstr(s, n);
    if (ERR         == r) throw error("getstr(s, n)");
    if (KEY_RESIZE  == r) throw signal("SIGWINCH", SIGWINCH);
}

void recurses::screen::getstr(char* s) {
    auto r = ::getstr(s);
    if (ERR         == r) throw error("getstr(s)");
    if (KEY_RESIZE  == r) throw signal("SIGWINCH", SIGWINCH);
}

void recurses::screen::nap(std::chrono::milliseconds ms) {
    NV(napms(ms.count()))
}

void recurses::screen::printw(char const* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    ::vwprintw(stdscr, fmt, args);
    va_end(args);
}

int recurses::screen::scanw(char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    int r = ::vwscanw(stdscr, fmt, args);
    va_end(args);
    return r;
}

int recurses::screen::scanw(char const* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    std::vector<char> s(fmt, fmt + strlen(fmt));
    int r = ::vwscanw(stdscr, s.data(), args);
    va_end(args);
    return r;
}

WRAPV1( addstr, char const*, s )
WRAPV0( clear )
WRAP0(  getch,  int )
WRAPV2( move,   int, y, int, x )
WRAPV1( napms,  int, ms )
WRAPV0( refresh )
