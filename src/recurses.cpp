#include "recurses.hpp"

#define NCURSES_NOMACROS
#include <ncursesw/ncurses.h>
    // Includes stdio.h, unctrl.h, stdarg.h, and stddef.h.

#include <csignal>
#include <string>
#include <vector>

#include <stdlib.h>

namespace recurses {

// Macros {{{

/// *Ncurses Void* - Call the NCurses version, and throw if it fails.
#define NV(X) if (ERR == ::X) throw error(#X); else;

/// *Ncurses* - Return the result of the NCurses version, or throw if it fails.
#define N(X) { \
    auto r = ::X; \
    if (ERR == r) throw error(#X); \
    return r; \
}

/// *WRAP Void*
#define WRAPV0(F) void screen::F() { NV(F()) }
#define WRAPV1(F, T, x) void screen::F(T x) { NV(F(x)) }
#define WRAPV2(F, T, x, U, y) void screen::F(T x, U y) { NV(F(x, y)) }

/// *WRAP*
#define WRAP0(F, R) R screen::F() { N(F()); }
#define WRAP1(F, T, X, R) R screen::F(T X) { N(F(X)); }

/// *WRAP Const*
#define WRAPC0(F, R) R screen::F() const { N(F()); }
#define WRAPC1(F, T, X, R) R screen::F(T X) const { N(F(X)); }

// }}}

// class screen {{{

static attr_t convert(attr a) {
    attr_t r = 0;
    if (a & bold)       r |= A_BOLD;
    if (a & blink)      r |= A_BLINK;
    if (a & normal)     r |= A_NORMAL;
    if (a & underline)  r |= A_UNDERLINE;
    return r;
}

static int screen_depth;

// TERM settings other than "screen" confuse ncurses inside tmux.
screen::screen()  {
    if (++screen_depth == 1) {
        if (getenv("TMUX")) setenv("TERM", "screen", 1);
        initscr();
    }
}

screen::~screen() {
    if (--screen_depth == 0) endwin();
}

WRAPV1( addstr, char const*, s )
WRAP0(  getch,  int )
WRAPV2( move,   int, y, int, x )
WRAPV1( napms,  int, ms )
WRAPV0( refresh )

void screen::addch(   chtype c) { NV(addch(c._value))       }
void screen::attroff( attr   a) { NV(attroff(convert(a)))   }
void screen::attron(  attr   a) { NV(attron(convert(a)))    }
void screen::attrset( attr   a) { NV(attrset(convert(a)))   }
void screen::bkgd(    chtype c) { NV(bkgd(c._value))        }
void screen::insch(   chtype c) { NV(insch(c._value))       }

void screen::mvaddch(int y, int x, chtype c)   { NV(mvaddch(y, x, c._value)) }
void screen::mvaddstr(int y, int x, char const* s) { NV(mvaddstr(y, x, s)) }
void screen::mvinsch(int y, int x, chtype c)   { NV(mvinsch(y, x, c._value)) }
void screen::nap(std::chrono::milliseconds ms) { NV(napms(ms.count())) }

bool screen::beep()  { return OK == ::beep();  }
bool screen::flash() { return OK == ::flash(); }

int  screen::getmaxx()    const { return ::getmaxx(stdscr); }
int  screen::getmaxy()    const { return ::getmaxy(stdscr); }
bool screen::has_colors() const { return ::has_colors(); }

#define BODY \
    va_list args; \
    va_start(args, fmt); \
    ::vwprintw(stdscr, fmt, args); \
    va_end(args);
void screen::mvprintw(int y, int x, char const* fmt, ...) { move(y, x); BODY }
void screen::printw(char const* fmt, ...) { BODY }
#undef BODY

void screen::getnstr(char* s, int n) {
    auto r = ::getnstr(s, n);
    if (ERR         == r) throw error("getstr(s, n)");
    if (KEY_RESIZE  == r) throw signal("SIGWINCH", SIGWINCH);
}

void screen::getstr(char* s) {
    auto r = ::getstr(s);
    if (ERR         == r) throw error("getstr(s)");
    if (KEY_RESIZE  == r) throw signal("SIGWINCH", SIGWINCH);
}

int screen::scanw(char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    int r = ::vwscanw(stdscr, fmt, args);
    va_end(args);
    return r;
}

int screen::scanw(char const* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    std::vector<char> s(fmt, fmt + strlen(fmt));
    int r = ::vwscanw(stdscr, s.data(), args);
    va_end(args);
    return r;
}

// }}}

// class color_screen {{{

chtype operator|(color_pair cp, chtype ch) {
    ch._value |= COLOR_PAIR(cp._n);
    return ch;
}

static int color_screen_depth;
static int color_screen_colors;
static int color_screen_color_pairs;

detail::color_screen_pre::color_screen_pre() {
    if (++color_screen_depth == 1) {
        if (!has_colors()) throw error("screen does not support colors");
        NV(start_color())
        color_screen_colors      = COLORS;
        color_screen_color_pairs = COLOR_PAIRS;
    }
}

detail::color_screen_pre::~color_screen_pre() {
    --color_screen_depth;
}

static int color_screen_next_pair = 1;

color_screen::color_screen():
    colors(color_screen_colors),
    color_pairs(color_screen_color_pairs) { }

void color_screen::attrset(color_pair c) {
    NV(attrset(COLOR_PAIR(c._n)))
}

void color_screen::bkgd(color_pair c) {
    NV(bkgd(COLOR_PAIR(c._n)))
}

color_pair color_screen::init_pair(color f, color b) {
    if (color_screen_next_pair >= color_pairs)
        throw error("too many color pairs");
    NV(init_pair(color_screen_next_pair, int(f), int(b)))
    return {color_screen_next_pair++};
}

// }}}

}

// vi:fdm=marker
