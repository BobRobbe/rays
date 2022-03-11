#ifndef RENDERPLANE
#define RENDERPLANE

#include "renderobject.h"

class RenderPlane : public RenderObject
{
public:
    // constructors
    RenderPlane();
    ~RenderPlane();
    RenderPlane(const RenderPlane &source);             // copy constructor
    RenderPlane &operator=(const RenderPlane &source);  // copy assignment operator
    RenderPlane(const RenderPlane &&source);            // move constructor
    RenderPlane &operator=(const RenderPlane &&source); // move assignment operator

    // create an object using origin coordinate and material
    RenderPlane(Coordinate3d coordinate, Vector3d normal, Color3d material);

    // returns the distance along the ray if this object has been hit by the ray
    double hits_render_object(Scene &scene, const Ray3d &ray) override;

    // returns the color of the ray hitting the object at dinstance
    // use depth to limit the number of mirror bounces
    Color3d get_color(Scene &scene, const Ray3d &ray, const double distance, int depth) override;

private:
    Vector3d _normal;
};

#endif