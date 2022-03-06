
#include <cmath>
#include "rendersky.h"

// constructors
RenderSky::RenderSky() : RenderObject() {}

RenderSky::~RenderSky() {}

RenderSky::RenderSky(const RenderSky &source)
{
    _origin = Coordinate3d(source._origin);
    _color = Color3d(source._color);
}

RenderSky &RenderSky::operator=(const RenderSky &source)
{
    if (this == &source)
        return *this;

    _origin = Coordinate3d(source._origin);
    _color = Color3d(source._color);
    return *this;
}

RenderSky::RenderSky(const RenderSky &&source)
{
    _origin = source._origin;
    _color = source._color;
}

RenderSky &RenderSky::operator=(const RenderSky &&source)
{
    if (this == &source)
        return *this;

    _origin = source._origin;
    _color = source._color;
    return *this;
}

RenderSky::RenderSky(Coordinate3d coordinate, Color3d color) : RenderObject{coordinate, color} {}

double RenderSky::hits_render_object(Scene &scene, const Ray3d &ray)
{ // override
    return INFINITY;
}

Color3d RenderSky::get_color(Scene &scene, const Ray3d &ray, const double distance, int depth)
{ // override
    // no object has been hit, paint background sky gradient
    // get the ray vector normalized to length 1
    Vector3d direction = ray.direction().vector_unit();
    // check the height (y) amount to fetch the sky color
    double height = 0.3 * (direction.y() + 1.0);
    // calculate a color gradient for the sky
    return (_color * (1.0 - height) + Color3d(0.3, 0.6, 1.0) * height);
}