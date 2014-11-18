int rows = getmaxy() - 1, cols = getmaxx() - 1;

move(0, 0);
addch('*');
refresh();
napms(500);

move(0, cols);
addch('*');
refresh();
napms(500);

move(rows, 0);
addch('*');
refresh();
napms(500);

move(rows, cols);

// The `addch` method fails to move the window position past the bottom right
// corner, and so reports an error.  The `insch` has no such problem.
//
//  addch('*');
insch('*');

getch();
