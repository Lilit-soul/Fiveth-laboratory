#include "warehouse.h"
#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;

map<string, Cell> warehouse;
set<string> allAddresses;
const int MAX_PER_CELL = 10;
int totalCells = 0, totalCapacity = 0;

// Параметры варианта 6
const char ZONES[3] = {'A', 'B', 'C'};
const int RACKS = 16;
const int SECTIONS = 8;
const int SHELVES = 6;  // 23040 / 3 / 16 / 8 / 10 = 6

void generateAddresses() {
    for (char z : ZONES)
        for (int r = 1; r <= RACKS; ++r)
            for (int s = 1; s <= SECTIONS; ++s)
                for (int sh = 1; sh <= SHELVES; ++sh) {
                    stringstream ss; ss << z << r << s << sh; // Создаём строковый поток и записываем значения адреса
                    allAddresses.insert(ss.str()); // Сохраняем адрес в виде строки в список
                }
    totalCells = allAddresses.size();
    totalCapacity = totalCells * MAX_PER_CELL;
}

void init() {
    warehouse.clear();
    generateAddresses();
}

// Вывод адреса
bool exists(const string& addr) {
    return allAddresses.find(addr) != allAddresses.end();
}

// Добавление товаров
void add(const string& name, int qty, const string& addr) {
    // Проверка существования адреса
    if (!exists(addr)) {
        cout << "Ошибка: Адрес " << addr << " не существует в конфигурации склада\n";
        return;
    }
    
    // Проверка положительного количества
    if (qty <= 0) {
        cout << "Ошибка: Количество должно быть положительным\n";
        return;
    }
    
    // Проверка вместимости ячейки
    if (qty > MAX_PER_CELL) {
        cout << "Ошибка: Превышена вместимость ячейки (максимум " << MAX_PER_CELL << " единиц)\n";
        return;
    }
    
    auto it = warehouse.find(addr);
    
    // Ячейка пуста
    if (it == warehouse.end()) {
        warehouse[addr] = {name, qty};
        cout << "Добавлено " << qty << " " << name << " в " << addr << "\n";
        return;
    }
    
    // Ячейка занята другим товаром
    if (it->second.name != name) {
        cout << "Ошибка: Ячейка " << addr << " занята товаром " << it->second.name << "\n";
        return;
    }
    
    // Проверка на превышение вместимости при добавлении
    if (it->second.qty + qty > MAX_PER_CELL) {
        cout << "Ошибка: Превышена вместимость ячейки (максимум " << MAX_PER_CELL 
             << ", сейчас " << it->second.qty << ")\n";
        return;
    }
    
    // Успешное добавление
    it->second.qty += qty;
    cout << "Добавлено " << qty << " " << name << " в " << addr 
         << " (теперь " << it->second.qty << ")\n";
}

// Удаление товара
void remove(const string& name, int qty, const string& addr) {
    // Проверка существования адреса
    if (!exists(addr)) {
        cout << "Ошибка: Адрес " << addr << " не существует в конфигурации склада\n";
        return;
    }
    
    // Проверка положительного количества
    if (qty <= 0) {
        cout << "Ошибка: Количество должно быть положительным\n";
        return;
    }
    
    auto it = warehouse.find(addr);
    
    // Проверка, что ячейка не пуста
    if (it == warehouse.end()) {
        cout << "Ошибка: Ячейка " << addr << " пуста\n";
        return;
    }
    
    // Проверка, что товар совпадает
    if (it->second.name != name) {
        cout << "Ошибка: Товар " << name << " не найден в ячейке " << addr 
             << " (там " << it->second.name << ")\n";
        return;
    }
    
    // Проверка достаточности количества
    if (it->second.qty < qty) {
        cout << "Ошибка: Недостаточно товаров для удаления (есть " 
             << it->second.qty << ", запрошено " << qty << ")\n";
        return;
    }
    
    // Успешное удаление
    it->second.qty -= qty;
    if (it->second.qty == 0) {
        warehouse.erase(it);
        cout << "Удалено " << qty << " " << name << " из " << addr 
             << " (ячейка освобождена)\n";
    } else {
        cout << "Удалено " << qty << " " << name << " из " << addr 
             << " (остаток: " << it->second.qty << ")\n";
    }
}

// Информация о состоянии склада 
void info() {
    int occupied = warehouse.size();
    int totalProducts = 0;
    for (auto& p : warehouse) totalProducts += p.second.qty;
    
    double overallLoad = (static_cast<double>(totalProducts) / totalCapacity) * 100.0;
    
    cout << fixed << setprecision(2);
    cout << "\n========== СОСТОЯНИЕ СКЛАДА ==========\n";
    cout << "Загруженность склада: " << overallLoad << " %\n";
    cout << "Всего ячеек: " << totalCells << ", занято: " << occupied 
         << ", свободно: " << (totalCells - occupied) << "\n";
    cout << "Всего единиц товара: " << totalProducts << " из " << totalCapacity << "\n";
    
    // Загруженность по зонам
    cout << "\n--- Загруженность по зонам ---\n";
    for (char z : ZONES) {
        int zoneProducts = 0, zoneCells = 0, zoneCapacity = 0;
        for (const string& addr : allAddresses) {
            if (addr[0] == z) {
                zoneCells++;
                zoneCapacity += MAX_PER_CELL;
                auto it = warehouse.find(addr);
                if (it != warehouse.end()) zoneProducts += it->second.qty;
            }
        }
        double zoneLoad = (zoneCells > 0) ? (zoneProducts * 100.0 / zoneCapacity) : 0.0;
        cout << "Зона " << z << ": " << zoneLoad << " % (товаров: " << zoneProducts 
             << "/" << zoneCapacity << ")\n";
    }
    
    // Заполненные ячейки
    cout << "\n--- Заполненные ячейки ---\n";
    if (warehouse.empty()) {
        cout << "Нет заполненных ячеек\n";
    } else {
        for (auto& p : warehouse) {
            cout << p.first << ": " << p.second.name << " (" << p.second.qty << ")\n";
        }
    }
    
    // Пустые ячейки (первые 20 для читаемости)
    cout << "\n--- Пустые ячейки ---\n";
    int cnt = 0;
    for (const string& addr : allAddresses) {
        if (warehouse.find(addr) == warehouse.end()) {
            cout << addr;
            if (++cnt < 20) cout << ", ";
            else break;
        }
    }
    if (cnt == 0) {
        cout << "Нет пустых ячеек";
    } else if (allAddresses.size() - occupied > 20) {
        cout << "... и ещё " << (allAddresses.size() - occupied - 20) << " ячеек";
    }
    cout << "\n=====================================\n";
}
