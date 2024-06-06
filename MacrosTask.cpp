#include <iostream>

#define PI 3.14159

#define MULTIPLY(a, b) \
[&]() { \
decltype(a) _a = a; \
decltype(b) _b = b; \
return (_a) * (_b); \
}()

#define DEBUG

#define STRING(x) #x
#define CONCAT(a, b) a##b

#define DECLARE_PROPERTY(Type, Name) \
private: \
Type CONCAT(m_, Name); \
public: \
Type CONCAT(Get, Name)() const { return CONCAT(m_, Name); } \
void CONCAT(Set, Name)(Type value) { CONCAT(m_, Name) = value; }

struct Entity
{
    DECLARE_PROPERTY(int, X);
    DECLARE_PROPERTY(int, Y);

    Entity(int x, int y) : m_X(x), m_Y(y) {}

    int result() const { return GetX() + GetY(); }
};

int main() 
{
    std::cout << MULTIPLY(10 + 2, 3) << std::endl;

#ifdef DEBUG
    std::cout << "Debugging is enabled!" << std::endl;
#else
    std::cout << "Debugging is disabled!" << std::endl;
#endif

    const char* str = STRING(Hello);
    std::cout << str << std::endl;

    Entity e(10, 5);
    std::cout << e.result() << std::endl;

    return 0;
}