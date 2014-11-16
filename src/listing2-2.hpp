for (char c : "Greetings from NCurses!"s) {
    addch(c);
    refresh();
    nap(100ms);
}
getch();
