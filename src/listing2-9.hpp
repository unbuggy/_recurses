auto const uni = 4.5;

addstr("SUSHI BAR");

move(3, 0);
printw("We have Uni today for $%.2f.\n", uni);
addstr("How many pieces would you like? ");

int pieces;
scanw("%d", &pieces);
printw("You want %d pieces?\n", pieces);
printw("That will be $%.2f!", uni * pieces);
getch();
