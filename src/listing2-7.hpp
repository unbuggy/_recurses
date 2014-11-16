char first[24];
char last[32];

addstr("What is your first name? ");
getstr(first);

addstr("What is your last name? ");
getstr(last);

printw("Pleased to meet you, %s %s!", first, last);
getch();
