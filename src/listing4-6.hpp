int const col1 = 5, col2 = 38;

mvprintw(5, col1, "%30s", "Your name:");
mvprintw(5, col2, "%-30s", "Art Grockmeister");

mvprintw(7, col1, "%30s", "Your company:");
mvprintw(7, col2, "%-30s", "Sterling/Worbletyme");

mvprintw(9, col1, "%30s", "Position:");
mvprintw(9, col2, "%-30s", "Grand Duke of Finance");

mvprintw(11, col1, "%30s", "Date hired:");
mvprintw(11, col2, "%-30s", "October 19, 1993");

refresh();
getch();
