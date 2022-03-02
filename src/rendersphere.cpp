
#include "rendersphere.h"


// constructors
RenderSphere::RenderSphere() : RenderObject(), _radius{} {}

RenderSphere::~RenderSphere() {}

RenderSphere::RenderSphere(const RenderSphere &source) {
    _origin = Coordinate3d(source._origin);
    _radius = source._radius;
}

RenderSphere::RenderSphere(Coordinate3d coordinate, double radius) : RenderObject{coordinate}, _radius{radius} {}


bool RenderSphere::hits_render_object(const Ray3d &ray) {   // override
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
    return (root > 0);
}

