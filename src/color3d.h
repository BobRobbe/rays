#ifndef COLOR3D
#define COLOR3D

#include <iostream>

class Color3d;

// defines material kind
enum MKind
{
    phong,
    mirror,
    glas,
    checkered,
    sky,
    light
};

class Color3d
{
public:
    // constructors
    Color3d();
    ~Color3d();
    Color3d(const Color3d &source);             // copy constructor
    Color3d &operator=(const Color3d &source);  // copy assignment operator
    Color3d(const Color3d &&source);            // move constructor
    Color3d &operator=(const Color3d &&source); // move assignment operator

    Color3d(double grey);
    Color3d(double dr, double dg, double db);
    Color3d(double dr, double dg, double db, MKind material);

    // getters
    double r() const;
    double g() const;
    double b() const;
    MKind get_material_kind();

    // getters for integer range
    int r_integer() const;
    int g_integer() const;
    int b_integer() const;

    // setters
    void r(double dr);
    void g(double dg);
    void b(double db);

    // normalize to make sure the values are between 0.0 and 1.0
    void normalize();

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
    MKind _material;
};

// https://stackoverflow.com/questions/476272/how-to-properly-overload-the-operator-for-an-ostream
std::ostream &operator<<(std::ostream &my_out, const Color3d &other);

#endif