#include <iostream>
#include <string>
#include <sstream>
#include <exception>
#include <typeinfo>

using namespace std;

class bad_from_string : public std::exception
{
public:
    bad_from_string(const std::string& what_arg) : what_(what_arg) {}
    bad_from_string(const char* what_arg) : what_(what_arg) {}

    virtual const char* what() const noexcept { return what_.c_str(); }

private:
    std::string what_;
};

template <class T>
T from_string(std::string const& s)
{
    T t;
    std::istringstream stream(s);
    stream >> std::noskipws >> t;
    if (stream.fail() || stream.peek() != EOF)
    {
        throw bad_from_string("failed conversion to type " + std::string(typeid(T).name()) + " - " + s);
    }
    return t;
}

int main()
{
    string s1("123");
    int a1 = from_string<int>(s1);  // a1 = 123
    std::cout << a1 << std::endl;

    double b1 = from_string<double>(s1);  // b1 = 123.0
    std::cout << b1 << std::endl;

    string c1 = from_string<string>(s1);  // c1 = "123"
    std::cout << c1 << std::endl;

    string s2("12.3");
    int a2 = from_string<int>(s2);        // exception
    double b2 = from_string<double>(s2);  // b2 = 12.3
    std::cout << b2 << std::endl;

    string c2 = from_string<string>(s2);  // c2 = "12.3"
    std::cout << c2 << std::endl;

    string s3("abc");
    int a3 = from_string<int>(s3);        // exception
    double b3 = from_string<double>(s3);  // exception
    string c3 = from_string<string>(s3);  // c3 = "abc"
    std::cout << c3 << std::endl;

    return 0;
}