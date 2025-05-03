#include <iostream>
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
        if (!data.empty()) {
            data.erase(data.begin());
        } else {
            std::cout << "Очередь пуста!\n";
        }
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
    Queue<int> q1;
    q1.push(10);
    q1.push(20);
    q1.push(30);
    q1.pop();
    q1.display();  // 20 30

    Queue<std::string> q2;
    q2.push("A");
    q2.push("B");
    q2.display();  // A B

    return 0;
}