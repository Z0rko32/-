#include <iostream>
#include <string>

class Person {
private:
    std::string name;
    int age;
    std::string email;
    std::string address; // Новое поле

public:
    std::string getName() const {
        return name;
    }

    int getAge() const {
        return age;
    }

    std::string getEmail() const {
        return email;
    }

    std::string getAddress() const {
        return address;
    }

    void setName(const std::string& newName) {
        if (!newName.empty()) {
            name = newName;
        } else {
            std::cerr << "Ошибка: Имя не может быть пустым!\n";
        }
    }

    void setAge(int newAge) {
        if (newAge >= 0 && newAge <= 120) {
            age = newAge;
        } else {
            std::cerr << "Ошибка: Возраст должен быть в диапазоне от 0 до 120!\n";
        }
    }

    void setEmail(const std::string& newEmail) {
        if (newEmail.find('@') != std::string::npos) {
            email = newEmail;
        } else {
            std::cerr << "Ошибка: Email должен содержать символ '@'!\n";
        }
    }

    void setAddress(const std::string& newAddress) {
        if (!newAddress.empty()) {
            address = newAddress;
        } else {
            std::cerr << "Ошибка: Адрес не может быть пустым!\n";
        }
    }

    void displayInfo() const {
        std::cout << "Имя: " << name 
                  << ", Возраст: " << age 
                  << ", Email: " << email 
                  << ", Адрес: " << address << "\n";
    }
};

int main() {
    Person person;

    person.setName("Иван Иванов");
    person.setAge(30);
    person.setEmail("ivan@example.com");
    person.setAddress("ул. Ленина, д. 1");

    std::cout << "Информация о человеке:\n";
    person.displayInfo();

    std::cout << "\nПопытка установить некорректные данные:\n";
    person.setName("");           // Ошибка: имя не может быть пустым
    person.setAge(150);           // Ошибка: возраст вне диапазона
    person.setEmail("invalid");   // Ошибка: email без '@'
    person.setAddress("");        // Ошибка: адрес не может быть пустым

    std::cout << "\nИнформация после попыток изменений:\n";
    person.displayInfo();

    return 0;
}