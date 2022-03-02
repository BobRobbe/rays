
#include "renderobject.h"

// constructors
RenderObject::RenderObject() : _origin() {}

RenderObject::~RenderObject() {}

RenderObject::RenderObject(const RenderObject &source)
{
    _origin = Coordinate3d(source._origin);
    _color = Color3d(source._color);
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
}
