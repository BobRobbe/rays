
#include "coordinate3d.h"

Coordinate3d::Coordinate3d() : _x{0}, _y{0}, _z{0} {}
Coordinate3d::~Coordinate3d() {}

Coordinate3d::Coordinate3d(double dx, double dy, double dz) : _x{dx}, _y{dy}, _z{dz} {}

double Coordinate3d::x() const { return _x; }
double Coordinate3d::y() const { return _y; }
double Coordinate3d::z() const { return _z; }

Coordinate3d& Coordinate3d::operator+=( const Coordinate3d &other){
    _x += other.x();
    _y += other.y();
    _z += other.z();

    return *this;
}

Coordinate3d& Coordinate3d::operator*=(const double factor){
    _x *= factor;
    _y *= factor;
    _z *= factor;
    return *this;
}

