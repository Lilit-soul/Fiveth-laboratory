#include "port.h"
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

int main() {
    int maxWeight, sections;
    
    cout << "Введите максимальный вес стека: ";
    cin >> maxWeight;
    cout << "Введите количество секций судна: ";
    cin >> sections;
    cin.ignore();
    
    init(maxWeight, sections);
    
    cout << "\nДоступные команды:\n";
    cout << "  ARRIVE <вес> - прибытие контейнера (ID генерируется автоматически)\n";
    cout << "  ARRIVE <ID> <вес> - прибытие контейнера с указанным ID\n";
    cout << "  LOAD - распределить контейнеры на секции судна\n";
    cout << "  STACKS - показать текущее состояние стеков\n";
    cout << "  EXIT - выход\n\n";
    
    string line;
    while (true) {
        cout << ">>> ";
        getline(cin, line);
        
        string cmd = line;
        transform(cmd.begin(), cmd.end(), cmd.begin(), ::toupper);
        
        if (cmd == "EXIT") {
            cout << "Выход из программы.\n";
            break;
        }
        
        if (cmd == "LOAD") {
            load();
            continue;
        }
        
        if (cmd == "STACKS") {
            showStacks();
            continue;
        }
        
        if (cmd.substr(0, 6) == "ARRIVE") {
            stringstream ss(line);
            string action;
            string idOrWeight;
            int weight;
            
            ss >> action >> idOrWeight;
            
            // Проверяем, указан ли ID или только вес
            if (idOrWeight[0] == 'C' || idOrWeight[0] == 'c') {
                // Указан ID
                ss >> weight;
                if (weight <= 0) {
                    cout << "Ошибка: Вес должен быть положительным\n";
                    continue;
                }
                arrive(idOrWeight, weight);
            } else {
                // Только вес, ID генерируем
                weight = stoi(idOrWeight);
                if (weight <= 0) {
                    cout << "Ошибка: Вес должен быть положительным\n";
                    continue;
                }
                string id = generateContainerId();
                arrive(id, weight);
            }
            continue;
        }
        
        cout << "Неизвестная команда. Доступны: ARRIVE, LOAD, STACKS, EXIT\n";
    }
    
    return 0;
}
