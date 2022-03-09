
#include <cmath>

#include "renderplane.h"

// constructors
RenderPlane::RenderPlane() : RenderObject(), _normal{} {}

RenderPlane::~RenderPlane() {}

RenderPlane::RenderPlane(const RenderPlane &source)
{
    _origin = Coordinate3d(source._origin);
    _normal = Vector3d(source._normal);
    _material = source._material;
}

RenderPlane &RenderPlane::operator=(const RenderPlane &source)
{
    if (this == &source)
        return *this;

    _origin = Coordinate3d(source._origin);
    _normal = Vector3d(source._normal);
    _material = source._material;
    return *this;
}

RenderPlane::RenderPlane(const RenderPlane &&source)
{
    _origin = source._origin;
    _normal = source._normal;
    _material = source._material;
}

RenderPlane &RenderPlane::operator=(const RenderPlane &&source)
{
    if (this == &source)
        return *this;

    _origin = source._origin;
    _normal = source._normal;
    _material = source._material;
    return *this;
}

RenderPlane::RenderPlane(Coordinate3d coordinate, Vector3d normal, Color3d material) : RenderObject{coordinate, material}, _normal{normal} {}

double RenderPlane::hits_render_object(Scene &scene, const Ray3d &ray)
{ // override
    double distance = (_origin - ray.origin()).dot(_normal) / ray.direction().dot(_normal);

    return distance;
}

Color3d RenderPlane::get_color(Scene &scene, const Ray3d &ray, const double distance, int depth)
{
    // where does the ray hit the plane
    Coordinate3d hit_point = ray.point_at(distance);

    switch (_material.get_material_kind())
    {
    case phong:
    {
        return _material;
    }

    case checkered:
    {

        const int offset = 10000;
        const double factor = 0.2;

        int index_x = (int)((hit_point.x() + offset) * factor) % 2;
        int index_z = (int)((hit_point.z() + offset) * factor) % 2;

        if ((index_x != 0 && index_z != 0) || (index_x == 0 && index_z == 0))
        {
            return _material;
        }
        else
        {
            return Color3d(0, 0, 0);
        }
    }

    default:
        return _material;
    }
}