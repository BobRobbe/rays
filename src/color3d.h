#ifndef COLOR3D
#define COLOR3D

#include <iostream>

class Color3d
{
public:
    // constructors
    Color3d();
    ~Color3d();
    Color3d(double dr, double dg, double db);

    // getters
    double r() const;
    double g() const;
    double b() const;

    // getters for integer range
    int r_integer() const;
    int g_integer() const;
    int b_integer() const;

    // setters
    void r(double dr);
    void g(double dg);
    void b(double db);

    // overloaded operators
    Color3d &operator+=(const Color3d &other);
    Color3d operator+(const Color3d &other);
    Color3d operator-(const Color3d &other);

    Color3d &operator*=(const double factor);
    Color3d operator*(const Color3d &other);
    Color3d operator*(const double factor);
    Color3d operator/(const double factor);

protected:
    double _r, _g, _b;
};

// https://stackoverflow.com/questions/476272/how-to-properly-overload-the-operator-for-an-ostream
std::ostream &operator<<(std::ostream &my_out, const Color3d &other);

#endif