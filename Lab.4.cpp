#include <iostream>
#include <string>
#include <memory>
#include <vector>
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

    virtual void attack(Entity& target) {
        int damage = m_attack - target.getDefense();
        if (damage > 0) {
            target.m_health -= damage;
            std::cout << m_name << " attacks " << target.getName() << " for " << damage << " damage!\n";
        } else {
            std::cout << m_name << " attacks " << target.getName() << ", but it has no effect!\n";
        }
    }

    virtual void displayInfo() const {
        std::cout << "Name: " << m_name << ", HP: " << m_health
                  << ", Attack: " << m_attack << ", Defense: " << m_defense << std::endl;
    }

    virtual void heal(int amount) {
    }

    virtual ~Entity() {}

    const std::string& getName() const { return m_name; }
    int getHealth() const { return m_health; }
    int getAttack() const { return m_attack; }
    int getDefense() const { return m_defense; }
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

class Inventory {
private:
    std::unique_ptr<std::string[]> items; 
    size_t capacity;                      
    size_t count;                       

public:
    Inventory(size_t initialCapacity = 4)
        : capacity(initialCapacity), count(0) {
        items = std::make_unique<std::string[]>(capacity);
    }

    void addItem(const std::string& item) {
        if (count >= capacity) {
            capacity *= 2;
            auto newItems = std::make_unique<std::string[]>(capacity);
            
                 for (size_t i = 0; i < count; ++i) {
                newItems[i] = items[i];
            }
            
               items = std::move(newItems);
        }
        
        items[count++] = item;
        std::cout << "Added " << item << " to inventory\n";
    }

    void displayInventory() const {
        std::cout << "\nInventory contents (" << count << " items):\n";
        for (size_t i = 0; i < count; ++i) {
            std::cout << "- " << items[i] << "\n";
        }
    }
};

int main() {
    srand(static_cast<unsigned>(time(0)));

    std::cout << "=== Polymorphic entities with smart pointers ===\n";
    std::vector<std::unique_ptr<Entity>> entities;
    
    entities.push_back(std::make_unique<Character>("Hero", 100, 20, 10));
    entities.push_back(std::make_unique<Monster>("Goblin", 50, 15, 5));
    entities.push_back(std::make_unique<Boss>("Evil Boss", 200, 30, 15));

    for (const auto& entity : entities) {
        entity->displayInfo();
    }

    std::cout << "\n=== Battle Phase ===\n";
    entities[0]->attack(*entities[1]);
    entities[1]->attack(*entities[0]);
    entities[2]->attack(*entities[0]);

    std::cout << "\n=== Healing Phase ===\n";
    if (Character* hero = dynamic_cast<Character*>(entities[0].get())) {
        hero->heal(30);
    }

    std::cout << "\n=== Inventory System ===";
    
    auto playerInventory = std::make_unique<Inventory>();
    
    playerInventory->addItem("Sword");
    playerInventory->addItem("Shield");
    playerInventory->addItem("Health Potion");
    playerInventory->addItem("Mana Potion");
    playerInventory->addItem("Magic Ring");
    playerInventory->addItem("Golden Coin");
    
    playerInventory->displayInventory();

    return 0;
}
