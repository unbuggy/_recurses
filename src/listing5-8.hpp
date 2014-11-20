char Ham1[] = "To be, or not to be: that is the question:\n";
char Ham2[] = "Whether 'tis nobler in the mind to suffer\n";
char Ham3[] = "The slings and arrows of outrageous fortune,\n";
char Ham4[] = "Or to take arms against a sea of troubles,\n";
char Ham5[] = "And by opposing end them?\n";

addstr(Ham1);
addstr(Ham2);
addstr(Ham3);
addstr(Ham4);
addstr(Ham5);
getch();

move(2, 25);
for (int c = sizeof("outrageous"); --c;) {
    delch();
    refresh();
    napms(100);
}

move(2, 25);
char ob[] = "obnoxious";
for (int c = sizeof(ob) - 1; c--;) {
    insch(ob[c]);
    refresh();
    napms(100);
}

getch();
