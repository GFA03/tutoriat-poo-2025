# Practical Examples of OOP Concepts in C++

## Introduction to Practical Examples

Practical examples are essential for understanding Object-Oriented Programming (OOP) concepts. They help bridge the gap between theoretical knowledge and real-world application. This document provides an overview of various OOP concepts through practical examples, including inheritance, polymorphism, encapsulation, constructors, destructors, virtual functions, and operator overloading.

## Example 1: Bank Account Management

### Classes: BankAccount, SavingsAccount, CheckingAccount

This example demonstrates the use of inheritance, polymorphism, and encapsulation.

```cpp
#include <iostream>
#include <string>
using namespace std;

class BankAccount {
protected:
    string accountHolder;
    double balance;

public:
    BankAccount(string holder, double initialBalance)
        : accountHolder(holder), balance(initialBalance) {}

    virtual void deposit(double amount) {
        balance += amount;
    }

    virtual void withdraw(double amount) {
        if (amount <= balance) {
            balance -= amount;
        } else {
            cout << "Insufficient funds!" << endl;
        }
    }

    virtual void displayBalance() const {
        cout << "Account Holder: " << accountHolder << ", Balance: $" << balance << endl;
    }
};

class SavingsAccount : public BankAccount {
public:
    SavingsAccount(string holder, double initialBalance)
        : BankAccount(holder, initialBalance) {}

    void withdraw(double amount) override {
        if (amount <= balance - 100) {
            balance -= amount;
        } else {
            cout << "Insufficient funds! Minimum balance of $100 required." << endl;
        }
    }
};

class CheckingAccount : public BankAccount {
public:
    CheckingAccount(string holder, double initialBalance)
        : BankAccount(holder, initialBalance) {}

    void withdraw(double amount) override {
        if (amount <= balance - 500) {
            balance -= amount;
        } else {
            cout << "Insufficient funds! Minimum balance of $500 required." << endl;
        }
    }
};

int main() {
    BankAccount* account1 = new SavingsAccount("Alice", 500);
    BankAccount* account2 = new CheckingAccount("Bob", 1000);

    account1->deposit(200);
    account1->withdraw(150);
    account1->displayBalance();

    account2->deposit(300);
    account2->withdraw(600);
    account2->displayBalance();

    delete account1;
    delete account2;
    return 0;
}
```

## Example 2: Library Management System

### Classes: Book, Library, Member

This example shows the use of constructors, destructors, and dynamic memory allocation.

```cpp
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Book {
    string title;
    string author;

public:
    Book(string t, string a) : title(t), author(a) {}

    void display() const {
        cout << "Title: " << title << ", Author: " << author << endl;
    }
};

class Library {
    vector<Book*> books;

public:
    ~Library() {
        for (auto book : books) {
            delete book;
        }
    }

    void addBook(string title, string author) {
        books.push_back(new Book(title, author));
    }

    void displayBooks() const {
        for (const auto& book : books) {
            book->display();
        }
    }
};

class Member {
    string name;
    Library& library;

public:
    Member(string n, Library& lib) : name(n), library(lib) {}

    void borrowBook(string title) {
        cout << name << " is borrowing " << title << endl;
    }
};

int main() {
    Library library;
    library.addBook("1984", "George Orwell");
    library.addBook("To Kill a Mockingbird", "Harper Lee");

    Member member("Charlie", library);
    member.borrowBook("1984");

    library.displayBooks();
    return 0;
}
```

## Example 3: Shape Hierarchy

### Classes: Shape, Circle, Rectangle, Triangle

This example demonstrates the use of virtual functions and function overriding.

```cpp
#include <iostream>
using namespace std;

class Shape {
public:
    virtual void draw() const = 0; // Pure virtual function
    virtual ~Shape() {}
};

class Circle : public Shape {
public:
    void draw() const override {
        cout << "Drawing a circle" << endl;
    }
};

class Rectangle : public Shape {
public:
    void draw() const override {
        cout << "Drawing a rectangle" << endl;
    }
};

class Triangle : public Shape {
public:
    void draw() const override {
        cout << "Drawing a triangle" << endl;
    }
};

int main() {
    Shape* shapes[3];
    shapes[0] = new Circle();
    shapes[1] = new Rectangle();
    shapes[2] = new Triangle();

    for (int i = 0; i < 3; ++i) {
        shapes[i]->draw();
        delete shapes[i];
    }
    return 0;
}
```

## Example 4: Student Grade Management

### Classes: Student, Course, Grade

This example shows the use of overloaded operators and copy constructors.

```cpp
#include <iostream>
#include <string>
using namespace std;

class Grade {
    char letter;

public:
    Grade(char l) : letter(l) {}

    char getLetter() const {
        return letter;
    }

    friend ostream& operator<<(ostream& os, const Grade& grade) {
        os << "Grade: " << grade.letter;
        return os;
    }
};

class Student {
    string name;
    Grade* grades;
    int numGrades;

public:
    Student(string n, Grade* g, int num)
        : name(n), numGrades(num) {
        grades = new Grade[numGrades];
        for (int i = 0; i < numGrades; ++i) {
            grades[i] = g[i];
        }
    }

    // Copy constructor
    Student(const Student& other)
        : name(other.name), numGrades(other.numGrades) {
        grades = new Grade[numGrades];
        for (int i = 0; i < numGrades; ++i) {
            grades[i] = other.grades[i];
        }
    }

    ~Student() {
        delete[] grades;
    }

    void displayGrades() const {
        cout << name << "'s grades: ";
        for (int i = 0; i < numGrades; ++i) {
            cout << grades[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    Grade grades[] = {Grade('A'), Grade('B'), Grade('C')};
    Student student1("David", grades, 3);
    Student student2 = student1; // Copy constructor

    student1.displayGrades();
    student2.displayGrades();
    return 0;
}
```

## Best Practices

### Designing and Implementing OOP Solutions

- **Encapsulation**: Keep data members private and provide public getter and setter methods.
- **Inheritance**: Use inheritance to promote code reuse and establish a clear hierarchy.
- **Polymorphism**: Use virtual functions to achieve runtime polymorphism.
- **Resource Management**: Always release dynamically allocated memory to avoid leaks.
- **Avoid Deep Copy**: Use smart pointers or move semantics to manage resources efficiently.

### Common Pitfalls

- **Object Slicing**: Be cautious when assigning derived class objects to base class objects.
- **Memory Leaks**: Ensure all dynamically allocated memory is properly deallocated.
- **Incomplete Interface**: Always override all necessary virtual functions in derived classes.

These examples and best practices provide a solid foundation for understanding and applying OOP concepts in C++. By studying and practicing these examples, you can develop a strong grasp of OOP principles and their practical applications.