#include <iostream>
#include <string>

class Weapon {
private:
    std::string name;
    int damage;
    int weight;

public:
    Weapon(const std::string& n, int d, int w)
        : name(n), damage(d), weight(w) {
        std::cout << "Weapon " << name << " created!\n";
    }

    ~Weapon() {
        std::cout << "Weapon " << name << " destroyed!\n";
    }

    void displayInfo() const {
        std::cout << "Weapon: " << name 
                  << ", Damage: " << damage 
                  << ", Weight: " << weight << std::endl;
    }
};

int main() {
    Weapon sword("Excalibur", 30, 5);
    Weapon bow("Longbow", 20, 3);

    sword.displayInfo();
    bow.displayInfo();

    return 0;
}