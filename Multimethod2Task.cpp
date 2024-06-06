#include <functional>
#include <typeinfo>
#include <typeindex>
#include <map>

// Base - базовый класс иерархии
// Result - тип возвращаемого значения мультиметода
// Commutative - флаг, который показывает, что
// мультиметод коммутативный (т.е. f(x,y) = f(y,x)).
template <class Base, class Result, bool Commutative>
struct Multimethod2
{
    using Key = std::pair<std::type_index, std::type_index>;
    using F = std::function<Result(Base*, Base*)>;

    std::map<Key, F> implementations;

    // устанавливает реализацию мультиметода
    // для типов t1 и t2 заданных через typeid
    // f - это функция или функциональный объект
    // принимающий два указателя на Base
    // и возвращающий значение типа Result
    void addImpl(const std::type_info& t1, const std::type_info& t2, F f)
    {
        implementations[Key(std::type_index(t1), std::type_index(t2))] = f;
        if (Commutative)
        {
            implementations[Key(std::type_index(t2), std::type_index(t1))] = [f](Base* a, Base* b) { return f(b, a); };
        }
    }

    // проверяет, есть ли реализация мультиметода
    // для типов объектов a и b
    bool hasImpl(Base* a, Base* b) const { return implementations.find(Key(std::type_index(typeid(*a)), std::type_index(typeid(*b)))) != implementations.end(); }

    // Применяет мультиметод к объектам
    // по указателям a и b
    Result call(Base* a, Base* b) const
    {
        auto it = implementations.find(Key(std::type_index(typeid(*a)), std::type_index(typeid(*b)));
        if (it != implementations.end())
        {
            return it->second(a, b);
        }
        return Result();
    }
};