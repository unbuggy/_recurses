int rows = getmaxy() - 1, cols = getmaxx() - 1;

mvaddch(0, 0, '*');
refresh();
napms(500);

mvaddch(0, cols, '*');
refresh();
napms(500);

mvaddch(rows, 0, '*');
refresh();
napms(500);

// The `addch` method fails to move the window position past the bottom right
// corner, and so reports an error.  The `insch` has no such problem.
//
//  mvaddch(rows, cols, '*');
mvinsch(rows, cols, '*');

getch();
