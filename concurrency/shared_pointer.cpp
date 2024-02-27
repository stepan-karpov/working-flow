#include <iostream>
#include <memory>

class MyClass {
public:
    MyClass(int value) : data(value) {
        std::cout << "Constructor called. Data: " << data << std::endl;
    }
    
    ~MyClass() {
        std::cout << "Destructor called. Data: " << data << std::endl;
    }
    
    void display() {
        std::cout << "Data: " << data << std::endl;
    }

    int data;
};

int main() {
    // Creating a shared pointer to an instance of MyClass
    std::shared_ptr<MyClass> sharedPtr1(new MyClass(42));

    // Creating another shared pointer that points to the same object
    std::shared_ptr<MyClass> sharedPtr2 = sharedPtr1;

    // Creating a third shared pointer using make_shared
    auto sharedPtr3 = std::make_shared<MyClass>(99);

    // Using the shared pointers
    sharedPtr1->display();
    sharedPtr2->display();
    sharedPtr3->display();

    // Changing the value via one of the shared pointers
    sharedPtr2->data = 12;
    sharedPtr2->display();

    return 0;
}
