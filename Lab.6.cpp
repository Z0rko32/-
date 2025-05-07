#include <iostream>
#include <vector>
#include <deque>
#include <stdexcept>

template <typename T>
class Queue {
private:
    std::deque<T> data; 

public:
    void push(const T& item) {
        data.push_back(item);
        std::cout << "Added item: " << item << " to queue\n";
    }

    void pop() {
        if (empty()) {
            throw std::out_of_range("Queue is empty! Cannot perform pop()");
        }
        std::cout << "Removed item: " << data.front() << " from queue\n";
        data.pop_front();
    }

    T front() const {
        if (empty()) {
            throw std::out_of_range("Queue is empty! Cannot access front()");
        }
        return data.front();
    }

    bool empty() const {
        return data.empty();
    }

    size_t size() const {
        return data.size();
    }

    void display() const {
        std::cout << "\nQueue contents (" << size() << " items):\n";
        for (const auto& item : data) {
            std::cout << "- " << item << "\n";
        }
    }
};

int main() {
    std::cout << "=== Queue with integers ===\n";
    
    Queue<int> intQueue;
    
    intQueue.push(10);
    intQueue.push(20);
    intQueue.push(30);
    
    intQueue.display();
    
    try {
        std::cout << "\nProcessing queue:\n";
        std::cout << "First item: " << intQueue.front() << std::endl;
        intQueue.pop();
        std::cout << "Next item: " << intQueue.front() << std::endl;
        intQueue.pop();
        std::cout << "Last item: " << intQueue.front() << std::endl;
        intQueue.pop();
        
        std::cout << "\nAttempting operations on empty queue:\n";
        intQueue.pop(); 
    } catch (const std::out_of_range& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    std::cout << "\n=== Queue with strings ===\n";
    
    Queue<std::string> stringQueue;
    
    stringQueue.push("Hello");
    stringQueue.push("World");
    stringQueue.push("Template");
    
    stringQueue.display();
    
    try {
        std::cout << "\nProcessing queue:\n";
        std::cout << "First item: " << stringQueue.front() << std::endl;
        stringQueue.pop();
        std::cout << "Next item: " << stringQueue.front() << std::endl;
        stringQueue.pop();
        std::cout << "Last item: " << stringQueue.front() << std::endl;
        stringQueue.pop();
        
        if (stringQueue.empty()) {
            std::cout << "String queue is now empty!" << std::endl;
        }
        
        std::cout << "Trying to access front of empty queue:\n";
        std::cout << stringQueue.front() << std::endl;  
    } catch (const std::out_of_range& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
