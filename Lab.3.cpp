#include <iostream>
#include <string>

class Weapon {
private:
    std::string name;
    int damage;
    double weight;

public:
    Weapon(const std::string& n, int d, double w)
        : name(n), damage(d), weight(w) {
        std::cout << "Weapon " << name << " created!\n";
    }

    ~Weapon() {
        std::cout << "Weapon " << name << " destroyed!\n";
    }

    void displayInfo() const {
        std::cout << "Weapon: " << name 
                  << ", Damage: " << damage 
                  << ", Weight: " << weight << " kg" << std::endl;
    }

    int getDamage() const {
        return damage;
    }

    std::string getName() const {
        return name;
    }

    double getWeight() const {
        return weight;
    }

    Weapon operator+(const Weapon& other) const {
        std::string newName = this->name + "+" + other.name;
        int newDamage = this->damage + other.damage;
        double newWeight = this->weight + other.weight;
        
        return Weapon(newName, newDamage, newWeight);
    }

    bool operator>(const Weapon& other) const {
        return this->damage > other.damage;
    }

    friend std::ostream& operator<<(std::ostream& os, const Weapon& weapon) {
        os << "Weapon: " << weapon.name 
           << ", Damage: " << weapon.damage 
           << ", Weight: " << weapon.weight << " kg";
        return os;
    }
};

int main() {
    std::cout << "=== Создание оружия ===" << std::endl;
    Weapon sword("Sword", 25, 3.5);
    Weapon bow("Bow", 15, 1.8);
    
    std::cout << "\n=== Демонстрация перегрузки операторов ===" << std::endl;
    
    std::cout << "\nИнформация об оружии через оператор <<:" << std::endl;
    std::cout << "Меч: " << sword << std::endl;
    std::cout << "Лук: " << bow << std::endl;

    std::cout << "\nСравнение оружия через оператор >:" << std::endl;
    if (sword > bow) {
        std::cout << "Меч сильнее лука\n";
    } else {
        std::cout << "Лук сильнее меча\n";
    }
    
    if (bow > sword) {
        std::cout << "Лук сильнее меча\n";
    } else {
        std::cout << "Меч сильнее лука\n";
    }
    
    std::cout << "\nСоздание нового оружия через оператор +:" << std::endl;
    Weapon hybrid = sword + bow;
    hybrid.displayInfo();
    
    Weapon hybrid2 = hybrid + hybrid;
    hybrid2.displayInfo();
    
    std::cout << "\n=== Завершение программы ===" << std::endl;
    return 0;
}
