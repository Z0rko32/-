#include <iostream>
#include <vector>
#include <stdexcept>

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
            throw std::out_of_range("Queue is empty! Cannot pop.");
        }
        elements.erase(elements.begin());
    }
};

int main() {
    Queue<int> queue;

    try {
        queue.pop(); // Вызовет исключение
    } catch (const std::out_of_range& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        // Вывод: Error: Queue is empty! Cannot pop.
    }

    return 0;
}