struct Point
{
    constexpr Point(double x, double y) : x(x), y(y) {}

    double x = 0;
    double y = 0;
};

constexpr Point operator+(const Point& a, const Point& b)
{
    return Point(a.x + b.x, a.y + b.y);
}

constexpr Point operator-(const Point& a, const Point& b)
{
    return Point(a.x - b.x, a.y - b.y);
}

constexpr double operator*(const Point& a, const Point& b)
{
    return a.x * b.x + a.y * b.y;
}

int main()
{
    constexpr Point a(1, 2);
    constexpr Point b(3, 4);
    constexpr Point c = a + b;
    constexpr Point d = a - b;
    constexpr double e = a * b;

    return 0;
}