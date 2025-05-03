#include <iostream>
#include <memory>
#include <string>

class Inventory {
private:
    std::unique_ptr<std::string[]> items;
    int capacity;
    int count;

public:
    Inventory(int size = 10) : capacity(size), count(0) {
        items = std::make_unique<std::string[]>(capacity);
    }

    void addItem(const std::string& item) {
        if (count < capacity) {
            items[count++] = item;
        } else {
            std::cout << "Инвентарь полон!\n";
        }
    }

    void displayInventory() const {
        std::cout << "Инвентарь:\n";
        for (int i = 0; i < count; ++i) {
            std::cout << "- " << items[i] << "\n";
        }
    }
};

int main() {
    Inventory inv(3);
    inv.addItem("Зелье здоровья");
    inv.addItem("Меч");
    inv.addItem("Щит");
    inv.addItem("Кольцо");  // Не поместится

    inv.displayInventory();
    return 0;
}