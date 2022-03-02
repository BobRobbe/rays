#ifndef RAY3D
#define RAY3D

#include "coordinate3d.h"

class Ray3d : public Coordinate3d
{
public:
    // constructors
    Ray3d();
    ~Ray3d();
    Ray3d(const Coordinate3d &origin, const Vector3d &direction);

    // getters
    Coordinate3d origin() const;
    Vector3d direction() const;

    Coordinate3d target() const;

protected:
    Vector3d _direction;
};

#endif