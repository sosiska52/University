#pragma once


enum Section { ������ = 1, ������, �������, ��������������, ������� };

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
