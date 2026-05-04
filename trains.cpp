#include "trains.h"
#include <iostream>
#include <algorithm>
using namespace std;

map<string, Train> trains;
map<string, set<string>> townToTrains;

Command parseCommand(const string& cmd) {
    string upper = cmd;
    transform(upper.begin(), upper.end(), upper.begin(), ::toupper);
    
    if (upper == "CREATE_TRAIN") return Command::CREATE_TRAIN;
    if (upper == "TRAINS_FOR_TOWN") return Command::TRAINS_FOR_TOWN;
    if (upper == "TOWNS_FOR_TRAIN") return Command::TOWNS_FOR_TRAIN;
    if (upper == "TRAINS") return Command::TRAINS;
    
    return Command::UNKNOWN;  // неизвестная команда
}

void createTrain(const string& name, const vector<string>& towns) {
    // Проверка: поезд уже существует?
    if (trains.find(name) != trains.end()) {
        cout << "Ошибка: Поезд с именем " << name << " уже создан\n";
        return;
    }
    
    // Проверка: количество городов >= 2?
    if (towns.size() < 2) {
        cout << "Ошибка: Поезд должен проходить минимум через 2 города\n";
        return;
    }
    
    // Проверка: нет повторяющихся подряд городов?
    for (size_t i = 0; i < towns.size() - 1; i++) {
        if (towns[i] == towns[i + 1]) {
            cout << "Ошибка: Поезд не может проходить дважды подряд через один город\n";
            return;
        }
    }
    
    // Сохраняем поезд
    trains[name] = {name, towns};
    
    // Обновляем индекс город -> поезда
    for (const string& town : towns) {
        townToTrains[town].insert(name);
    }
    
    // Вывод сообщения об успехе
    cout << "Поезд " << name << " создан\n";
}

void trainsForTown(const string& town) {
    auto it = townToTrains.find(town);
    if (it == townToTrains.end() || it->second.empty()) {
        cout << "Ошибка: Город " << town << " не найден\n";
        return;
    }
    
    cout << "Поезда через город " << town << ": ";
    bool first = true;
    for (const string& trainName : it->second) {
        if (!first) cout << ", ";
        cout << trainName;
        first = false;
    }
    cout << "\n";
}

void townsForTrain(const string& name) {
    auto it = trains.find(name);
    if (it == trains.end()) {
        cout << "Ошибка: Поезд " << name << " не найден\n";
        return;
    }
    
    const Train& train = it->second;
    cout << "Города поезда " << name << ": ";
    for (size_t i = 0; i < train.towns.size(); i++) {
        cout << train.towns[i];
        if (i < train.towns.size() - 1) cout << " -> ";
    }
    cout << "\n";
    
    // Для каждого города выводим другие поезда
    cout << "\n--- Другие поезда по городам ---\n";
    for (const string& town : train.towns) {
        cout << "Город " << town << ": ";
        auto it2 = townToTrains.find(town);
        if (it2 != townToTrains.end()) {
            bool first = true;
            for (const string& otherTrain : it2->second) {
                if (otherTrain != name) {
                    if (!first) cout << ", ";
                    cout << otherTrain;
                    first = false;
                }
            }
            if (first) cout << "нет других поездов";
        } else {
            cout << "нет других поездов";
        }
        cout << "\n";
    }
}

void listAllTrains() {
    if (trains.empty()) {
        cout << "Ошибка: Поезда не найдены\n";
        return;
    }
    
    cout << "\n=== СПИСОК ВСЕХ ПОЕЗДОВ ===\n";
    for (const auto& pair : trains) {
        const Train& train = pair.second;
        cout << "Поезд " << train.name << ": ";
        for (size_t i = 0; i < train.towns.size(); i++) {
            cout << train.towns[i];
            if (i < train.towns.size() - 1) cout << " -> ";
        }
        cout << "\n";
    }
    cout << "===========================\n";
}

bool trainExists(const string& name) {
    return trains.find(name) != trains.end();
}
