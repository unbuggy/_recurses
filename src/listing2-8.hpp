char first[4];
char last[4];

addstr("Enter the first 3 letters of your first name? ");
getnstr(first, 3);

addstr("Enter the first 3 letters of your last name? ");
getnstr(last, 3);

addstr("Your secret agent name is ");
printw("%s%s", first, last);
addch('!');

getch();
