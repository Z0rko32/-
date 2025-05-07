#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <memory>
#include <stdexcept>
#include <ctime>
#include <mutex>
#include <limits> 

template <typename T>
class Logger {
private:
    std::ofstream logFile;
public:
    Logger(const std::string& filename) {
        logFile.open(filename, std::ios::app);
        if (!logFile) {
            throw std::runtime_error("Не удалось открыть файл логов!");
        }
    }

    void log(const T& message) {
        logFile << message << std::endl;
    }

    ~Logger() {
        if (logFile.is_open()) {
            logFile.close();
        }
    }
};

class Character {
protected:
    std::string name;
    int health;
    int attack;
    int defense;
    int level;
    int experience;

public:
    Character(const std::string& n, int h, int a, int d, int l = 1, int exp = 0)
        : name(n), health(h), attack(a), defense(d), level(l), experience(exp) {}

    virtual ~Character() = default;

    virtual std::string getName() const {
        return name;
    }

    int getHealth() const { return health; }
    int getAttack() const { return attack; }
    int getDefense() const { return defense; }
    int getLevel() const { return level; }
    int getExperience() const { return experience; }

    virtual void attackEnemy(Character& enemy, Logger<std::string>& logger) {
        int damage = attack - enemy.defense;
        if (damage > 0) {
            enemy.health -= damage;
            std::string msg = name + " атакует " + enemy.getName() + "! Урон: " + std::to_string(damage);
            std::cout << msg << std::endl;
            logger.log(msg);
        } else {
            std::string msg = name + " атакует " + enemy.getName() + ", но это неэффективно!";
            std::cout << msg << std::endl;
            logger.log(msg);
        }
    }

    void heal(int amount, Logger<std::string>& logger) {
        health += amount;
        if (health > 100) health = 100;
        std::string msg = name + " лечится! HP восстановлено: " + std::to_string(amount);
        std::cout << msg << std::endl;
        logger.log(msg);
    }

    void gainExperience(int exp, Logger<std::string>& logger) {
        experience += exp;
        if (experience >= 100) {
            level++;
            experience -= 100;
            std::string msg = name + " повысил уровень до " + std::to_string(level) + "!";
            std::cout << msg << std::endl;
            logger.log(msg);
        }
    }

    bool isAlive() const {
        return health > 0;
    }

    virtual void displayInfo() const {
        std::cout << "Имя: " << name
                  << ", Здоровье: " << health
                  << ", Атака: " << attack
                  << ", Защита: " << defense
                  << ", Уровень: " << level
                  << ", Опыт: " << experience << std::endl;
    }
};

class Monster : public Character {
public:
    Monster(const std::string& n, int h, int a, int d)
        : Character(n, h, a, d) {}

    std::string getName() const override {
        return "Монстр " + name;
    }
};

class Goblin : public Monster {
public:
    Goblin() : Monster("Гоблин", 50, 10, 5) {}

    std::string getName() const override {
        return "Гоблин";
    }
};

class Dragon : public Monster {
public:
    Dragon() : Monster("Дракон", 150, 25, 15) {}

    std::string getName() const override {
        return "Дракон";
    }
};

class Skeleton : public Monster {
public:
    Skeleton() : Monster("Скелет", 30, 5, 2) {}

    std::string getName() const override {
        return "Скелет";
    }
};

class Inventory {
private:
    std::vector<std::string> items;
public:
    void addItem(const std::string& item) {
        items.push_back(item);
        std::cout << "Предмет '" << item << "' добавлен в инвентарь." << std::endl;
    }

    void displayInventory() const {
        std::cout << "Инвентарь:" << std::endl;
        for (size_t i = 0; i < items.size(); ++i) {
            std::cout << i + 1 << ". " << items[i] << std::endl;
        }
    }

    bool useHealingPotion(Character* character, Logger<std::string>& logger) {
        if (items.empty()) {
            std::cout << "Инвентарь пуст!" << std::endl;
            return false;
        }

        for (size_t i = 0; i < items.size(); ++i) {
            if (items[i] == "Зелье лечения") {
                character->heal(30, logger); 
                items.erase(items.begin() + i);  
                return true;
            }
        }

        std::cout << "Зелье лечения не найдено в инвентаре!" << std::endl;
        return false;
    }
};

class Game {
private:
    std::unique_ptr<Character> player;
    Inventory inventory;
    Logger<std::string> logger;
    std::mutex battleMutex;

public:
    Game() : logger("game_log.txt") {
        player = std::make_unique<Character>("Герой", 100, 20, 10);
    }

    void start() {
        std::cout << "Добро пожаловать в RPG-игру!" << std::endl;
        while (true) {
            std::cout << "\n1. Бой с монстром\n2. Инвентарь\n3. Сохранить\n4. Загрузить\n5. Выход\n6. Использовать зелье лечения\nВыберите действие: ";
            int choice;
            std::cin >> choice;

            if (std::cin.fail()) {
                std::cin.clear();  
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                std::cout << "Ошибка ввода! Введите число от 1 до 6." << std::endl;
                continue;
            }

            switch (choice) {
                case 1: fight(); break;
                case 2: inventory.displayInventory(); break;
                case 3: saveGame(); break;
                case 4: loadGame(); break;
                case 5: return;
                case 6: {
                    if (inventory.useHealingPotion(player.get(), logger)) {
                        std::cout << "Зелье использовано. Текущее здоровье: " << player->getHealth() << std::endl;
                    }
                    break;
                }
                default:
                    std::cout << "Неверный выбор! Попробуйте снова." << std::endl;
            }
        }
    }

    void fight() {
        std::srand(static_cast<unsigned int>(std::time(0)));
        int type = std::rand() % 3;
        std::unique_ptr<Monster> monster;
        if (type == 0) monster = std::make_unique<Goblin>();
        else if (type == 1) monster = std::make_unique<Dragon>();
        else monster = std::make_unique<Skeleton>();

        std::lock_guard<std::mutex> lock(battleMutex);
        std::cout << "Вы встретили " << monster->getName() << "! Начало боя..." << std::endl;

        while (player->isAlive() && monster->isAlive()) {
            player->attackEnemy(*monster, logger);
            if (monster->isAlive()) {
                monster->attackEnemy(*player, logger);
            }
        }

        if (player->isAlive()) {
            std::cout << "Вы победили " << monster->getName() << "!" << std::endl;
            player->gainExperience(50, logger);
            inventory.addItem("Зелье лечения");
        } else {
            std::cout << "Вы погибли..." << std::endl;
            exit(0);
        }
    }

    void saveGame() {
        std::ofstream file("save.txt");
        if (!file) {
            std::cerr << "Не удалось сохранить игру!" << std::endl;
            return;
        }

        file << player->getName() << " "
             << player->getHealth() << " "
             << player->getAttack() << " "
             << player->getDefense() << " "
             << player->getLevel() << " "
             << player->getExperience() << "\n";

        std::cout << "Игра сохранена!" << std::endl;
    }

    void loadGame() {
        std::ifstream file("save.txt");
        if (!file) {
            std::cerr << "Сохранение не найдено!" << std::endl;
            return;
        }

        std::string name;
        int hp, attack, defense, level, exp;
        file >> name >> hp >> attack >> defense >> level >> exp;
        player = std::make_unique<Character>(name, hp, attack, defense, level, exp);

        std::cout << "Игра загружена!" << std::endl;
        player->displayInfo();
    }
};

int main() {
    try {
        Game game;
        game.start();
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
    return 0;
}
