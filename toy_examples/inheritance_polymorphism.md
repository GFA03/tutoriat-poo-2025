# **Inheritance & Polymorphism**

## **Course Outline**

### **Module 1: Introduction to Inheritance**
- **Definition & Importance**: Code reusability, maintainability, and logical hierarchy.
- **Basic Syntax & Implementation**:

```cpp
#include <iostream>
using namespace std;

class Parent {
public:
    void display() {
        cout << "This is the Parent class" << endl;
    }
};

class Child : public Parent {
};

int main() {
    Child obj;
    obj.display(); // Inherits display() from Parent
    return 0;
}
```

### **Module 2: Types of Inheritance**

#### **Single Inheritance**
```cpp
class A {
public:
    void show() {
        cout << "Single Inheritance Example" << endl;
    }
};
class B : public A {};
```

#### **Multiple Inheritance**
```cpp
class A {
public:
    void methodA() { cout << "From Class A" << endl; }
};
class B {
public:
    void methodB() { cout << "From Class B" << endl; }
};
class C : public A, public B {}; // Inherits from both A and B
```

#### **Multilevel Inheritance**
```cpp
class A { public: void showA() { cout << "Class A"; } };
class B : public A { public: void showB() { cout << " Class B"; } };
class C : public B { public: void showC() { cout << " Class C"; } };
```

#### **Hierarchical Inheritance**
```cpp
class Parent {
public:
    void commonMethod() { cout << "Common Method"; }
};
class Child1 : public Parent {};
class Child2 : public Parent {};
```

### **Module 3: Virtual Functions & Runtime Polymorphism**

#### **Vehicle Management System Example**
```cpp
class Vehicle {
public:
    virtual void start() {
        cout << "Vehicle is starting..." << endl;
    }
};
class Car : public Vehicle {
public:
    void start() override {
        cout << "Car is starting..." << endl;
    }
};
int main() {
    Vehicle* v = new Car();
    v->start(); // Calls Car's start() due to runtime polymorphism
    delete v;
}
```

### **Module 4: Abstract Classes & Interfaces**

#### **Banking System Example**
```cpp
class BankAccount {
public:
    virtual void accountType() = 0; // Pure virtual function
};
class Savings : public BankAccount {
public:
    void accountType() override {
        cout << "Savings Account" << endl;
    }
};
class Checking : public BankAccount {
public:
    void accountType() override {
        cout << "Checking Account" << endl;
    }
};
```

### **Module 5: Method Overriding & Overloading**

#### **Shape Calculation System Example**
```cpp
class Shape {
public:
    virtual void area() {
        cout << "Calculating area..." << endl;
    }
};
class Circle : public Shape {
public:
    void area() override {
        cout << "Area of Circle: πr^2" << endl;
    }
};
```

### **Module 6: Real-World Applications**

#### **Employee Management System**
- Base Class: `Employee`
- Derived Classes: `Manager`, `Developer`, `Intern`
- Functionality: Salary calculation, role-specific tasks.

#### **Library Management System**
- Base Class: `Book`
- Derived Classes: `EBook`, `PrintedBook`
- Functionality: Borrowing, returning, tracking.

#### **University Course Registration System**
- Base Class: `Course`
- Derived Classes: `OnlineCourse`, `OfflineCourse`
- Functionality: Register students, generate schedules.

### **Conclusion: Best Practices & Common Pitfalls**
- Use `virtual` for polymorphic behavior.
- Avoid the diamond problem in multiple inheritance.
- Keep base class functions `protected` or `public` as needed.

### **Exercises**
1. Implement a `Person` class and derive `Student` and `Professor` classes.
2. Create a `MusicInstrument` base class with `Piano` and `Guitar` subclasses.
3. Design a `Vehicle` hierarchy with `Car`, `Bike`, and `Bus` classes.

