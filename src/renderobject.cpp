
#include "renderobject.h"

// constructors
RenderObject::RenderObject() : _origin() {}

RenderObject::~RenderObject() {}

RenderObject::RenderObject(const RenderObject &source)
{
    _origin = Coordinate3d(source._origin);
    _material = source._material;
}

RenderObject &RenderObject::operator=(const RenderObject &source)
{
    if (this == &source)
        return *this;

    _origin = Coordinate3d(source._origin);
    _material = source._material;
    return *this;
}

RenderObject::RenderObject(const RenderObject &&source)
{
    _origin = source._origin;
    _material = source._material;
}

RenderObject &RenderObject::operator=(const RenderObject &&source)
{
    if (this == &source)
        return *this;

    _origin = source._origin;
    _material = source._material;
    return *this;
}

RenderObject::RenderObject(Coordinate3d coordinate, Color3d material) : _origin{coordinate}, _material{material} {}

double RenderObject::hits_render_object(Scene &scene, const Ray3d &ray)
{
    return -1.0;
}

Color3d RenderObject::get_color(Scene &scene, const Ray3d &ray, const double distance, int depth)
{
    return Color3d(0, 0, 0);
}
