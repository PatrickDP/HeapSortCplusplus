#include "StaticList.hpp"

StaticList::StaticList() { sizeList = 0; }
StaticList::~StaticList() { 
    Client client;

    for(int i = sizeList; i >= 0; i--) {
        clients[i] = client;
    }

    sizeList = 0;
}

void StaticList::printList() {
    if(sizeList == 0) { 
        cout << endl << "ERROR: Empty List." << endl;
        return;
    }

    for(unsigned i = 1; i < sizeList; i++) {
        clients[i].printClient();
    }
    
    cout << endl;
}
void StaticList::addList(unsigned position, const Client & client) {
    if(position > sizeList) {
        cout << "Error: Invalid position." << endl;
        return;
    }
    if(TOTAL_MAX == sizeList) {
        cout << "Error: Full List." << endl;
        return;
    }

    for(int i = sizeList; i > position; i--) {
        clients[i] = clients[i - 1];
    }

    clients[position] = client;
    sizeList++;
}
int StaticList::searchList(unsigned key) {
    int index = -1;
    unsigned position = 0;

    while(position < sizeList) {
        if(clients[position].key == key) {
            index = position;
            position = sizeList;
        }

        position++;
    }

    return index;
}
void StaticList::deleteList(unsigned key) {
    int position = 0;

    position = searchList(key);

    if(position >= 0) {
        sizeList--;
        
        for(unsigned i = position; i < sizeList; i++) {
            clients[i] = clients[i + 1];
        }
    }
}
void StaticList::randomList() {
    unsigned randomKey = 0;

    for(unsigned i = 0; i < TOTAL_MAX; i++) {
       
        randomKey = rand() % TOTAL_MAX;   
       
        while(isRandomKey(randomKey)) {
            randomKey = rand() % TOTAL_MAX;
        }   
        
        clients[i].key = randomKey; 
        clients[i].name = "rc" + to_string(randomKey);
        
        sizeList++;
    }
}
bool StaticList::isRandomKey(unsigned randomKey) {
    for(unsigned i = 0; i < sizeList; i++) {
        if(clients[i].key == randomKey) {
            return true;
        }
    }
    
    return false;
}
void StaticList::eachStepList( Client clients[], Client auxiliarList[]) { // OK
    static unsigned counter = 1;
    cout << "\t\t" << counter << ".\t"; printTwoLists(clients, auxiliarList);
    counter++;
}
void StaticList::printTwoLists(Client clients[], Client auxiliarList[]) { // OK
    cout << "1° parameter:\t";
    for(unsigned i = 0; i < sizeList; i++) {
        clients[i].printClient();
    }

    cout << "\t-\t 2° parameter:\t "; 
    for(unsigned i = 0; i < sizeList; i++) {
        auxiliarList[i].printClient();
    }
    cout << endl;
}
void StaticList::storeValueArrayMergeSort(unsigned num_memoryAcess, unsigned arr[]) {
    static unsigned index = 0;
    
    if(index < sizeList) {
        arr[index] = num_memoryAcess;
        index++;
    } else { index = 0; }
}
void StaticList::storeValueArrayMerge(unsigned num_memoryAcess, unsigned arr[]) {
    static unsigned index = 0;
    
    if(index < sizeList) {
        arr[index] = num_memoryAcess;
        index++;
    } else { index = 0; }
}
void StaticList::printMemoryAcessList() {

    cout << endl <<"- Array of memory acesses in mergeSort function:\t\t";
    for(unsigned i = 0; i < sizeList; i++) {
        total_memoryAcess_mergeSort += arr_mergeSort[i];
        cout << arr_mergeSort[i] << " ";
    }
    cout << endl;

    cout <<"- Array of memory acesses in merge function:\t\t\t";
    for(unsigned i = 0; i < sizeList; i++) {
        total_memoryAcess_merge += arr_merge[i];
        cout << arr_merge[i] << " ";
    }
    cout << endl;
    
    cout << "- Memory acesses on the list during mergeSort function:\t" << total_memoryAcess_mergeSort << endl;
    cout << "- Memory acesses on the list during merge function:\t\t" << total_memoryAcess_merge << endl;

    cout << endl <<"> Array of total memory acesses:\t\t\t\t\t\t";
    for(unsigned i = 0; i < sizeList; i++) {
        arr_totalMemoryAcess[i] = arr_mergeSort[i] + arr_merge[i];
        cout << arr_totalMemoryAcess[i] << " ";
    }
    cout << endl;

    total_memoryAcess = total_memoryAcess_mergeSort + total_memoryAcess_merge;

    cout << "> Total of memoryAcess in mergeSort algorithm:\t\t\t" << total_memoryAcess << endl;

    cout << endl << "- Acumulator Array of memory acesses value:\t\t\t\t";
    for(unsigned i = 0; i < sizeList; i++) {
        arr_acumulatorMemoryAcess[i] = acumulator_memoryAcess + arr_totalMemoryAcess[i];
        acumulator_memoryAcess = arr_acumulatorMemoryAcess[i];
        cout << arr_acumulatorMemoryAcess[i] << " ";
    }
    cout << endl;
}
// HEAP
// CRIA UM HEAP
void StaticList::createHeap() {
    unsigned mid = sizeList / 2;
    for(unsigned i = mid; i != 0; i--) { heapfy(i); }
}
// ENCONTRA O PAI, FILHO ESQ. E DIR.
unsigned StaticList::parent(unsigned i) { return (i / 2); }
unsigned StaticList::leftSon(unsigned i) { return (2 * i); }
unsigned StaticList::rightSon(unsigned i) { return (2 * i) + 1; }
// RESTAURA A PROPRIEDADE DE HEAP
void StaticList::heapfy(unsigned i) {
    unsigned left = leftSon(i);
    unsigned right = rightSon(i);

    unsigned majorElement = 0;

    if((left <= sizeList) && (clients[left].key > clients[i].key)) {
        majorElement = left;
    } else { majorElement = i; }
    if((right <= sizeList) && (clients[right].key > clients[majorElement].key)) {
        majorElement = right;
    }
    if (majorElement != i) {
        swap(clients[i], clients[majorElement]);
        heapfy(majorElement);
    }
}
void StaticList::heapSort() {
    createHeap();

    sizeList--;
    unsigned sizeList_aux = sizeList;

    for(unsigned i = sizeList_aux; i != 0; i--) {
        sizeList--;
        swap(clients[1], clients[i]);
        heapfy(1);
    }

    sizeList = sizeList_aux + 1;

    cout << "Heap sorted list: "; printList();
}