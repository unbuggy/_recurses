auto fill = [this]() {
    move(0, 0);
    char s[] = "blah ";
    for (int c = (getmaxy() * getmaxx()) / (sizeof(s) - 1) - 1; c--;)
        addstr(s);
    insstr(s);
    getch();
};

fill();
move(5, 20);
clrtoeol();
getch();

fill();
move(5, 20);
clrtobot();
getch();
