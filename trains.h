#pragma once
#include <string>
#include <vector>
#include <map>
#include <set>
using namespace std;

// Структура для хранения маршрута поезда
struct Train {
    string name;
    vector<string> towns;
};

enum class Command {
    CREATE_TRAIN,
    TRAINS_FOR_TOWN,
    TOWNS_FOR_TRAIN,
    TRAINS,
    UNKNOWN
};

extern map<string, Train> trains;           // все поезда: ключ - имя поезда
extern map<string, set<string>> townToTrains; // город -> список поездов

Command parseCommand(const string& cmd);

void createTrain(const string& name, const vector<string>& towns);
void trainsForTown(const string& town);
void townsForTrain(const string& name);
void listAllTrains();
bool trainExists(const string& name);
