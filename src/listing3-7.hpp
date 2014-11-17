
auto pair1 = init_pair(white, blue),
     pair2 = init_pair(green, white),
     pair3 = init_pair(red,   green);

bkgd(pair1);
addstr("I think that I shall never see\n");
addstr("a color screen as pretty as thee\n");
addstr("For seasons may change\n");
addstr("and storms may thunder;\n");
addstr("But color text shall always wonder.");
getch();

bkgd(pair2);
getch();

bkgd(pair3);
getch();
