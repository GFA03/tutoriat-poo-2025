#  Abstract Classes & Pure Virtual Functions in C++

## 📌 What is an Abstract Class?

An **abstract class** is a class that **cannot be instantiated** on its own. It serves as a **blueprint** for derived classes.

A class becomes abstract when it contains **at least one pure virtual function**.

---

## 🌀 What is a Pure Virtual Function?

A **pure virtual function** is a virtual function that has **no implementation** in the base class and must be **overridden** in a derived class.

### 🔧 Syntax:

```cpp
virtual ReturnType functionName() = 0;
```

## Example
```cpp
#include <iostream>

// Abstract base class
class Shape {
public:
    // Pure virtual function
    virtual void draw() = 0;

    // You can still define regular functions
    void info() {
        std::cout << "This is a shape." << std::endl;
    }
};

// Derived class
class Circle : public Shape {
public:
    void draw() override {
        std::cout << "Drawing a circle." << std::endl;
    }
};

// Another derived class
class Square : public Shape {
public:
    void draw() override {
        std::cout << "Drawing a square." << std::endl;
    }
};

```