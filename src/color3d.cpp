
#include "color3d.h"

// constructors
Color3d::Color3d() : _r{0}, _g{0}, _b{0} {}
Color3d::~Color3d() {}

Color3d::Color3d(const Color3d &source)
{
    _r = source._r;
    _g = source._g;
    _b = source._b;
    _material = source._material;
}

Color3d &Color3d::operator=(const Color3d &source)
{
    if (this == &source)
        return *this;

    _r = source._r;
    _g = source._g;
    _b = source._b;
    _material = source._material;
    return *this;
}

Color3d::Color3d(const Color3d &&source)
{
    _r = source._r;
    _g = source._g;
    _b = source._b;
    _material = source._material;
}

Color3d &Color3d::operator=(const Color3d &&source)
{
    if (this == &source)
        return *this;

    _r = source._r;
    _g = source._g;
    _b = source._b;
    _material = source._material;
    return *this;
}

Color3d::Color3d(double grey) : _r{grey}, _g{grey}, _b{grey} {}

Color3d::Color3d(double dr, double dg, double db) : _r{dr}, _g{dg}, _b{db} {}

Color3d::Color3d(double dr, double dg, double db, MKind material) : _r{dr}, _g{dg}, _b{db}, _material{material} {}

// getters
double Color3d::r() const { return _r; }
double Color3d::g() const { return _g; }
double Color3d::b() const { return _b; }
MKind Color3d::get_material_kind() { return _material; }

// getters for integer range
const double conversion_factor = 255.0;
int Color3d::r_integer() const { return _r * conversion_factor; }
int Color3d::g_integer() const { return _g * conversion_factor; }
int Color3d::b_integer() const { return _b * conversion_factor; }

// setters
void Color3d::r(double dr) { _r = dr; }
void Color3d::g(double dg) { _g = dg; }
void Color3d::b(double db) { _b = db; }

// normalize
void Color3d::normalize() {
    if(_r < 0) { _r = 0;}
    if(_g < 0) { _g = 0;}
    if(_b < 0) { _b = 0;}

    if(_r > 1) { _r = 1;}
    if(_g > 1) { _g = 1;}
    if(_b > 1) { _b = 1;}
}

// overloaded operators
Color3d &Color3d::operator+=(const Color3d &other)
{
    _r += other.r();
    _g += other.g();
    _b += other.b();

    return *this;
}

Color3d Color3d::operator+(const Color3d &other)
{
    return Color3d(r() + other.r(), g() + other.g(), b() + other.b());
}

Color3d Color3d::operator-(const Color3d &other)
{
    Color3d result = Color3d(r() - other.r(), g() - other.g(), b() - other.b());
    result.normalize();
    return result;
}

Color3d &Color3d::operator*=(const double factor)
{
    _r *= factor;
    _g *= factor;
    _b *= factor;
    return *this;
}

Color3d Color3d::operator*(const Color3d &other)
{
    return Color3d(r() * other.r(), g() * other.g(), b() * other.b());
}

Color3d Color3d::operator*(const double factor)
{
    return Color3d(r() * factor, g() * factor, b() * factor);
}

Color3d Color3d::operator/(const double factor)
{
    return Color3d(r() / factor, g() / factor, b() / factor);
}

std::ostream &operator<<(std::ostream &my_out, const Color3d &other)
{
    return my_out << "(" << other.r() << "," << other.g() << "," << other.b() << ")";
}
