#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <fstream>
#include <algorithm>
#include <stdexcept>
#include <sstream>

class User {
private:
    std::string name;
    int id;
    int accessLevel;

public:
    User(const std::string& name, int id, int accessLevel)
        : name(name), id(id), accessLevel(accessLevel) {
        if (accessLevel < 0) throw std::invalid_argument("Уровень доступа не может быть отрицательным");
        if (name.empty()) throw std::invalid_argument("Имя не может быть пустым");
    }

    virtual void displayInfo() const = 0;
    virtual ~User() = default;

    const std::string& getName() const { return name; }
    int getId() const { return id; }
    int getAccessLevel() const { return accessLevel; }

    virtual std::string getGroup() const { return ""; }
    virtual std::string getDepartment() const { return ""; }
};

class Student : public User {
private:
    std::string group;

public:
    Student(const std::string& name, int id, int accessLevel, const std::string& group)
        : User(name, id, accessLevel), group(group) {}

    void displayInfo() const override {
        std::cout << "Студент: " << getName() << ", ID: " << getId()
                  << ", Группа: " << group << ", Уровень доступа: " << getAccessLevel() << "\n";
    }

    std::string getGroup() const override { return group; }
};

class Teacher : public User {
private:
    std::string department;

public:
    Teacher(const std::string& name, int id, int accessLevel, const std::string& department)
        : User(name, id, accessLevel), department(department) {}

    void displayInfo() const override {
        std::cout << "Преподаватель: " << getName() << ", ID: " << getId()
                  << ", Кафедра: " << department << ", Уровень доступа: " << getAccessLevel() << "\n";
    }

    std::string getDepartment() const override { return department; }
};

class Administrator : public User {
public:
    Administrator(const std::string& name, int id, int accessLevel)
        : User(name, id, accessLevel) {}

    void displayInfo() const override {
        std::cout << "Администратор: " << getName() << ", ID: " << getId()
                  << ", Уровень доступа: " << getAccessLevel() << "\n";
    }
};

class Resource {
private:
    std::string name;
    int requiredAccessLevel;

public:
    Resource(const std::string& name, int requiredAccessLevel)
        : name(name), requiredAccessLevel(requiredAccessLevel) {
        if (requiredAccessLevel < 0) throw std::invalid_argument("Требуемый уровень доступа не может быть отрицательным");
    }

    bool checkAccess(const User& user) const {
        return user.getAccessLevel() >= requiredAccessLevel;
    }

    const std::string& getName() const { return name; }
    int getRequiredAccessLevel() const { return requiredAccessLevel; }
};

template <typename UserType, typename ResourceType>
class AccessControlSystem {
private:
    std::vector<std::shared_ptr<UserType>> users;
    std::vector<std::shared_ptr<ResourceType>> resources;

public:
    void addUser(std::shared_ptr<UserType> user) {
        users.push_back(user);
    }

    void addResource(std::shared_ptr<ResourceType> resource) {
        resources.push_back(resource);
    }

    void saveToFile(const std::string& filename) const {
        std::ofstream file(filename);
        if (!file) throw std::runtime_error("Не удалось открыть файл для записи");

        file << "Users:\n";
        for (const auto& user : users) {
            file << user->getName() << "," << user->getId() << "," 
                 << user->getAccessLevel() << ",";

             if (dynamic_cast<const Student*>(user.get())) {
                file << "Student," << dynamic_cast<const Student*>(user.get())->getGroup() << "\n";
            } else if (dynamic_cast<const Teacher*>(user.get())) {
                file << "Teacher," << dynamic_cast<const Teacher*>(user.get())->getDepartment() << "\n";
            } else if (dynamic_cast<const Administrator*>(user.get())) {
                file << "Administrator,\n";
            }
        }

        file << "Resources:\n";
        for (const auto& resource : resources) {
            file << resource->getName() << "," << resource->getRequiredAccessLevel() << "\n";
        }
    }

    void loadFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file) throw std::runtime_error("Не удалось открыть файл для чтения");

        users.clear();
        resources.clear();

        std::string line;
        while (std::getline(file, line)) {
            if (line == "Users:") {
                while (std::getline(file, line) && line != "Resources:") {
                    std::istringstream ss(line);
                    std::string name, idStr, levelStr, type, extra;
                    std::getline(ss, name, ',');
                    std::getline(ss, idStr, ',');
                    std::getline(ss, levelStr, ',');
                    std::getline(ss, type, ',');
                    std::getline(ss, extra, ',');

                    int id = std::stoi(idStr);
                    int level = std::stoi(levelStr);

                    if (type == "Student") {
                        users.push_back(std::make_shared<Student>(name, id, level, extra));
                    } else if (type == "Teacher") {
                        users.push_back(std::make_shared<Teacher>(name, id, level, extra));
                    } else if (type == "Administrator") {
                        users.push_back(std::make_shared<Administrator>(name, id, level));
                    }
                }
            } else if (line == "Resources:") {
                while (std::getline(file, line)) {
                    std::istringstream ss(line);
                    std::string name, levelStr;
                    std::getline(ss, name, ',');
                    std::getline(ss, levelStr, ',');
                    int level = std::stoi(levelStr);
                    resources.push_back(std::make_shared<Resource>(name, level));
                }
            }
        }
    }

    void displayAllUsers() const {
        for (const auto& user : users) {
            user->displayInfo();
        }
    }

    void displayAllResources() const {
        for (const auto& resource : resources) {
            std::cout << "Ресурс: " << resource->getName() 
                      << ", Требуемый уровень доступа: " << resource->getRequiredAccessLevel() << "\n";
        }
    }

    void checkAccess(int userId, const std::string& resourceName) const {
        auto userIt = std::find_if(users.begin(), users.end(), 
            [userId](const std::shared_ptr<UserType>& user) { return user->getId() == userId; });
        
        auto resourceIt = std::find_if(resources.begin(), resources.end(), 
            [resourceName](const std::shared_ptr<ResourceType>& res) { return res->getName() == resourceName; });

        if (userIt == users.end()) {
            std::cout << "Пользователь с ID " << userId << " не найден.\n";
            return;
        }

        if (resourceIt == resources.end()) {
            std::cout << "Ресурс " << resourceName << " не найден.\n";
            return;
        }

        if ((*resourceIt)->checkAccess(**userIt)) {
            std::cout << "Пользователь " << (*userIt)->getName() << " имеет доступ к " << resourceName << ".\n";
        } else {
            std::cout << "Пользователь " << (*userIt)->getName() << " не имеет доступа к " << resourceName << ".\n";
        }
    }

    void sortUsersByAccessLevel() {
        std::sort(users.begin(), users.end(), 
            [](const std::shared_ptr<UserType>& a, const std::shared_ptr<UserType>& b) {
                return a->getAccessLevel() < b->getAccessLevel();
            });
    }

    std::shared_ptr<UserType> findUserById(int id) const {
        auto it = std::find_if(users.begin(), users.end(), 
            [id](const std::shared_ptr<UserType>& user) { return user->getId() == id; });
        return (it != users.end()) ? *it : nullptr;
    }

    std::vector<std::shared_ptr<UserType>> findUsersByName(const std::string& name) const {
        std::vector<std::shared_ptr<UserType>> result;
        std::copy_if(users.begin(), users.end(), std::back_inserter(result),
            [&name](const std::shared_ptr<UserType>& user) { return user->getName() == name; });
        return result;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    try {
        AccessControlSystem<User, Resource> accessSystem;

        accessSystem.addUser(std::make_shared<Student>("Иван Иванов", 101, 2, "Группа А"));
        accessSystem.addUser(std::make_shared<Teacher>("Петр Петров", 201, 5, "Кафедра математики"));
        accessSystem.addUser(std::make_shared<Administrator>("Сергей Сергеев", 301, 10));

        accessSystem.addResource(std::make_shared<Resource>("Библиотека", 3));
        accessSystem.addResource(std::make_shared<Resource>("Лаборатория", 5));

        accessSystem.saveToFile("university_data.txt");

        AccessControlSystem<User, Resource> newSystem;
        newSystem.loadFromFile("university_data.txt");

        std::cout << "Все пользователи:\n";
        newSystem.displayAllUsers();

        std::cout << "\nВсе ресурсы:\n";
        newSystem.displayAllResources();

        std::cout << "\nПроверка доступа:\n";
        newSystem.checkAccess(101, "Библиотека");
        newSystem.checkAccess(101, "Лаборатория");
        newSystem.checkAccess(201, "Лаборатория");

        newSystem.sortUsersByAccessLevel();
        std::cout << "\nПользователи после сортировки по уровню доступа:\n";
        newSystem.displayAllUsers();

        std::cout << "\nПоиск пользователя по ID 201:\n";
        auto user = newSystem.findUserById(201);
        if (user) user->displayInfo();

        std::cout << "\nПоиск пользователей по имени 'Иван Иванов':\n";
        auto users = newSystem.findUsersByName("Иван Иванов");
        for (const auto& u : users) u->displayInfo();

    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }

    return 0;
}
