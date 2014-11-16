auto const count = 5;

char text[count][10] = { "Do", "you", "find", "this", "silly?" };

for (int a = 0; a < count; ++a) {
    for (int b = 0; b < count; ++b) {
        if (b == a) attrset(bold | underline);
        printw("%s", text[b]);
        if (b == a) attroff(bold | underline);
        addch(' ');
    }
    addstr("\b\n");
}
getch();
