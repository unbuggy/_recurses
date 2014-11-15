#include "recurses.hpp"

#define NCURSES_NOMACROS
#include <ncursesw/ncurses.h>
    // Includes stdio.h, unctrl.h, stdarg.h, and stddef.h.

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

/// *WRAP*
#define WRAP0(F, R) R recurses::screen::F() { N(F()); }
#define WRAP1(F, T, X, R) R recurses::screen::F(T X) { N(F(X)); }

static int screen_depth;

recurses::screen::screen()  { if (++screen_depth == 1) initscr(); }
recurses::screen::~screen() { if (--screen_depth == 0) endwin();  }

void recurses::screen::addch(chtype c) { NV(addch(c._value)); }

WRAPV0(refresh)
WRAPV1(addstr, char const*, s)
WRAP0(getch, int)
