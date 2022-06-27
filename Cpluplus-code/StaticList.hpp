#pragma once

#include <iostream>
#include <cmath>
#include "client.hpp"

using namespace std;

#define TOTAL_MAX 100

class StaticList {
public:
    // RESPONSÁVEL EM SER AO MESMO TEMPO O TAMANHO DE UMA LISTA OU HEAP (CONFORME A PASSAGEM DE PARAMETRO POR EACHSTEP)
    unsigned dataStructure_size = 0;
    unsigned dataStructure_size_aux = 0;
    
    Client clients[TOTAL_MAX + 1];
    
    unsigned memoryAcess_counter = 0;
    unsigned arr_memoryAcess[TOTAL_MAX + 1] = {};
    unsigned total_memoryAcess = 0;
    unsigned acumulator_memoryAcess = 0;
    unsigned arr_acumulatorMemoryAcess[TOTAL_MAX + 1] = {};
    
    StaticList();
    ~StaticList();

    void printList(unsigned dataStructure_size);
    void addList(unsigned position, const Client & client);
    int searchList(unsigned key);
    void deleteList(unsigned key);
    

    void createHeap();
    unsigned parent(unsigned i);
    unsigned leftSon(unsigned i);
    unsigned rightSon(unsigned i);
    void heapfy(unsigned i);
    void heapSort();

    void randomList();
    bool isRandomKey(unsigned randomKey);
    
    void eachStep();
    void storeValueArrayMemory(unsigned num_memoryAcess);
    void printMemoryAcessList();
};