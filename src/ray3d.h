#ifndef RAY3D
#define RAY3D

#include "coordinate3d.h"

// Ray3d is used to define a ray, which is a combination of a coordinate (the origin)
// and a vector (representing the direction of the ray)
class Ray3d : public Coordinate3d
{
public:
    // constructors
    Ray3d();
    ~Ray3d();
    Ray3d(const Ray3d &source);             // copy constructor
    Ray3d &operator=(const Ray3d &source);  // copy assignment operator
    Ray3d(const Ray3d &&source);            // move constructor
    Ray3d &operator=(const Ray3d &&source); // move assignment operator

    Ray3d(const Coordinate3d &origin, const Vector3d &direction);

    // getters
    Coordinate3d origin() const;
    Vector3d direction() const;

    // returns the coordinate where this ray points to (origin + direction)
    Coordinate3d target() const;

    // returns the coordinate where the ray points to when the distance scalar is applied
    // result = origin + ( direction * distance )
    Coordinate3d point_at(const double distance) const;

protected:
    Vector3d _direction;
};

#endif