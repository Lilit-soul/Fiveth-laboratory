#pragma once
#include <string>
#include <vector>
#include <stack>
#include <list>
using namespace std;

struct Container {
    string id;
    int weight;
};

extern int maxStackWeight;
extern int numSections;
extern vector<stack<Container>> stacks;
extern list<Container> waitingContainers;
extern int nextContainerNum;

void init(int maxWeight, int sections);
void arrive(const string& id, int weight);
void load();
void showStacks();
string generateContainerId();
