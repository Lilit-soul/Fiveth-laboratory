#include "warehouse.h"
#include <iostream>
#include <sstream>
#include <algorithm>
using namespace std;

int main() {
    init();
    
    cout << "3 зоны, 16 стеллажей, 8 секций, 6 полок\n";
    cout << "Вместимость: 23040 товаров\n";
    cout << "Команды: ADD <товар> <кол-во> <адрес> | REMOVE ... | INFO | EXIT\n\n";
    
    string line;
    while (true) {
        cout << ">>> ";
        getline(cin, line);
        
        string cmd = line;
        transform(cmd.begin(), cmd.end(), cmd.begin(), ::toupper);
        
        if (cmd == "EXIT") break;
        if (cmd == "INFO") { info(); continue; }
        
        string action, name, addr;
        int qty;
        stringstream ss(line);
        ss >> action >> name >> qty >> addr;
        if (action.empty()) continue;
        
        transform(action.begin(), action.end(), action.begin(), ::toupper);
        
        if (action == "ADD") add(name, qty, addr);
        else if (action == "REMOVE") remove(name, qty, addr);
        else cout << "Неизвестно. ADD, REMOVE, INFO, EXIT\n";
    }
    return 0;
}
