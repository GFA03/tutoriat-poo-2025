Exception Handling Guide

## 📌 What is Exception Handling?

Exception handling in C++ is used to gracefully handle errors or unexpected behavior at `runtime`, using three main keywords:

- `try` — to wrap code that might throw an exception.
- `throw` — to signal that an exception has occurred.
- `catch` — to handle the exception.

### Basic Syntax

```cpp
try {
    // Code that might throw an exception
    throw std::runtime_error("Something went wrong!");
} catch (const std::exception& e) {
    std::cout << "Caught exception: " << e.what() << std::endl;
}
```

### Multiple Catches
```cpp
try {
    // some code
} catch (const std::invalid_argument& e) {
    std::cout << "Invalid argument: " << e.what() << std::endl;
} catch (int){
    std::cout <<" You can throw variable of some type" << std::endl;
} catch (std::string){
    std::cout <<" It gets caught by the frist catch that matches the type" << std::endl;
} catch (...){ // This one always placed last
    std::cout << "Catch anything" << std::endl;
}

```

### Nested Exceptions
Exceptions propagate until it's caught, no code in between will be executed.

```cpp
#include <iostream>

void f() {
    std::cout << "I'm in f() now" << std::endl;
    throw std::runtime_error("Inner error");
}

void g() {
    std::cout << "I'm in g() now" << std::endl;
    f();
    std::cout << "Will this print?" << std::endl;
}

int main(){
    try{
        g();
    }catch(std::runtime_error e){
        std::cout << "Caught it in main" << std::endl;
    }
}

```

---
### Custom Exceptions
```cpp
#include <iostream>

// Method 1
class MyCustomException : public std::exception {
public:
    const char* what() const noexcept override {
        return "My custom error occurred!";
    }
};

// Method 2
class MyOtherException : public std::exception{
public:
    virtual const char* what() const throw(){
        return "My other exception";
    }    
}ex; // make a global exception

// Usage
int main(){
    try {
        throw MyCustomException();
    } catch (const MyCustomException& e) {
        std::cout << e.what() << std::endl;
    }

    try {
        throw ex;
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    
}
```

### Break down
#### Method 1:  const char* what() const noexcept override
| **Component**   | **Description**                                                                                      |
|-----------------|------------------------------------------------------------------------------------------------------|
| `const char*`   | Return type: a pointer to a constant character string (C-style string). Typically an error message.  |
| `what()`        | Function name. This matches the virtual `what()` function in `std::exception`.                       |
| `const`         | Means this function does **not** modify the state of the object. Safe to call on `const` instances.  |
| `noexcept`      | Promises the function **won’t throw any exceptions**. Improves performance and reliability.          |
| `override`      | Tells the compiler this method **overrides** a virtual function from a base class.                   |

#### Method 2: virtual const char* what() const throw()

| **Component**       | **Description**                                                                                      |
|---------------------|------------------------------------------------------------------------------------------------------|
| `virtual`           | Declares this function as virtual — it can be overridden in derived classes.                        |
| `const char*`       | Return type: a pointer to a constant character string (C-style string), usually the error message.   |
| `what()`            | The function name with no parameters.                                                               |
| `const`             | Means the function does not modify the object’s state. Safe to call on const objects.               |
| `throw()`           | Dynamic exception specification (old-style). Means this function **does not throw any exceptions**. |
