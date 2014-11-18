auto center = [this](int row, char const* title) {
    int width = getmaxx();
    auto len = std::strlen(title);
    auto indent = (width - len) / 2;
    mvaddstr(row, indent, title);
    refresh();
};

center(1, "Penguin Soccer Finals");
center(5, "Cattle Dung Samples from Temecula");
center(7, "Catatonic Theater");
center(9, "Why Do Ions Hate Each Other?");
getch();
