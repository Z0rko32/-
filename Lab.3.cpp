#include <iostream>
#include <string>

class Weapon {
private:
    std::string name;
    int damage;
    int weight;

public:
    Weapon(const std::string& n, int d, int w) : name(n), damage(d), weight(w) {}

    // Перегрузка оператора +
    Weapon operator+(const Weapon& other) const {
        return Weapon(name + "+" + other.name, damage + other.damage, weight + other.weight);
    }

    // Перегрузка оператора >
    bool operator>(const Weapon& other) const {
        return damage > other.damage;
    }

    // Метод для вывода информации
    void displayInfo() const {
        std::cout << "Weapon: " << name << ", Damage: " << damage << ", Weight: " << weight << std::endl;
    }
};

int main() {
    Weapon sword("Excalibur", 30, 5);
    Weapon bow("Longbow", 20, 3);

    // Проверка оператора +
    Weapon combined = sword + bow;
    combined.displayInfo(); // Вывод: Weapon: Excalibur+Longbow, Damage: 50, Weight: 8

    // Проверка оператора >
    if (sword > bow) {
        std::cout << "Sword is stronger than bow!" << std::endl;
    } else {
        std::cout << "Bow is stronger than sword!" << std::endl;
    }

    return 0;
}