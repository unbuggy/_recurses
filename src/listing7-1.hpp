auto g = [this]() {
    try {
        getch();
        return true;
    } catch (...) {
        return false;
    }
};

addstr("Press any key to begin:\n");
getch();

nodelay();
addstr("Press any key to stop the insane loop!\n");
for (int c, value = 0; !getch(c); ++value)
    printw("%d\r", value);
