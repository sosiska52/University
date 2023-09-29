#pragma once


enum Section { Рыбный = 1, Мясной, Хлебный, Растительность, Напитки };

union Selfmade {
    bool itIs;
    char ch;
};

struct product {
    int index;
    char name[100];
    int ammount;
    double price;
    char date[10];
    Section section;
    Selfmade smade;
};
