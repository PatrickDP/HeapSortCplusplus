#include "client.hpp"

using namespace std;

Client::Client(unsigned newKey, const string &newName) {
    key = newKey;
    name = newName;
}
Client::Client() {
    key = 0;
    name = "Dummy";
}
Client::~Client() {}

void Client::printClient() { 
    cout << key << "  ";
}