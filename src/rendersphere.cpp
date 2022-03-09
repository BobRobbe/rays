
#include <cmath>

#include "rendersphere.h"

// constructors
RenderSphere::RenderSphere() : RenderObject(), _radius{} {}

RenderSphere::~RenderSphere() {}

RenderSphere::RenderSphere(const RenderSphere &source)
{
    _origin = Coordinate3d(source._origin);
    _radius = source._radius;
    _material = source._material;
}

RenderSphere &RenderSphere::operator=(const RenderSphere &source)
{
    if (this == &source)
        return *this;

    _origin = Coordinate3d(source._origin);
    _radius = source._radius;
    _material = source._material;
    return *this;
}

RenderSphere::RenderSphere(const RenderSphere &&source)
{
    _origin = std::move(source._origin);
    _radius = source._radius;
    _material = std::move(source._material);
}

RenderSphere &RenderSphere::operator=(const RenderSphere &&source)
{
    if (this == &source)
        return *this;

    _origin = std::move(source._origin);
    _radius = source._radius;
    _material = std::move(source._material);
    return *this;
}

RenderSphere::RenderSphere(Coordinate3d coordinate, double radius, Color3d material) : RenderObject{coordinate, material}, _radius{radius} {}

double RenderSphere::hits_render_object(Scene &scene, const Ray3d &ray)
{ // override
    Vector3d sphere_vector = ray.origin() - _origin;
    // implementing the sphere equation
    // https://gabrielgambetta.com/computer-graphics-from-scratch/02-basic-raytracing.html#the-sphere-equation
    double a = ray.direction().dot(ray.direction());
    double b = 2.0 * sphere_vector.dot(ray.direction());
    double c = sphere_vector.dot(sphere_vector) - _radius * _radius;
    // compute the value for the suare root
    double root = b * b - 4 * a * c;
    // no need to calculate the square root, just need to know whether
    // <= 0 : sphere is not in the rays path
    // > 0  : sphere got hit by the ray
    if (root < 0)
    {
        return -1.0;
    }
    else
    {
        return ((-b - sqrt(root)) / (2.0 * a));
    }
}

Color3d RenderSphere::get_color(Scene &scene, const Ray3d &ray, const double distance, int depth)
{ // override
    if (distance > 0.0)
    {
        Vector3d normal = (ray.point_at(distance) - _origin).vector_unit();

        if (_material.get_material_kind() == mirror)
        {

            if (depth < 5)
            {
                Vector3d reflection = ray.direction() - (normal * 2 * ray.direction().dot(normal));
                Ray3d reflectedRay(ray.point_at(distance), reflection.vector_unit());
                Color3d reflectedColor = scene.simple_ray_trace(reflectedRay, ++depth);
                return (_material * reflectedColor);
            }
            else
            {
                return _material;
            }
        }
        else if (_material.get_material_kind() == phong)
        {
            return _material;
        }
    }
    else
    {
        return _material;
    }
    // std::cout << "SphereColor=" << _color << std::endl;
    return _material;
}