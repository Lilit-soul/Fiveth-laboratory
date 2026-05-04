#include "ui.h"
#include "friends.h"
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

void runInterface() {
    cout << "Команды: FRIENDS, COUNT, QUESTION\n\n";
    
    int N;
    cout << "Введите количество запросов (N): ";
    cin >> N;
    cin.ignore();
    cout << "\n";
    
    for (int i = 0; i < N; i++) {
        string line;
        cout << ">>> ";
        getline(cin, line);
        
        stringstream ss(line);
        string cmd;
        ss >> cmd;
        
        string cmdUpper = cmd;
        transform(cmdUpper.begin(), cmdUpper.end(), cmdUpper.begin(), ::toupper);
        
        if (cmdUpper == "FRIENDS") {
            string p1, p2;
            ss >> p1 >> p2;
            if (p1.empty() || p2.empty()) {
                cout << "Ошибка: Укажите двух человек\n";
            } else {
                addFriends(p1, p2);
            }
        }
        else if (cmdUpper == "COUNT") {
            string person;
            ss >> person;
            if (person.empty()) {
                cout << "Ошибка: Укажите человека\n";
            } else {
                cout << countFriends(person) << "\n";
            }
        }
        else if (cmdUpper == "QUESTION") {
            string p1, p2;
            ss >> p1 >> p2;
            if (p1.empty() || p2.empty()) {
                cout << "Ошибка: Укажите двух человек\n";
            } else {
                cout << (areFriends(p1, p2) ? "Yes" : "No") << "\n";
            }
        }
        else {
            cout << "Неизвестная команда\n";
        }
    }
}
