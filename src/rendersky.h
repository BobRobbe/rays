#ifndef RENDERSKY
#define RENDERSKY

#include "renderobject.h"

class RenderSky : public RenderObject
{
public:
    // constructors
    RenderSky();
    ~RenderSky();
    RenderSky(const RenderSky &source);               // copy constructor
    RenderSky& operator=(const RenderSky &source);    // copy assignment operator
    RenderSky(const RenderSky &&source);               // move constructor
    RenderSky& operator=(const RenderSky &&source);    // move assignment operator

    RenderSky(Coordinate3d coordinate);

    double hits_render_object(const Ray3d &ray) override;

    Color3d get_color(const Ray3d &ray, const double distance, int depth);
};

#endif