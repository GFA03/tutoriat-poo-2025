# Dynamic Memory Allocation in C++

## Introduction to Dynamic Allocation

Dynamic memory allocation in C++ allows the programmer to request memory during runtime, as opposed to compile-time. This is essential for handling variable-sized data structures and managing resources efficiently.

### Stack vs. Heap Memory
- **Stack Memory**: Automatically managed by the compiler, limited in size, and used for local variables and function calls.
- **Heap Memory**: Manually managed by the programmer, larger in size, and used for dynamic allocation.

## Using `new` and `delete`

### Allocating and Deallocating Memory
```cpp
#include <iostream>

int main() {
    int* ptr = new int(10); // Allocate memory for an integer
    std::cout << "Value: " << *ptr << std::endl;
    delete ptr; // Deallocate memory

    return 0;
}
```

### Importance of Proper Management
Failure to deallocate memory can lead to memory leaks, which can exhaust system resources over time.

## Arrays and Dynamic Allocation

### Allocating Arrays
```cpp
#include <iostream>

int main() {
    int* arr = new int[5];
    for (int i = 0; i < 5; ++i) {
        arr[i] = i * 2;
    }
    for (int i = 0; i < 5; ++i) {
        std::cout << arr[i] << " ";
    }
    delete[] arr; // Deallocate array

    return 0;
}
```

## Smart Pointers

### Introduction to Smart Pointers
Smart pointers manage dynamic memory automatically and help prevent memory leaks.

### `unique_ptr`
```cpp
#include <iostream>
#include <memory>

int main() {
    std::unique_ptr<int> ptr = std::make_unique<int>(20);
    std::cout << "Value: " << *ptr << std::endl;

    return 0;
}
```

### `shared_ptr`
```cpp
#include <iostream>
#include <memory>

int main() {
    std::shared_ptr<int> ptr1 = std::make_shared<int>(30);
    std::shared_ptr<int> ptr2 = ptr1;
    std::cout << "Value: " << *ptr1 << std::endl;
    std::cout << "Reference Count: " << ptr1.use_count() << std::endl;

    return 0;
}
```

### `weak_ptr`
```cpp
#include <iostream>
#include <memory>

int main() {
    std::shared_ptr<int> sharedPtr = std::make_shared<int>(40);
    std::weak_ptr<int> weakPtr = sharedPtr;

    if (auto spt = weakPtr.lock()) { // Check if the object is still valid
        std::cout << "Value: " << *spt << std::endl;
    }

    return 0;
}
```

## Best Practices

- Always `delete` dynamically allocated memory when no longer needed.
- Use smart pointers (`unique_ptr`, `shared_ptr`, `weak_ptr`) for safer memory management.
- Avoid accessing dangling pointers.
- Properly handle exceptions to prevent memory leaks.

## Practical Examples

### Dynamic Matrix Allocation
```cpp
#include <iostream>

int main() {
    int rows = 3, cols = 3;
    int** matrix = new int*[rows];
    for (int i = 0; i < rows; ++i) {
        matrix[i] = new int[cols];
    }

    // Initialize matrix
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matrix[i][j] = i * j;
        }
    }

    // Print matrix
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }

    // Deallocate memory
    for (int i = 0; i < rows; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;

    return 0;
}
```

## Conclusion

Dynamic memory allocation is a powerful feature in C++ that allows flexible memory management. By understanding the use of `new`, `delete`, and smart pointers, programmers can effectively manage resources and avoid common pitfalls such as memory leaks.

