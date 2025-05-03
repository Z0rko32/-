#include <iostream>
#include <vector>
#include <string>

template <typename T>
class Queue {
private:
    std::vector<T> elements;

public:
    void push(const T& item) {
        elements.push_back(item);
    }

    void pop() {
        if (elements.empty()) {
            throw std::out_of_range("Queue is empty!");
        }
        elements.erase(elements.begin());
    }

    void display() const {
        for (const auto& item : elements) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    // Очередь для строк
    Queue<std::string> stringQueue;
    stringQueue.push("Apple");
    stringQueue.push("Banana");
    stringQueue.display(); // Вывод: Apple Banana 

    // Очередь для чисел
    Queue<int> intQueue;
    intQueue.push(10);
    intQueue.push(20);
    intQueue.display(); // Вывод: 10 20 

    return 0;
}