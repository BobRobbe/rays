#ifndef RENDERSKY
#define RENDERSKY

#include "renderobject.h"

class RenderSky : public RenderObject
{
public:
    // constructors
    RenderSky();
    ~RenderSky();
    RenderSky(const RenderSky &source);             // copy constructor
    RenderSky &operator=(const RenderSky &source);  // copy assignment operator
    RenderSky(const RenderSky &&source);            // move constructor
    RenderSky &operator=(const RenderSky &&source); // move assignment operator

    // create an object using origin coordinate and material
    RenderSky(Coordinate3d coordinate, Color3d material);

    // returns the distance along the ray if this object has been hit by the ray
    double hits_render_object(Scene &scene, const Ray3d &ray) override;

    // returns the color of the ray hitting the object at dinstance
    // use depth to limit the number of mirror bounces
    Color3d get_color(Scene &scene, const Ray3d &ray, const double distance, int depth);
};

#endif