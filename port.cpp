#include "port.h"
#include <iostream>
#include <algorithm>
#include <sstream>
using namespace std;

int maxStackWeight;
int numSections;
vector<stack<Container>> stacks;
list<Container> waitingContainers;
int nextContainerNum = 1;

void init(int maxWeight, int sections) {
    maxStackWeight = maxWeight;
    numSections = sections;
    stacks.clear();
    waitingContainers.clear();
    nextContainerNum = 1;
}

// Прибытие контейнеров
void arrive(const string& id, int weight) {
    if (weight > maxStackWeight) {
        cout << "Ошибка: Вес контейнера " << weight << " превышает грузоподъёмность стека (максимум " << maxStackWeight << ")\n";
        return;
    }
    
    // Ищем первый подходящий стек
    for (size_t i = 0; i < stacks.size(); i++) {
        if (stacks[i].empty()) {
            // Пустой стек - можно разместить
            stacks[i].push({id, weight});
            cout << "Контейнер " << id << " размещен в стек " << i + 1 << "\n";
            return;
        }
        
        // Временная сумма (нужно проверить с добавлением)
        int currentSum = 0;
        stack<Container> temp = stacks[i];
        while (!temp.empty()) {
            currentSum += temp.top().weight;
            temp.pop();
        }
        
        if (currentSum + weight <= maxStackWeight) {
            stacks[i].push({id, weight});
            cout << "Контейнер " << id << " размещен в стек " << i + 1 << "\n";
            return;
        }
    }
    
    // Нет подходящего стека - создаём новый
    stack<Container> newStack;
    newStack.push({id, weight});
    stacks.push_back(newStack);
    cout << "Контейнер " << id << " размещен в новом стеке " << stacks.size() << "\n";
}

string generateContainerId() {
    stringstream ss;
    ss << "C" << (nextContainerNum < 10 ? "00" : (nextContainerNum < 100 ? "0" : "")) << nextContainerNum;
    nextContainerNum++;
    return ss.str();
}

void load() {
    if (stacks.empty()) {
        cout << "Ошибка: Нет контейнеров для погрузки\n";
        return;
    }
    
    // Собираем все контейнеры из стеков в порядке LIFO
    vector<Container> allContainers;
    for (auto& st : stacks) {
        while (!st.empty()) {
            allContainers.push_back(st.top());
            st.pop();
        }
    }
    
    // Инициализация секций
    vector<int> sectionWeights(numSections, 0);
    vector<vector<string>> sectionContainers(numSections);
    
    // Распределение контейнеров
    for (const auto& container : allContainers) {
        // Ищем секцию с наименьшим весом
        int bestSection = 0;
        for (int i = 1; i < numSections; i++) {
            if (sectionWeights[i] < sectionWeights[bestSection]) {
                bestSection = i;
            }
        }
        sectionWeights[bestSection] += container.weight;
        sectionContainers[bestSection].push_back(container.id);
    }
    
    // Вывод результата
    cout << "\n=== РАСПРЕДЕЛЕНИЕ КОНТЕЙНЕРОВ ===\n";
    for (int i = 0; i < numSections; i++) {
        cout << "Секция " << i + 1 << " (" << sectionWeights[i] << " тонн): ";
        for (size_t j = 0; j < sectionContainers[i].size(); j++) {
            cout << sectionContainers[i][j];
            if (j < sectionContainers[i].size() - 1) cout << ", ";
        }
        cout << "\n";
    }
    cout << "===================================\n";
    
    // Очищаем стеки
    stacks.clear();
}

void showStacks() {
    cout << "\n=== ТЕКУЩИЕ СТЕКИ ===\n";
    if (stacks.empty()) {
        cout << "Нет контейнеров\n";
    } else {
        for (size_t i = 0; i < stacks.size(); i++) {
            cout << "Стек " << i + 1 << ": ";
            stack<Container> temp = stacks[i];
            vector<string> ids;
            while (!temp.empty()) {
                ids.push_back(temp.top().id);
                temp.pop();
            }
            for (auto it = ids.rbegin(); it != ids.rend(); it++) {
                cout << *it;
                if (it + 1 != ids.rend()) cout << " <- ";
            }
            cout << "\n";
        }
    }
    cout << "==================\n";
}
