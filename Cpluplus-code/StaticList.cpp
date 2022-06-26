#include "StaticList.hpp"

StaticList::StaticList() { dataStructure_size = 0; }
StaticList::~StaticList() { 
    Client client;

    for(int i = dataStructure_size; i >= 0; i--) {
        clients[i] = client;
    }

    dataStructure_size = 0;
}

void StaticList::printList(unsigned dataStructure_size) {
    if(dataStructure_size == 0) { 
        cout << endl << "ERROR: Empty List." << endl;
        return;
    }

    for(unsigned i = 0; i < dataStructure_size; i++) {
        clients[i].printClient();
    }
    
    cout << endl;
}
void StaticList::addList(unsigned position, const Client & client) {
    if(position > dataStructure_size) {
        cout << "Error: Invalid position." << endl;
        return;
    }
    if(TOTAL_MAX == dataStructure_size) {
        cout << "Error: Full List." << endl;
        return;
    }

    for(int i = dataStructure_size; i > position; i--) {
        clients[i] = clients[i - 1];
    }

    clients[position] = client;
    dataStructure_size++;
}
int StaticList::searchList(unsigned key) {
    int index = -1;
    unsigned position = 0;

    while(position < dataStructure_size) {
        if(clients[position].key == key) {
            index = position;
            position = dataStructure_size;
        }

        position++;
    }

    return index;
}
void StaticList::deleteList(unsigned key ) {
    int position = 0;

    position = searchList(key);

    if(position >= 0) {
        dataStructure_size--;
        
        for(unsigned i = position; i < dataStructure_size; i++) {
            clients[i] = clients[i + 1];
        }
    }
}
// HEAP
// CRIA UM HEAP
void StaticList::createHeap() {
    unsigned mid = dataStructure_size / 2;
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

    eachStep();

    memoryAcess_heapfy += 1;
    storeValueArrayheapfy(memoryAcess_heapfy, arr_heapfy);
    
    if((left <= dataStructure_size) && (clients[left].key > clients[i].key)) {
        majorElement = left;
        memoryAcess_heapfy += 2;
    } else { 
        majorElement = i; 
        memoryAcess_heapfy += 2;
        }
    if((right <= dataStructure_size) && (clients[right].key > clients[majorElement].key)) {
        majorElement = right;
        memoryAcess_heapfy += 2;
    }
    if (majorElement != i) {
        swap(clients[i], clients[majorElement]);
        memoryAcess_heapfy += 3;
        heapfy(majorElement);
    }
}
void StaticList::heapSort() {
    dataStructure_size_aux = dataStructure_size; 
    
    // DESLOCA OS ELEMENTOS DA ESQUERDA PARA A DIREITA PARA TRANSFORMAR A LISTA EM UM HEAP
    for(unsigned i = dataStructure_size; i > 0; i--) { swap(clients[i], clients[i - 1]); }
    
    // MOSTRA OS PASSOS PARA TRANSFORMAR A LISTA EM HEAP
    cout << "Each Step (createHeap - heapfy):" << endl; 
    createHeap();
    cout << endl << "Heap:\t\t\t\t\t\t\t"; printList(dataStructure_size+1);
    
    memoryAcess_heapSort += 1;

    // MOSTRA O HEAP SENDO ORDENADO
    cout << endl << "EachStep (heapSort - heapFy):" << endl;
    for(unsigned i = dataStructure_size_aux; i != 0; i--) {
        dataStructure_size--;
        
        memoryAcess_heapSort += 3;
        swap(clients[1], clients[i]);
        
        memoryAcess_heapSort += 1;
        heapfy(1);
        
        storeValueArrayheapSort(memoryAcess_heapSort, arr_heapSort);
    }
    dataStructure_size = dataStructure_size_aux;

    // RESTAURA AS POSIÇÕES DOS ELEMENTOS (DESEJA-SE APENAS ORDENAR)
    for(unsigned i = 0; i < dataStructure_size; i++) { swap(clients[i], clients[i + 1]); }
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
        
        dataStructure_size++;
    }
}
bool StaticList::isRandomKey(unsigned randomKey) {
    for(unsigned i = 0; i < dataStructure_size; i++) {
        if(clients[i].key == randomKey) {
            return true;
        }
    }
    
    return false;
}
void StaticList::eachStep() {
    static unsigned counter = 1;
    cout << "" << counter << ".\t\t\t\t\t\t\t\t"; printList(dataStructure_size_aux+1);
    counter++;
}
void StaticList::storeValueArrayheapSort(unsigned num_memoryAcess, unsigned arr[]) {
    static unsigned index = 0;
    
    if(index < dataStructure_size_aux) {
        arr[index] += num_memoryAcess;
        index++;
    } else { index = 0; }
}
void StaticList::storeValueArrayheapfy(unsigned num_memoryAcess, unsigned arr[]) {
    static unsigned index = 0;
    
    if(index < dataStructure_size_aux) {
        arr[index] += num_memoryAcess;
        index++;
    } else { index = 0; }
}
void StaticList::printMemoryAcessList() {
    cout << endl <<"- Array of memory acesses in heapSort function:" << endl;
    for(unsigned i = 0; i < dataStructure_size; i++) {
        total_memoryAcess_heapSort += arr_heapSort[i];
        cout << arr_heapSort[i] << " ";
    }
    cout << endl << endl;
    cout <<"- Array of memory acesses in heapfy function:" << endl;
    for(unsigned i = 0; i < dataStructure_size; i++) {
        total_memoryAcess_heapfy += arr_heapfy[i];
        cout << arr_heapfy[i] << " ";
    }
    cout << endl << endl;
     cout << "- Memory acesses on the list during heapSort function:" << endl << total_memoryAcess_heapSort << endl;
    cout << endl << "- Memory acesses on the list during heapfy function:"<< endl << total_memoryAcess_heapfy << endl;
    
    cout << endl << "> Array of total memory acesses:" << endl;
    for(unsigned i = 0; i < dataStructure_size; i++) {
        arr_totalMemoryAcess[i] = arr_heapSort[i] + arr_heapfy[i];
        cout << arr_totalMemoryAcess[i] << " ";
    }
    cout << endl << endl;
    
    total_memoryAcess = total_memoryAcess_heapSort + total_memoryAcess_heapfy;
    
    cout << "> Total of memoryAcess in heapSort algorithm:" << endl << total_memoryAcess << endl;
    
    cout << endl << "- Acumulator Array of memory acesses value:" << endl;
    for(unsigned i = 0; i < dataStructure_size; i++) {
        arr_acumulatorMemoryAcess[i] = acumulator_memoryAcess + arr_totalMemoryAcess[i];
        acumulator_memoryAcess = arr_acumulatorMemoryAcess[i];
        cout << arr_acumulatorMemoryAcess[i] << " ";
    }
    cout << endl;
}