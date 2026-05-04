#include "friends.h"
#include <iostream>
using namespace std;

map<string, set<string>> friendships;

void addFriends(const string& person1, const string& person2) {
    if (person1 == person2) {
        cout << "Ошибка: Нельзя добавить дружбу с самим собой\n";
        return;
    }
    
    if (friendships[person1].count(person2)) {
        cout << person1 << " и " << person2 << " уже друзья\n";
        return;
    }
    
    friendships[person1].insert(person2);
    friendships[person2].insert(person1);
    cout << person1 << " и " << person2 << " теперь друзья\n";
}

int countFriends(const string& person) {
    auto it = friendships.find(person);
    if (it == friendships.end()) return 0;
    return it->second.size();
}

bool areFriends(const string& person1, const string& person2) {
    if (person1 == person2) return true;
    auto it = friendships.find(person1);
    if (it == friendships.end()) return false;
    return it->second.count(person2) > 0;
}
