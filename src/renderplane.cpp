
#include <cmath>

#include "renderplane.h"

// constructors
RenderPlane::RenderPlane() : RenderObject(), _normal{} {}

RenderPlane::~RenderPlane() {}

RenderPlane::RenderPlane(const RenderPlane &source)
{
    _origin = Coordinate3d(source._origin);
    _normal = Vector3d(source._normal);
    _color = Color3d(source._color);
    std::cout << "Plane copy constructor color=" << _color << std::endl;
}

RenderPlane& RenderPlane::operator=(const RenderPlane &source) {
    if (this == &source)
        return *this;

    _origin = Coordinate3d(source._origin);
    _normal = Vector3d(source._normal);
    _color = Color3d(source._color);
    std::cout << "Plane assignment operator color=" << _color << std::endl;
    return *this;
}

RenderPlane::RenderPlane(const RenderPlane &&source)
{
    _origin = source._origin;
    _normal = source._normal;
    _color = source._color;
    std::cout << "Plane move constructor color=" << _color << std::endl;
}

RenderPlane& RenderPlane::operator=(const RenderPlane &&source) {
    if (this == &source)
        return *this;

    _origin = source._origin;
    _normal = source._normal;
    _color = source._color;
    std::cout << "Plane move assignment operator color=" << _color << std::endl;
    return *this;
}

RenderPlane::RenderPlane(Coordinate3d coordinate, Color3d color, Vector3d normal) : RenderObject{coordinate, color}, _normal{normal} {}

double RenderPlane::hits_render_object(Scene &scene, const Ray3d &ray)
{ // override
    double distance = (_origin - ray.origin()).dot(_normal) / ray.direction().dot(_normal);

    return distance;
}

Color3d RenderPlane::get_color(Scene &scene, const Ray3d &ray, const double distance, int depth)
{
    //std::cout << "PlaneColor=" << _color << std::endl;
    // override
    return _color;
}