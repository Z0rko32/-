#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdexcept>
#include <cstdlib>
#include <ctime>

using namespace std;

class Entity {
protected:
    string m_name;
    int m_health;
    int m_attack;
    int m_defense;

public:
    Entity(const string& n, int h, int a, int d)
        : m_name(n), m_health(h), m_attack(a), m_defense(d) {}

    virtual void attack(Entity& target) {
        int damage = m_attack - target.getDefense();
        if (damage > 0) {
            target.heal(-damage);
            cout << m_name << " attacks " << target.getName() << " for " << damage << " damage!\n";
        } else {
            cout << m_name << " attacks " << target.getName() << ", but it has no effect!\n";
        }
    }

    virtual void displayInfo() const {
        cout << "Name: " << m_name << ", HP: " << m_health
             << ", Attack: " << m_attack << ", Defense: " << m_defense << endl;
    }

    virtual string getType() const { return "Entity"; }
    virtual int getHealth() const { return m_health; }
    virtual int getAttack() const { return m_attack; }
    virtual int getDefense() const { return m_defense; }
    virtual const string& getName() const { return m_name; }

    virtual void heal(int amount) {
    }

    virtual ~Entity() {}
};

class Character : public Entity {
public:
    Character(const string& n, int h, int a, int d)
        : Entity(n, h, a, d) {}

    void attack(Entity& target) override {
        int damage = getAttack() - target.getDefense();
        if (damage > 0) {
            if (rand() % 100 < 20) {
                damage *= 2;
                cout << "Critical hit! ";
            }
            target.heal(-damage);
            cout << getName() << " attacks " << target.getName() << " for " << damage << " damage!\n";
        } else {
            cout << getName() << " attacks " << target.getName() << ", but it has no effect!\n";
        }
    }

    void displayInfo() const override {
        cout << "Character: " << getName() << ", HP: " << getHealth()
             << ", Attack: " << getAttack() << ", Defense: " << getDefense() << endl;
    }

    void heal(int amount) override {
        m_health += amount;
        cout << getName() << " heals for " << amount << " HP! Current HP: " << getHealth() << endl;
    }

    string getType() const override { return "Character"; }
};

class Monster : public Entity {
public:
    Monster(const string& n, int h, int a, int d)
        : Entity(n, h, a, d) {}

    void attack(Entity& target) override {
        int damage = getAttack() - target.getDefense();
        if (damage > 0) {
            if (rand() % 100 < 30) {
                damage += 5;
                cout << "Poisonous attack! ";
            }
            target.heal(-damage);
            cout << getName() << " attacks " << target.getName() << " for " << damage << " damage!\n";
        } else {
            cout << getName() << " attacks " << target.getName() << ", but it has no effect!\n";
        }
    }

    void displayInfo() const override {
        cout << "Monster: " << getName() << ", HP: " << getHealth()
             << ", Attack: " << getAttack() << ", Defense: " << getDefense() << endl;
    }

    string getType() const override { return "Monster"; }
};

class Boss : public Monster {
public:
    Boss(const string& n, int h, int a, int d)
        : Monster(n, h, a, d) {}

    void attack(Entity& target) override {
        int damage = getAttack() - target.getDefense();
        if (damage > 0) {
            if (rand() % 100 < 25) {
                damage += 10;
                cout << "Fire strike! ";
            }
            target.heal(-damage);
            cout << getName() << " attacks " << target.getName() << " for " << damage << " damage!\n";
        } else {
            cout << getName() << " attacks " << target.getName() << ", but it has no effect!\n";
        }
    }

    void displayInfo() const override {
        cout << "Boss: " << getName() << ", HP: " << getHealth()
             << ", Attack: " << getAttack() << ", Defense: " << getDefense() << endl;
    }

    string getType() const override { return "Boss"; }
};

void saveToFile(const vector<Entity*>& entities, const string& filename) {
    ofstream fout(filename);
    if (!fout) {
        throw runtime_error("Failed to open file for writing.");
    }
    
    for (const auto& entity : entities) {
        fout << entity->getType() << " "
             << entity->getName() << " "
             << entity->getHealth() << " "
             << entity->getAttack() << " "
             << entity->getDefense() << "\n";
    }
}

vector<Entity*> loadFromFile(const string& filename) {
    vector<Entity*> entities;
    ifstream fin(filename);
    
    if (!fin) {
        throw runtime_error("Failed to open file for reading.");
    }
    
    string line;
    while (getline(fin, line)) {
        istringstream iss(line);
        string type, name;
        int health, attack, defense;
        
        if (iss >> type >> name >> health >> attack >> defense) {
            if (type == "Character") {
                entities.push_back(new Character(name, health, attack, defense));
            } else if (type == "Monster") {
                entities.push_back(new Monster(name, health, attack, defense));
            } else if (type == "Boss") {
                entities.push_back(new Boss(name, health, attack, defense));
            } else {
                entities.push_back(new Entity(name, health, attack, defense));
            }
        } else {
            cerr << "Error reading line: " << line << endl;
        }
    }
    return entities;
}

int main() {
    srand(static_cast<unsigned>(time(0)));
    
    try {
        vector<Entity*> entities;
        entities.push_back(new Character("Hero", 100, 20, 10));
        entities.push_back(new Monster("Goblin", 50, 15, 5));
        entities.push_back(new Boss("Evil Boss", 200, 30, 15));
        
        cout << "=== Saving game data ===\n";
        saveToFile(entities, "game_save.txt");
        
        for (auto entity : entities) {
            delete entity;
        }
        entities.clear();
        
        cout << "\n=== Loading game data ===\n";
        entities = loadFromFile("game_save.txt");
        
        cout << "\n=== Loaded characters ===\n";
        for (const auto& entity : entities) {
            entity->displayInfo();
        }
        
        cout << "\n=== Battle Phase ===\n";
        if (entities.size() >= 2) {
            entities[0]->attack(*entities[1]);
            if (Character* hero = dynamic_cast<Character*>(entities[0])) {
                cout << "\n=== Healing Phase ===\n";
                hero->heal(30);
            }
        }
        
        for (auto entity : entities) {
            delete entity;
        }
        
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
    
    return 0;
}
