# C++ Operator Overloading

Operator overloading in C++ allows developers to redefine the way operators work for user-defined types (classes and structs). This enhances code readability and allows for intuitive syntax when working with custom data types.

## Syntax

To overload an operator, a special function is defined using the `operator` keyword. This function can be a member function or a non-member function (friend function).

```cpp
class ClassName {
public:
    ReturnType operator OpSymbol (ParameterList) {
        // Implementation
    }
};
```

## Example: Overloading the `+` Operator

```cpp
#include <iostream>

class Complex {
private:
    double real, imag;
public:
    Complex(double r = 0, double i = 0) : real(r), imag(i) {}
    
    // Overloading the + operator
    Complex operator+(const Complex& obj) {
        return Complex(real + obj.real, imag + obj.imag);
    }
    
    void display() {
        std::cout << real << " + " << imag << "i" << std::endl;
    }
};

int main() {
    Complex c1(3, 4), c2(1, 2);
    Complex c3 = c1 + c2;  // Using overloaded operator
    c3.display();
    return 0;
}
```

## Overloading Other Operators

- **Unary Operators:** (`++`, `--`, `-`, `!`)
- **Binary Operators:** (`+`, `-`, `*`, `/`, `%`, `==`, `!=`, `<`, `>`, `<<`, `>>`, etc.)

### Example: Overloading `++` (Postfix & Prefix)
```cpp
class Count {
private:
    int value;
public:
    Count(int v = 0) : value(v) {}
    
    // Prefix
    Count& operator++() {
        ++value;
        return *this;
    }
    
    // Postfix
    Count operator++(int) {
        Count temp = *this;
        ++value;
        return temp;
    }
};
```

## Rules for Operator Overloading
1. When overloading an operator as a member function, `this` always refers to the left-hand operand, and the right-hand operand is passed as a `function parameter`. This is why some operators (like `<<` and `>>`) are usually overloaded as non-member (or `friend`) functions—so they can work with standard types like `std::ostream` on the left-hand side.
2. Cannot overload `.` (member access), `::` (scope resolution), `sizeof`, `?:` (ternary operator).
3. Overloaded operators must have at least one user-defined type operand. (You can't overload for example operator+ for `int`, but u can for a class defined by you)
4. Cannot change the precedence or associativity of operators.
5. Some operators should be overloaded as non-member functions (e.g., `<<`, `>>` for stream operations).

## C++ Operator Precedence Table

| **Precedence** | **Operator(s)**                 | **Description**                                            | **Associativity**    |
|--------------|-----------------------------|------------------------------------------------|----------------|
| 1            | `a::b`                        | Scope resolution                               | Left-to-right (`→`) |
| 2            | `a++ a--`                     | Suffix/postfix increment and decrement         | Left-to-right (`→`) |
|              | `type(a) type{a}`             | Functional cast                                | |
|              | `a()`                         | Function call                                  | |
|              | `a[]`                         | Subscript                                     | |
|              | `a.b a->b`                    | Member access                                 | |
| 3            | `++a --a`                     | Prefix increment and decrement                | Right-to-left (`←`) |
|              | `+a -a`                       | Unary plus and minus                          | |
|              | `!a ~a`                       | Logical NOT and bitwise NOT                   | |
|              | `(type)a`                     | C-style cast                                  | |
|              | `*a`                          | Indirection (dereference)                     | |
|              | `&a`                          | Address-of                                    | |
|              | `sizeof`                      | Size-of                                       | |
|              | `co_await`                    | Await-expression (C++20)                      | |
|              | `new new[]`                   | Dynamic memory allocation                     | |
|              | `delete delete[]`             | Dynamic memory deallocation                   | |
| 4            | `a.*b a->*b`                  | Pointer-to-member                             | Left-to-right (`→`) |
| 5            | `a * b a / b a % b`           | Multiplication, division, and remainder       | Left-to-right (`→`) |
| 6            | `a + b a - b`                 | Addition and subtraction                      | Left-to-right (`→`) |
| 7            | `a << b a >> b`               | Bitwise left shift and right shift            | Left-to-right (`→`) |
| 8            | `a <=> b`                     | Three-way comparison operator (C++20)        | Left-to-right (`→`) |
| 9            | `a < b a <= b a > b a >= b`   | Relational operators                          | Left-to-right (`→`) |
| 10           | `a == b a != b`               | Equality operators                            | Left-to-right (`→`) |
| 11           | `a & b`                       | Bitwise AND                                   | Left-to-right (`→`) |
| 12           | `a ^ b`                       | Bitwise XOR                                   | Left-to-right (`→`) |
| 13           | `a | b`                       | Bitwise OR                                    | Left-to-right (`→`) |
| 14           | `a && b`                      | Logical AND                                   | Left-to-right (`→`) |
| 15           | `a || b`                      | Logical OR                                    | Left-to-right (`→`) |
| 16           | `a ? b : c`                   | Ternary conditional                           | Right-to-left (`←`) |
|              | `throw`                        | Throw operator                                | |
|              | `co_yield`                    | Yield-expression (C++20)                      | |
|              | `a = b`                       | Direct assignment                             | |
|              | `a += b a -= b`               | Compound assignment by sum and difference     | |
|              | `a *= b a /= b a %= b`       | Compound assignment by product, quotient, remainder | |
|              | `a <<= b a >>= b`             | Compound assignment by bitwise shift          | |
|              | `a &= b a ^= b a |= b`        | Compound assignment by bitwise operations     | |
| 17           | `a, b`                        | Comma    

## Overloading `<<` `>>` Operators

### Without `friend` function (using a member function)
```cpp
#include <iostream>

class Number {
private:
    int value;
public:
    Number(int v) : value(v) {}
    
    std::ostream& operator<< (std::ostream &out);
};

std::ostream& Number::operator<< (std::ostream &out){
        out << value;
        return out;
  }

int main() {
    Number num(42);
    num << std::cout;       // ???????
    return 0;
}
```

### With `friend` function
```cpp
#include <iostream>

class Number {
private:
    int value;
public:
    Number(int v) : value(v) {}
    
    friend std::ostream& operator<<(std::ostream& os, const Number& num);
};

std::ostream& operator<<(std::ostream& os, const Number& num) {
    os << num.value;
    return os;
}

int main() {
    Number num(42);
    std::cout << num << std::endl;
    return 0;
}
```

- Notice that in both methods, the `output stream` is given by `reference` and not `const`
- We must use `friend` because in the left-hand side of `cout << num`, `cout` is not out `this`. Otherwise we're forced to write it in reverse: `num << cout`

## Example: Overloading `++` (Postfix & Prefix)
```cpp
#include <iostream>

class Counter {
private:
    int value;
public:
    Counter(int v = 0) : value(v) {}
    
    // Prefix increment (++i)
    Counter& operator++() {
        ++value;
        return *this;
    }
    
    // Postfix increment (i++)
    Counter operator++(int) {   // Notice the formal parameter    
        Counter temp = *this;   // Save current state
        ++value;                // Increment
        return temp;            // Return old state
    }

};
```
- Notice the return type for one

## Conclusion
Operator overloading makes custom types behave more naturally and intuitively, enhancing code maintainability and readability. However, it should be used judiciously to avoid confusion and unintended behaviors.
