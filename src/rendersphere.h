#ifndef RENDERSPHERE
#define RENDERSPHERE

#include "renderobject.h"

class RenderSphere : public RenderObject
{
public:
    // constructors
    RenderSphere();
    ~RenderSphere();
    RenderSphere(const RenderSphere &source);             // copy constructor
    RenderSphere &operator=(const RenderSphere &source);  // copy assignment operator
    RenderSphere(const RenderSphere &&source);            // move constructor
    RenderSphere &operator=(const RenderSphere &&source); // move assignment operator

    // create an object using origin coordinate and material
    RenderSphere(Coordinate3d coordinate, double radius, Color3d material);

    // returns the distance along the ray if this object has been hit by the ray
    double hits_render_object(Scene &scene, const Ray3d &ray) override;

    // returns the color of the ray hitting the object at dinstance
    // use depth to limit the number of mirror bounces
    Color3d get_color(Scene &scene, const Ray3d &ray, const double distance, int depth) override;

private:
    double _radius;
};

#endif