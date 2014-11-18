addstr("Type some text; '~' to end:\n");
refresh();

while (getch() != '~')
    ;

int row = getcury(), col = getcurx();
printw("\n\nThe cursor was at row %d, column %d\n", row, col);
printw("when you stopped typing.");
getch();
