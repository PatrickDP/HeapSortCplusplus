#pragma once

#include <iostream>

using namespace std;

class Client {
public:
    unsigned key;
    string name;

    Client(unsigned newKey, const string & newName);
    Client();
    ~Client();

    void printClient();
};