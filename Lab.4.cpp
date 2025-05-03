#include <iostream>
#include <memory>
#include <vector>
#include <string>

class Inventory {
private:
    std::vector<std::unique_ptr<std::string>> items;

public:
    void addItem(const std::string& item) {
        items.push_back(std::make_unique<std::string>(item));
    }

    void displayInventory() const {
        std::cout << "Inventory items:" << std::endl;
        for (const auto& item : items) {
            std::cout << *item << std::endl;
        }
    }
};

int main() {
    Inventory inv;
    inv.addItem("Sword");
    inv.addItem("Health Potion");
    inv.displayInventory(); 
    // Вывод:
    // Inventory items:
    // Sword
    // Health Potion
    return 0;
}