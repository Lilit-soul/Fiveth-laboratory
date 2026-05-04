#include "trains.h"
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

int main() {
    cout << "Команды: " << endl; 
    cout << "    CREATE_TRAIN <имя> <N> <город1> ... <городN>" << endl;
    cout << "    TRAINS_FOR_TOWN <город> " << endl;
    cout << "    TOWNS_FOR_TRAIN <поезд>" << endl;
    cout << "    TRAINS" << endl;
    cout <<  "    EXIT" << endl;

    
    int N;
    cout << "Введите количество запросов (N): ";
    cin >> N;
    cin.ignore();
    
    for (int i = 0; i < N; i++) {
        string line;
        cout << ">>> ";
        getline(cin, line);
        
        stringstream ss(line);
        string firstWord;
        ss >> firstWord;
        
        //  Получаем команду в виде enum
        Command cmd = parseCommand(firstWord);
        
        //  Обрабатываем через switch
        switch (cmd) {
            case Command::CREATE_TRAIN: {
                string name;
                int n;
                ss >> name >> n;
                
                vector<string> towns;
                for (int j = 0; j < n; j++) {
                    string town;
                    ss >> town;
                    towns.push_back(town);
                }
                createTrain(name, towns);
                break;
            }
            
            case Command::TRAINS_FOR_TOWN: {
                string town;
                ss >> town;
                trainsForTown(town);
                break;
            }
            
            case Command::TOWNS_FOR_TRAIN: {
                string trainName;
                ss >> trainName;
                townsForTrain(trainName);
                break;
            }
            
            case Command::TRAINS:
                listAllTrains();
                break;
            
            case Command::UNKNOWN:
                cout << "Неизвестная команда\n";
                break;
        }
    }
    
    return 0;
}
