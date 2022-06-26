#include <iostream>
#include "client.hpp"
#include "client.cpp"
#include "StaticList.cpp"
#include "StaticList.hpp"

using namespace std;

int main() {
    Client c0(0, "Dummy");
    Client c1(67, "c1");
    Client c2(42, "c2");
    Client c3(30, "c3");
    Client c4(15, "c4");
    Client c5(36, "c5");
    Client c6(10, "c6");
    Client c7(13, "c7");
    Client c8(9, "c8");
    Client c9(3, "c9");
    Client c10(16, "c10");

    StaticList l;

    l.addList(0, c0);
    l.addList(1, c1);
    l.addList(2, c2);
    l.addList(3, c3);
    l.addList(4, c4);
    l.addList(5, c5);
    l.addList(6, c6);
    l.addList(7, c7);
    l.addList(8, c8);
    l.addList(9, c9);
    l.addList(10, c10);

    l.printList();
    l.heapSort();

    return 0;
}