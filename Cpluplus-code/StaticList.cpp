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
unsigned StaticList::leftSon(unsigned i) { memoryAcess_counter += 1; return (2 * i);  }
unsigned StaticList::rightSon(unsigned i) { memoryAcess_counter += 1; return (2 * i) + 1; }
// RESTAURA A PROPRIEDADE DE HEAP
void StaticList::heapfy(unsigned i) {
    memoryAcess_counter += 1;

    memoryAcess_counter += 1;
    unsigned left = leftSon(i);

    memoryAcess_counter += 1;
    unsigned right = rightSon(i);
    
    unsigned majorElement = 0;

    eachStep();
    
    if((left <= dataStructure_size) && (clients[left].key > clients[i].key)) {
        memoryAcess_counter += 4;
        majorElement = left;
    } else {
        majorElement = i; 
        }
    if((right <= dataStructure_size) && (clients[right].key > clients[majorElement].key)) {
        memoryAcess_counter += 4;
        majorElement = right;
    }
    if (majorElement != i) {
        memoryAcess_counter += 4;
        swap(clients[i], clients[majorElement]);
        heapfy(majorElement);
    }
}
void StaticList::heapSort() {
    memoryAcess_counter += 1;

    dataStructure_size_aux = dataStructure_size; 
    
    // DESLOCA OS ELEMENTOS DA ESQUERDA PARA A DIREITA PARA TRANSFORMAR A LISTA EM UM HEAP
    for(unsigned i = dataStructure_size; i > 0; i--) { swap(clients[i], clients[i - 1]); }
    
    // MOSTRA OS PASSOS PARA TRANSFORMAR A LISTA EM HEAP
    cout << "Each Step (createHeap - heapfy):" << endl; 

    memoryAcess_counter += 1;
    createHeap();
    
    // IMPRIMI UM HEAP
    cout << endl << "Heap:\t\t\t\t\t\t\t"; printList(dataStructure_size+1);

    // MOSTRA O HEAP SENDO ORDENADO
    cout << endl << "EachStep (heapSort - heapFy):" << endl;
    for(unsigned i = dataStructure_size_aux; i != 0; i--) {
        dataStructure_size--;
        
        memoryAcess_counter += 4;
        swap(clients[1], clients[i]);
        heapfy(1);   
        
        storeValueArrayMemory(memoryAcess_counter);
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
void StaticList::storeValueArrayMemory(unsigned num_memoryAcess) {
    static unsigned index = 0;
    
    if(index < dataStructure_size_aux) {
        arr_memoryAcess[index] += num_memoryAcess;
        index++;
    } else { index = 0; }
}
void StaticList::printMemoryAcessList() {
    cout << endl <<"- Array of memory acesses:" << endl;
    for(unsigned i = 0; i < dataStructure_size; i++) {
        total_memoryAcess += arr_memoryAcess[i];
        cout << arr_memoryAcess[i] << " ";
    }
    cout << endl << endl << "> Total of memoryAcess in heapSort algorithm:" << endl << total_memoryAcess << endl;
    
    cout << endl << "- Acumulator Array of memory acesses value:" << endl;
    for(unsigned i = 0; i < dataStructure_size; i++) {
        arr_acumulatorMemoryAcess[i] = acumulator_memoryAcess + arr_memoryAcess[i];
        acumulator_memoryAcess = arr_acumulatorMemoryAcess[i];
        cout << arr_acumulatorMemoryAcess[i] << " ";
    }
    cout << endl;
}