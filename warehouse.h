#pragma once
#include <string>
#include <map>
#include <set>
using namespace std;

struct Cell {
    string name;
    int qty;
};

extern map<string, Cell> warehouse;
extern set<string> allAddresses;
extern const int MAX_PER_CELL;
extern int totalCells, totalCapacity;

void init();
void add(const string& name, int qty, const string& addr);
void remove(const string& name, int qty, const string& addr);
void info();
