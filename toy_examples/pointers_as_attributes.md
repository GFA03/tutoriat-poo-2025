## Overview

This C++ class, `Example`, demonstrates basic memory management with dynamic memory allocation for a `char*` attribute, and it includes operator overloading for assignment (`=`) and addition (`+`). The class performs memory-safe handling of strings by using proper constructors, a destructor, and overloaded operators.

### Features:
- Constructor that dynamically allocates memory for the string.
- Copy constructor to safely handle deep copying of the object.
- Destructor that ensures the memory is properly freed when the object goes out of scope.
- Overloaded assignment operator for safe object assignment.
- Overloaded `+` operator for concatenating two `Example` objects.

## Code Explanation

```cpp
#include <iostream>
#include <cstring>

class Example {
private:
    char* str;  // A dynamic character array (string)

public:
    // Constructor
    Example(const char* s = "") {
        str = new char[strlen(s) + 1];  // Allocates memory for the string
        strcpy(str, s);                 // Copies the string into the allocated memory
    }

    // Copy Constructor
    Example(const Example& other) {
        str = new char[strlen(other.str) + 1];  // Allocates memory for the new string
        strcpy(str, other.str);                 // Copies the string from the other object
    }

    // Destructor
    ~Example() {
        if(this->str != nullptr){
            delete[] str;  // Frees the dynamically allocated memory
            this->str = nullptr
        }
   }

    // Overloading the assignment operator
    Example& operator=(const Example& other) {
        if(this == &other) return *this;  // Self-assignment check
        if(this->str != nullptr){
            delete[] this->str;
            this->str = nullptr; // Set to nullptr to prevent dangling pointer
        }
        str = new char[strlen(other.str) + 1];  // Allocates new memory
        strcpy(str, other.str);  // Copies the string from the other object
        return *this;            // Returns the current object to support chaining
    }

    // Overloading the + operator for concatenation
    Example operator+(const Example& other) const {
        char* temp = new char[strlen(str) + strlen(other.str) + 1];  // Allocates enough space for both strings
        strcpy(temp, str);        // Copies the current string into the temp variable
        strcat(temp, other.str);  // Appends the other string to temp
        Example result(temp);     // Creates a new Example object with the concatenated string
        delete[] temp;            // Frees the temporary memory
        return result;            // Returns the new Example object
    }
};
```

## NULL vs nullptr

In C++, `NULL` and `nullptr` are both used to represent a null pointer, but they have distinct differences and purposes. Below is a breakdown of the key differences between them:

### 1. `NULL` (Null Pointer Constant)

- **Definition**: `NULL` is a macro that represents a null pointer constant. It is typically defined as `((void*)0)` in C, meaning it is an integer constant that evaluates to `0`. In C++, `NULL` is still defined as `0` or `((void*)0)`, but it is treated as a pointer constant.
- **Usage**: It can be assigned to any pointer type, and its value is `0`. It's commonly used to indicate that a pointer is not pointing to any valid object or memory.
- **Type Safety**: `NULL` can be problematic because it is essentially just an integer value (`0`), and thus, there could be ambiguity in situations where a `0` could be interpreted as an integer value rather than a null pointer. This ambiguity can lead to potential errors, especially in function overloads or template code.

### 2. `nullptr` (Null Pointer Literal)
- **Definition**: nullptr is a keyword introduced in C++11. It is a type-safe null pointer literal that can be assigned to any pointer type. It is not an integer constant, but a distinct type (std::nullptr_t), which ensures type safety when working with pointers.

- **Usage**: nullptr is used in the same way as NULL to represent null pointers, but it has the advantage of being safer and more explicit. Unlike NULL, which is an integer constant (0), nullptr cannot be mistakenly used as an integer or be interpreted ambiguously by the compiler.

- **Type Safety**: nullptr is specifically a pointer type, and the compiler will reject any assignment or comparison with a non-pointer type, providing better type safety.

### Example:
```cpp
int* ptr = NULL;  // This is valid, but NULL is treated as integer 0.
```

### Example to Illustrate Ambiguity with `NULL` vs `nullptr`
Consider a function overload with both integer and pointer types:

```cpp
void func(int) {
    std::cout << "Integer version" << std::endl;
}

void func(char*) {
    std::cout << "Pointer version" << std::endl;
}

int main() {
    func(0);        // Calls integer version (0 is treated as integer)
    func(NULL);     // Calls integer version, because NULL is 0 (integer)
    func(nullptr);  // Calls pointer version, because nullptr is a pointer
}
```

- `func(0)` calls the integer version because 0 is an integer.
- `func(NULL)`
- `func(nullptr)` calls the correct version (pointer version) because nullptr is specifically a pointer, not an integer.


### When to Use Which?
- **Use** `nullptr`: It is the modern, recommended way to represent null pointers in C++ (C++11 and later). It is type-safe, clear, and avoids ambiguity, making your code more reliable.

- **Avoid** `NULL`: In modern C++ code, prefer nullptr. It was commonly used in pre-C++11 code, but with the introduction of nullptr, its usage is now discouraged in favor of the newer, safer option.