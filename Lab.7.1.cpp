#include <iostream>
#include <fstream>
#include <vector>
#include <string>

// Базовый класс для сущностей (персонажей)
class Entity {
public:
    std::string name;
    int health;

    Entity(const std::string& name = "", int health = 0) : name(name), health(health) {}

    // Метод для сохранения данных в поток
    void save(std::ofstream& file) const {
        file << name << " " << health << "\n";
    }

    // Метод для загрузки данных из потока
    void load(std::ifstream& file) {
        file >> name >> health;
    }
};

// Менеджер персонажей
class GameManager {
public:
    std::vector<Entity> entities;

    void addEntity(const Entity& entity) {
        entities.push_back(entity);
    }

    void displayAll() const {
        for (const auto& entity : entities) {
            std::cout << "Имя: " << entity.name 
                      << ", Здоровье: " << entity.health << "\n";
        }
    }
};

// Сохранение в файл
void saveToFile(const GameManager& manager, const std::string& filename) {
    std::ofstream file(filename);
    if (!file) {
        throw std::runtime_error("Не удалось открыть файл для записи.");
    }
    for (const auto& entity : manager.entities) {
        entity.save(file); // Записываем каждый объект
    }
}

// Загрузка из файла
void loadFromFile(GameManager& manager, const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        throw std::runtime_error("Не удалось открыть файл для чтения.");
    }
    manager.entities.clear(); // Очищаем текущие данные
    Entity entity;
    while (file >> entity.name >> entity.health) {
        manager.entities.push_back(entity); // Считываем объекты
    }
}

int main() {
    try {
        GameManager manager;
        manager.addEntity(Entity("Герой", 100));
        manager.addEntity(Entity("Злодей", 80));

        // Сохраняем в файл
        saveToFile(manager, "save.txt");
        std::cout << "Сохранение выполнено!\n";

        // Загружаем из файла
        GameManager loadedManager;
        loadFromFile(loadedManager, "save.txt");
        std::cout << "Загруженные персонажи:\n";
        loadedManager.displayAll();
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << "\n";
    }
    return 0;
}