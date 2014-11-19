// Fill the screen with text, to see how it's moved by the ticker (below).
// The original listing uses addstr, letting a trailing '\n' in the string move
// the cursor to the next line, but addstr ERRs on the last line because the
// the newline cannot be rendered (since, by definition, there are no more
// lines, hence nowhere to put the cursor).
for (int y = getmaxy(); y--;)
    mvaddstr(y, 0, "A B C D E F G H I J K L M N O P Q R S T U V W X Y Z");
refresh();

char text[] = "Stock Market Swells!  DOW tops 15,000!";
for (auto len = sizeof(text) - 1; len--;) {
    move(5, 5);
    insch(text[len]);
    refresh();
    napms(100);
}
getch();
