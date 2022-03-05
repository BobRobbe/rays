
#include <cmath>

#include "coordinate3d.h"

// constructors
Coordinate3d::Coordinate3d() : _x{0}, _y{0}, _z{0} {}
Coordinate3d::~Coordinate3d() {}

Coordinate3d::Coordinate3d(const Coordinate3d &source)
{
    _x = source._x;
    _y = source._y;
    _z = source._z;
}

Coordinate3d &Coordinate3d::operator=(const Coordinate3d &source)
{
    if (this == &source)
        return *this;

    _x = source._x;
    _y = source._y;
    _z = source._z;
    return *this;
}

Coordinate3d::Coordinate3d(const Coordinate3d &&source)
{
    _x = source._x;
    _y = source._y;
    _z = source._z;
}

Coordinate3d &Coordinate3d::operator=(const Coordinate3d &&source)
{
    if (this == &source)
        return *this;

    _x = source._x;
    _y = source._y;
    _z = source._z;
    return *this;
}

Coordinate3d::Coordinate3d(double dx, double dy, double dz) : _x{dx}, _y{dy}, _z{dz} {}

// getters
double Coordinate3d::x() const { return _x; }
double Coordinate3d::y() const { return _y; }
double Coordinate3d::z() const { return _z; }

// setters
void Coordinate3d::x(double dx) { _x = dx; }
void Coordinate3d::y(double dy) { _y = dy; }
void Coordinate3d::z(double dz) { _z = dz; }

// overloaded operators
Coordinate3d &Coordinate3d::operator+=(const Coordinate3d &other)
{
    _x += other.x();
    _y += other.y();
    _z += other.z();

    return *this;
}

Coordinate3d Coordinate3d::operator+(const Coordinate3d &other)
{
    return Coordinate3d(x() + other.x(), y() + other.y(), z() + other.z());
}

Coordinate3d Coordinate3d::operator-(const Coordinate3d &other)
{
    return Coordinate3d(x() - other.x(), y() - other.y(), z() - other.z());
}

Coordinate3d &Coordinate3d::operator*=(const double factor)
{
    _x *= factor;
    _y *= factor;
    _z *= factor;
    return *this;
}

Coordinate3d Coordinate3d::operator*(const Coordinate3d &other)
{
    return Coordinate3d(x() * other.x(), y() * other.y(), z() * other.z());
}

Coordinate3d Coordinate3d::operator*(const double factor)
{
    return Coordinate3d(x() * factor, y() * factor, z() * factor);
}

Coordinate3d Coordinate3d::operator/(const double factor)
{
    return Coordinate3d(x() / factor, y() / factor, z() / factor);
}

std::ostream &operator<<(std::ostream &my_out, const Coordinate3d &other)
{
    return my_out << "(" << other.x() << "," << other.y() << "," << other.z() << ")";
}

double Coordinate3d::length() const
{
    return std::sqrt(x() * x() + y() * y() + z() * z());
}

Coordinate3d Coordinate3d::vector_unit()
{
    double length = this->length();
    Coordinate3d result{x() / length, y() / length, z() / length};
    return result;
}

double Coordinate3d::dot(const Coordinate3d other) const
{
    return x() * other.x() + y() * other.y() + z() * other.z();
}
