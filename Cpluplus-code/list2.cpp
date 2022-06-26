#include <iostream>
#include "client.hpp"
#include "client.cpp"
#include "StaticList.hpp"
#include "StaticList.cpp"

using namespace std;

int main() {
    StaticList l2;

    l2.randomList();
    l2.printList(l2.dataStructure_size); cout << endl;
    l2.heapSort();
    
    cout << endl << "====> Heap sort list: "; l2.printList(l2.dataStructure_size);
    l2.printMemoryAcessList();

    return 0;
}