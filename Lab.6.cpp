#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>

template <typename T>
class Queue {
private:
    std::vector<T> data;

public:
    void push(const T& item) {
        data.push_back(item);
    }

    void pop() {
        if (data.empty()) {
            throw std::runtime_error("Попытка удаления из пустой очереди");
        }
        data.erase(data.begin());
    }

    void display() const {
        std::cout << "Очередь: ";
        for (const auto& item : data) {
            std::cout << item << " ";
        }
        std::cout << "\n";
    }
};

int main() {
    Queue<int> q;
    q.push(1);
    q.push(2);

    try {
        q.pop();
        q.pop();
        q.pop();  // Вызовет исключение
    } catch (const std::runtime_error& e) {
        std::cerr << "Ошибка: " << e.what() << "\n";
    }

    return 0;
}