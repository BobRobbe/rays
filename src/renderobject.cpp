
#include "renderobject.h"

// constructors
RenderObject::RenderObject() : _origin() {}

RenderObject::~RenderObject() {}

RenderObject::RenderObject(const RenderObject &source)
{
    _origin = Coordinate3d(source._origin);
    _color = Color3d(source._color);
}

RenderObject &RenderObject::operator=(const RenderObject &source)
{
    if (this == &source)
        return *this;

    _origin = Coordinate3d(source._origin);
    _color = Color3d(source._color);
    return *this;
}

RenderObject::RenderObject(const RenderObject &&source)
{
    _origin = source._origin;
    _color = source._color;
}

RenderObject &RenderObject::operator=(const RenderObject &&source)
{
    if (this == &source)
        return *this;

    _origin = source._origin;
    _color = source._color;
    return *this;
}

RenderObject::RenderObject(Coordinate3d coordinate) : _origin{coordinate} {}

double RenderObject::hits_render_object(const Ray3d &ray)
{
    return -1.0;
}

Color3d RenderObject::get_color(const Ray3d &ray, const double distance)
{
    return _color;
}

void RenderObject::set_color(const Color3d color)
{
    _color = color;
    std::cout << "SetColor=" << _color << std::endl;
}
