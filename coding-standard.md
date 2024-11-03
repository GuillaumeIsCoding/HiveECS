# Coding Standard
## Naming Conventions

### Namespace
- snake_case
```c++
namespace example {}
namespace hive_example {}
```

### Classes and Structs
- PascalCase
```c++
class Example;
class HiveExample;
```

### Functions and Methods
- camelCase
```c++
void example() {}
void hiveExample() {}
```

### Attributes
- m\_snake\_case
```c++
class Example {
private:
    int m_example;
    int m_hive_example;
}
```

### Variables
- snake\_case
```c++
int example;
int hive_example;
```

### Constants
- ALL\_CAPS
```c++
const int EXAMPLE = 1;
const int HIVE_EXAMPLE = 0;
```
## Header Files

### Forward Declaration
- Use foward declarations when possible to reduce dependencies. This minimize the need for including full header files, which can reduce compilation time and decrease dependencies which make it easier to maintain

### Include Guards
- Always use include guard or `#pragma once` in header files to prevent multiple inclusion of the same file

### Header File Content
- Should only declare classes, structs and functions. Their implementation should be in their associated `.cpp`  file

## General Coding Practices

### `const` and `constexpr`
- Use `const`  and `constexpr` where they are appropriate. This improve code safety and optimization

### Smart Pointers
- Prefer smart pointers to automatically manage memory, reducing the rick of memory leaks and dangling pointers. You must be careful when using smart pointer that have a destructor on static variable since they might depend on something that is already shutdown

### Namespace 
- Avoid using `using namespace std;` in headers files

### Error 
- Avoid throwing error, instead manage them and return an error code as an enum or other value. It would also be useful to use the Logging system to log what went wrong
