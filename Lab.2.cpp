#include <iostream>
#include <string>

class Character {
private:
    std::string name;
    int health;
    int attack;
    int defense;

public:
    Character(const std::string& n, int h, int a, int d)
        : name(n), health(h), attack(a), defense(d) {
        std::cout << "Character " << name << " created!\n";
    }

    ~Character() {
        std::cout << "Character " << name << " destroyed!\n";
    }

    void displayInfo() const {
        std::cout << "Name: " << name << ", HP: " << health
                  << ", Attack: " << attack << ", Defense: " << defense << std::endl;
    }
};

class Monster {
private:
    std::string name;
    int health;
    int attack;
    int defense;

public:
    Monster(const std::string& n, int h, int a, int d)
        : name(n), health(h), attack(a), defense(d) {
        std::cout << "Monster " << name << " created!\n";
    }

    ~Monster() {
        std::cout << "Monster " << name << " destroyed!\n";
    }

    void displayInfo() const {
        std::cout << "Name: " << name << ", HP: " << health
                  << ", Attack: " << attack << ", Defense: " << defense << std::endl;
    }
};

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
};

int main() {
    std::cout << "=== Creating characters ===" << std::endl;
    Character hero("Arthur", 100, 20, 15);
    Monster dragon("Fire Dragon", 200, 30, 25);

    std::cout << "\n=== Creating weapons ===" << std::endl;
    Weapon sword("Excalibur", 25, 3.5);
    Weapon bow("Elven Bow", 15, 1.8);

    std::cout << "\n=== Displaying information ===" << std::endl;
    hero.displayInfo();
    dragon.displayInfo();
    sword.displayInfo();
    bow.displayInfo();

    std::cout << "\n=== Program ending ===" << std::endl;
    return 0;
}
