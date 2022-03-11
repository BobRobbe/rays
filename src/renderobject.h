#ifndef RENDEROBJECT
#define RENDEROBJECT

#include "ray3d.h"
#include "color3d.h"
#include "scene.h"

class Scene;

class RenderObject
{
public:
    // constructors
    RenderObject();
    ~RenderObject();
    RenderObject(const RenderObject &source);             // copy constructor
    RenderObject &operator=(const RenderObject &source);  // copy assignment operator
    RenderObject(const RenderObject &&source);            // move constructor
    RenderObject &operator=(const RenderObject &&source); // move assignment operator

    // create an object using origin coordinate and material
    RenderObject(Coordinate3d coordinate, Color3d material);

    // returns the distance along the ray if this object has been hit by the ray
    virtual double hits_render_object(Scene &scene, const Ray3d &ray);

    // returns the color of the ray hitting the object at dinstance
    // use depth to limit the number of mirror bounces
    virtual Color3d get_color(Scene &scene, const Ray3d &ray, const double distance, int depth);

    Coordinate3d get_origin();
    Color3d get_material();

protected:
    Coordinate3d _origin;
    Color3d _material;
};

#endif