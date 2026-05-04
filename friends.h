#pragma once
#include <string>
#include <map>
#include <set>
using namespace std;

// Хранилище дружеских связей: человек -> множество его друзей
extern map<string, set<string>> friendships;

void addFriends(const string& person1, const string& person2);
int countFriends(const string& person);
bool areFriends(const string& person1, const string& person2);
void showAll();
