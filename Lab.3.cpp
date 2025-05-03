#include <iostream>
#include <string>

class Weapon {
private:
    std::string name;
    int damage;

public:
    Weapon(const std::string& n, int d) : name(n), damage(d) {}

    // Перегрузка оператора +
    Weapon operator+(const Weapon& other) const {
        return Weapon(name + "+" + other.name, damage + other.damage);
    }

    // Перегрузка оператора >
    bool operator>(const Weapon& other) const {
        return damage > other.damage;
    }

    // Метод для вывода информации
    void display() const {
        std::cout << name << " (урон: " << damage << ")\n";
    }
};

int main() {
    Weapon sword("Меч", 15);
    Weapon bow("Лук", 10);

    // Демонстрация оператора +
    Weapon hybrid = sword + bow;
    std::cout << "Результат сложения: ";
    hybrid.display();

    // Демонстрация оператора >
    if (sword > bow) {
        std::cout << "Меч сильнее лука\n";
    } else {
        std::cout << "Лук сильнее меча\n";
    }

    return 0;
}