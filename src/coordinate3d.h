#ifndef COORDINATE3D
#define COORDINATE3D

class Coordinate3d
{
public:
    // constructors
    Coordinate3d();
    ~Coordinate3d();
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

    Coordinate3d &operator*=(const double factor);
    Coordinate3d operator*(const Coordinate3d &other);
    Coordinate3d operator*(const double factor);

protected:
    double _x, _y, _z;
};

// type alias
using Vector3d = Coordinate3d;

#endif