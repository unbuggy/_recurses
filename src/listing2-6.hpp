addstr("Type a few lines of text\n");
addstr("Press ~ to quit\n");

for (char ch; (ch = getch()) != '~';)
    ;
