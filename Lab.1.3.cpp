#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

class Entity {
protected:
    std::string m_name;
    int m_health;
    int m_attack;
    int m_defense;

public:
    Entity(const std::string& n, int h, int a, int d)
        : m_name(n), m_health(h), m_attack(a), m_defense(d) {}

    const std::string& getName() const { return m_name; }
    int getHealth() const { return m_health; }
    int getAttack() const { return m_attack; }
    int getDefense() const { return m_defense; }

    virtual void attack(Entity& target) {
        int damage = getAttack() - target.getDefense();
        if (damage > 0) {
            target.heal(-damage);
            std::cout << getName() << " attacks " << target.getName() << " for " << damage << " damage!\n";
        } else {
            std::cout << getName() << " attacks " << target.getName() << ", but it has no effect!\n";
        }
    }

    virtual void displayInfo() const {
        std::cout << "Name: " << getName() << ", HP: " << getHealth()
                  << ", Attack: " << getAttack() << ", Defense: " << getDefense() << std::endl;
    }

    virtual void heal(int amount) {
    }

    virtual ~Entity() {}
};

class Character : public Entity {
public:
    Character(const std::string& n, int h, int a, int d)
        : Entity(n, h, a, d) {}

    void attack(Entity& target) override {
        int damage = getAttack() - target.getDefense();
        if (damage > 0) {
            if (rand() % 100 < 20) {
                damage *= 2;
                std::cout << "Critical hit! ";
            }
            target.heal(-damage);
            std::cout << getName() << " attacks " << target.getName() << " for " << damage << " damage!\n";
        } else {
            std::cout << getName() << " attacks " << target.getName() << ", but it has no effect!\n";
        }
    }

    void displayInfo() const override {
        std::cout << "Character: " << getName() << ", HP: " << getHealth()
                  << ", Attack: " << getAttack() << ", Defense: " << getDefense() << std::endl;
    }

    void heal(int amount) override {
        m_health += amount;
        std::cout << getName() << " heals for " << amount << " HP! Current HP: " << getHealth() << std::endl;
    }
};

class Monster : public Entity {
public:
    Monster(const std::string& n, int h, int a, int d)
        : Entity(n, h, a, d) {}

    void attack(Entity& target) override {
        int damage = getAttack() - target.getDefense();
        if (damage > 0) {
            if (rand() % 100 < 30) {
                damage += 5;
                std::cout << "Poisonous attack! ";
            }
            target.heal(-damage);
            std::cout << getName() << " attacks " << target.getName() << " for " << damage << " damage!\n";
        } else {
            std::cout << getName() << " attacks " << target.getName() << ", but it has no effect!\n";
        }
    }

    void displayInfo() const override {
        std::cout << "Monster: " << getName() << ", HP: " << getHealth()
                  << ", Attack: " << getAttack() << ", Defense: " << getDefense() << std::endl;
    }
};

class Boss : public Monster {
public:
    Boss(const std::string& n, int h, int a, int d)
        : Monster(n, h, a, d) {}

    void attack(Entity& target) override {
        int damage = getAttack() - target.getDefense();
        if (damage > 0) {
            if (rand() % 100 < 25) {
                damage += 10;
                std::cout << "Fire strike! ";
            }
            target.heal(-damage);
            std::cout << getName() << " attacks " << target.getName() << " for " << damage << " damage!\n";
        } else {
            std::cout << getName() << " attacks " << target.getName() << ", but it has no effect!\n";
        }
    }

    void displayInfo() const override {
        std::cout << "Boss: " << getName() << ", HP: " << getHealth()
                  << ", Attack: " << getAttack() << ", Defense: " << getDefense() << std::endl;
    }
};

int main() {
    srand(static_cast<unsigned>(time(0)));

    Character hero("Hero", 100, 20, 10);
    Monster goblin("Goblin", 50, 15, 5);
    Monster dragon("Dragon", 150, 25, 20);
    Boss evilBoss("Evil Boss", 200, 30, 15);

    Entity* entities[] = {&hero, &goblin, &dragon, &evilBoss};

    std::cout << "=== Game Entities ===\n";
    for (auto& entity : entities) {
        entity->displayInfo();
    }

    std::cout << "\n=== Battle Phase ===\n";
    hero.attack(goblin);
    goblin.attack(hero);
    dragon.attack(hero);
    evilBoss.attack(hero);

    std::cout << "\n=== Healing Phase ===\n";
    hero.heal(30);

    return 0;
}
