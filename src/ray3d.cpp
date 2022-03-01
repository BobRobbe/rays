
#include "ray3d.h"

// constructors
Ray3d::Ray3d() : _direction{} {}

Ray3d::~Ray3d() {}

Ray3d::Ray3d(const Coordinate3d &origin, const Vector3d &direction) : Coordinate3d{origin}, _direction{direction} {}


// getters

Coordinate3d Ray3d::origin() const {
    return Coordinate3d(x(), y(), z());
}

Vector3d Ray3d::direction() const {
    return _direction;
}