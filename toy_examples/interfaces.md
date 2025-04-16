# Interfaces in C++

C++ doesn’t have a built-in `interface` keyword like Java or C#. Instead, **interfaces are implemented using abstract classes** — specifically, abstract classes that contain **only pure virtual functions**.

---

## 🧩 What is an Interface?

An **interface** defines a **behaviour**: a set of functions that must be implemented by any class that "implements" the interface.

In C++, it's represented as a class that:

- Has **only pure virtual functions**.
- Often has a **virtual destructor**.
- Is used via **pointers or references**.

---

## ✨ Interface Syntax in C++

```cpp
class IPrintable {
public:
    virtual void print() const = 0;
    virtual ~IPrintable() = default; // Important for proper cleanup
};
```
### Implementing an interface
```cpp
class Document : public IPrintable {
public:
    void print() const override {
        std::cout << "Printing a document." << std::endl;
    }
};

class Image : public IPrintable {
public:
    void print() const override {
        std::cout << "Printing an image." << std::endl;
    }
};
```
### Usage
```cpp 
void printAnything(const IPrintable& printable) {
    printable.print();
}

int main() {
    Document doc;
    Image img;

    printAnything(doc); // Output: Printing a document.
    printAnything(img); // Output: Printing an image.
}
```


## Multiple Interfaces
C++ allows `multiple inheritance`, so a class can implement multiple interfaces:
```cpp
class IShape {
public:
    virtual void draw() const = 0;
    virtual ~IShape() = default;
};

class ISerializable {
public:
    virtual void serialize() const = 0;
    virtual ~ISerializable() = default;
};

class Circle : public IShape, public ISerializable {
public:
    void draw() const override {
        std::cout << "Drawing a circle." << std::endl;
    }

    void serialize() const override {
        std::cout << "Serializing a circle." << std::endl;
    }
};

```