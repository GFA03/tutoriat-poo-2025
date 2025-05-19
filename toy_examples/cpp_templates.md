# Templates in C++

Templates are a powerful feature in C++ that allow writing generic and reusable code. They enable functions and classes to operate with generic types, making it easier to write type-independent code.

---

## 🧹 Function Templates

A **function template** allows you to define a single function to work with different data types.

### 📌 Syntax

```cpp
template <typename T>
T add(T a, T b) {
    return a + b;
}
```

- `template <typename T>` defines a generic type `T`.
- The function `add` can now be used with `int`, `chat`, `string`, etc (basically, anything that had operator+).

### ✅ Example

```cpp
#include <iostream>
using namespace std;

template <typename T>
T add(T a, T b) {
    return a + b;
}

int main() {
    cout << add(3, 7) << endl;         // int
    cout << add(3.5, 2.1) << endl;     // double
    cout << add('g', 'e') << endl;     // char
    return 0;
}
```

### What will this print?
```cpp
#include <iostream>
using namespace std;

template <typename T, typename Y>
T add1(Y a, T b) {
    return a + b;
}

template <typename T, typename Y>
Y add2(Y a, T b) {
    return a + b;
}

int main() {
    cout << add1(3, 3)   << endl;
    cout << add1(3.5, 7) << endl;
    cout << add2(3.5, 7) << endl;     
    return 0;
}
```


If we also have a method with the same name, the compiler will use the 'specialised' one, otherwise the template

```cpp
#include <iostream>
using namespace std;

char add(char a, char b){
    return a + b - 'a';
}

template <typename T>
T add(T a, T b) {
    return a + b;
}

int main() {
    cout << add(3, 7) << endl;         // int
    cout << add('g', 'e') << endl;     // char
    return 0;
}
```

---

## 🏗️ Class Templates

A **class template** allows you to define a blueprint for a class with generic data types.

### 📌 Syntax

```cpp
template <typename T>
class Box {
private:
    T value;
public:
    void set(T val) { value = val; }
    T get() { return value; }
};
```

### ✅ Example

```cpp
#include <iostream>
using namespace std;

template <typename T>
class Box {
private:
    T value;
public:
    void set(T val) { value = val; }
    T get() { return value; }
};

int main() {
    Box<int> intBox;
    intBox.set(123);
    cout << intBox.get() << endl;

    Box<string> strBox;
    strBox.set("Hello, Templates!");
    cout << strBox.get() << endl;

    return 0;
}
```

---

## 💡 Notes

- You can use `typename` or `class` when declaring templates: `template <typename T>` is the same as `template <class T>`.
- Templates can have multiple parameters: `template <typename T, typename U>`.
- Template instantiation happens at compile time.

---

## 📚 Advanced Topics

- Template Specialization
- Non-type Template Parameters
- Variadic Templates
- Concepts (C++20)

> Templates are foundational to many parts of the C++ STL (Standard Template Library), including `vector`, `map`, and `algorithm`.
