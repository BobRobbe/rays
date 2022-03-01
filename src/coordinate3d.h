#ifndef COORDINATE3D
#define COORDINATE3D

class Coordinate3d
{
public:
    Coordinate3d();
    ~Coordinate3d();

    Coordinate3d(double dx, double dy, double dz);

    double x() const;
    double y() const;
    double z() const;

    Coordinate3d &operator+=(const Coordinate3d &other);

    Coordinate3d &operator*=(const double factor);

private:
    double _x, _y, _z;
};

#endif