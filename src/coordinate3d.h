#ifndef COORDINATE3D
#define COORDINATE3D

#include <iostream>

// Coordinate3d is used to provide the possibility to define a 3D coordinate
class Coordinate3d
{
public:
    // constructors
    Coordinate3d();
    ~Coordinate3d();
    Coordinate3d(const Coordinate3d &source);             // copy constructor
    Coordinate3d &operator=(const Coordinate3d &source);  // copy assignment operator
    Coordinate3d(const Coordinate3d &&source);            // move constructor
    Coordinate3d &operator=(const Coordinate3d &&source); // move assignment operator

    Coordinate3d(double dx, double dy, double dz);

    // getters
    double x() const;
    double y() const;
    double z() const;

    // setters
    void x(double dx);
    void y(double dy);
    void z(double dz);

    // overloaded operators
    Coordinate3d &operator+=(const Coordinate3d &other);
    Coordinate3d operator+(const Coordinate3d &other);
    Coordinate3d operator-(const Coordinate3d &other);

    Coordinate3d &operator*=(const double factor);
    Coordinate3d operator*(const Coordinate3d &other);
    Coordinate3d operator*(const double factor);
    Coordinate3d operator/(const double factor);

    // calculations
    double length() const;
    Coordinate3d vector_unit();

    double dot(const Coordinate3d other) const;

protected:
    double _x, _y, _z;
};

// https://stackoverflow.com/questions/476272/how-to-properly-overload-the-operator-for-an-ostream
std::ostream &operator<<(std::ostream &my_out, const Coordinate3d &other);

// type alias to define a vector (which is technically the same as a coordinate)
using Vector3d = Coordinate3d;

#endif