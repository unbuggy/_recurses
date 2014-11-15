# Recurses Code

Unless otherwise noted, all entities below are declared in namespace `recurses`, in header file `recurses.hpp`.

## `screen`

The `screen` class is a sentry responsible for both setting up and tearing down the NCurses system.  The first time `screen` is instantiated, its constructor calls NCurses `initscr`; likewise, the corresponding destructor calls Ncurses `endwin`.  Screen scopes may be nested; i.e., creating multiple screen objects in the same lexical scope will not call `initscr` redundantly, nor will `endwin` be called until the last screen object is destroyed.  If the last live screen object goes out of scope, calling `endwin`, and a new top-level `screen` object is created, that new top-level screen will (correctly) call `initscr`.  This usage meets the requirements documented in the NCurses manual.

The `screen` class provides public methods that wrap various NCurses top-level functions (or function-like macros); e.g., `addstr` and `refresh`.
