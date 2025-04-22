# Understanding `dynamic_cast` and `static_cast` in C++

In C++, casting is a way to convert a variable from one type to another. Two of the most commonly used C++ cast operators are `dynamic_cast` and `static_cast`. Each serves a specific purpose and has unique characteristics.

---

## `static_cast`

`static_cast` is used for compile-time type conversions. It's commonly used for:

- Converting numeric data types (e.g., `int` to `float`)
- Casting up and down an inheritance hierarchy (with known relationships)
- Converting between pointers and references to related types

### Syntax
```cpp
Type result = static_cast<Type>(expression);
```

### Example
```cpp
class Base {
public:
    virtual void show() {}
};

class Derived : public Base {
public:
    void display() {}
};

int main() {
    Derived d;
    Base* basePtr = static_cast<Base*>(&d); // Upcasting explicitly
        // Just the same as Base* basePtr = &d

    Derived* derivedPtr = static_cast<Derived*>(basePtr); // Downcasting - potentially unsafe
    return 0;
}
```

### Key Points
- No runtime checks
- Faster than `dynamic_cast`
- Unsafe if downcasting without proper type checks
- Cannot cast from one sibling class to another (e.g., from one derived class to another unrelated derived class)

---

## `dynamic_cast`

`dynamic_cast` is used for safe downcasting at runtime. It works only with polymorphic types (i.e., classes with at least one virtual function).

### Syntax
```cpp
Type result = dynamic_cast<Type>(expression);
```

### Example
```cpp
#include <iostream>
#include <typeinfo>
using namespace std;

class Base {
public:
    virtual ~Base() {}
};

class Derived : public Base {
public:
    void specific() {}
};

class Sibling : public Base {
};

int main() {
    Base* basePtr = new Derived;

    // Valid downcast
    Derived* derivedPtr = dynamic_cast<Derived*>(basePtr);
    if (derivedPtr) {
        derivedPtr->specific(); // Safe to use
    } else {
        cout << "Cast to Derived* failed" << endl;
    }

    // Invalid cast between siblings
    Sibling* siblingPtr = dynamic_cast<Sibling*>(basePtr);
    if (!siblingPtr) {
        cout << "Cannot cast from Derived* to Sibling*" << endl;
    }

    try {
        // Example of reference casting, throws std::bad_cast on failure
        Sibling& siblingRef = dynamic_cast<Sibling&>(*basePtr);
    } catch (const std::bad_cast& e) {
        cout << "Exception caught: " << e.what() << endl;
    }

    delete basePtr;
    return 0;
}
```

### Key Points
- Performs a runtime type check
- Returns `nullptr` if the cast fails (for pointers)
- Throws `std::bad_cast` if casting by reference fails
- Requires at least one virtual function in the base class
- Cannot cast between sibling classes

---

## Summary
| Feature         | `static_cast`                 | `dynamic_cast`                |
|----------------|-------------------------------|-------------------------------|
| Type Checking  | Compile-time                  | Runtime                       |
| Speed          | Fast                          | Slower                        |
| Use Case       | Known and safe conversions    | Polymorphic downcasting       |
| Virtual Needed | No                            | Yes                           |
| Fails How?     | Undefined behavior            | Returns `nullptr` or throws   |
| Sibling Cast   | Not allowed                   | Not allowed                   |

Use `static_cast` when you are sure of the type conversion, and `dynamic_cast` when safety is a concern in a polymorphic class hierarchy.
