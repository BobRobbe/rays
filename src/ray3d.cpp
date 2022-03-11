
#include "ray3d.h"

// constructors
Ray3d::Ray3d() : _direction{} {}

Ray3d::~Ray3d() {}

Ray3d::Ray3d(const Ray3d &source)
{
    _x = source._x;
    _y = source._y;
    _z = source._z;
    _direction = Vector3d(source._direction);
}

Ray3d &Ray3d::operator=(const Ray3d &source)
{
    if (this == &source)
        return *this;

    _x = source._x;
    _y = source._y;
    _z = source._z;
    _direction = Vector3d(source._direction);
    return *this;
}

Ray3d::Ray3d(const Ray3d &&source)
{
    _x = source._x;
    _y = source._y;
    _z = source._z;
    _direction = std::move(source._direction);
}

Ray3d &Ray3d::operator=(const Ray3d &&source)
{
    if (this == &source)
        return *this;

    _x = source._x;
    _y = source._y;
    _z = source._z;
    _direction = std::move(source._direction);
    return *this;
}

Ray3d::Ray3d(const Coordinate3d &origin, const Vector3d &direction) : Coordinate3d{origin}, _direction{direction} {}

// getters

Coordinate3d Ray3d::origin() const
{
    return Coordinate3d(x(), y(), z());
}

Vector3d Ray3d::direction() const
{
    return _direction;
}

Coordinate3d Ray3d::target() const
{
    return Coordinate3d(x() + _direction.x(), y() + _direction.y(), z() + _direction.z());
}

Coordinate3d Ray3d::point_at(const double distance) const
{
    return (origin() + direction() * distance);
}
