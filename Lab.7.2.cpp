#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <random>

// Класс монстра
class Monster {
public:
    std::string name;
    int health;
    int attack;

    Monster(const std::string& name = "Монстр", int health = 50, int attack = 10)
        : name(name), health(health), attack(attack) {}

    void displayInfo() const {
        std::cout << name << " (Здоровье: " << health << ")\n";
    }
};

// Общие данные
std::vector<Monster> monsters;
std::mutex mtx; // Мьютекс для синхронизации
bool battleEnded = false;

// Поток для генерации монстров
void generateMonsters() {
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(3));
        std::lock_guard<std::mutex> lock(mtx); // Защищаем доступ
        monsters.emplace_back(Monster("Гоблин", 50, 15));
        std::cout << "Новый монстр создан!\n";
    }
}

// Поток для боя
void battleThread(Monster& monster, Monster& hero) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dmg(5, 20);

    while (hero.health > 0 && monster.health > 0) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::lock_guard<std::mutex> lock(mtx); // Защищаем общий ресурс

        // Герой атакует монстра
        int heroDmg = dmg(gen);
        monster.health -= heroDmg;
        std::cout << hero.name << " атакует " << monster.name << "! Урон: " << heroDmg << "\n";

        // Проверка окончания боя
        if (monster.health <= 0) {
            std::cout << monster.name << " побеждён!\n";
            break;
        }

        // Монстр атакует героя
        int monsterDmg = dmg(gen);
        hero.health -= monsterDmg;
        std::cout << monster.name << " атакует " << hero.name << "! Урон: " << monsterDmg << "\n";

        if (hero.health <= 0) {
            std::cout << hero.name << " погибает!\n";
            break;
        }
    }
    battleEnded = true;
}

int main() {
    // Запуск генератора монстров
    std::thread monsterGenerator(generateMonsters);
    monsterGenerator.detach(); // Отсоединяем поток

    // Создаём героя и первого монстра
    Monster hero("Герой", 100, 20);
    Monster monster("Гоблин", 50, 15);

    // Запуск потока боя
    std::thread battle(battleThread, std::ref(monster), std::ref(hero));
    battle.join(); // Ждём завершения боя

    std::cout << "Игра окончена.\n";
    return 0;
}