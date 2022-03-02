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

    RenderSky(Coordinate3d coordinate);

    bool hits_render_object(const Ray3d &ray) override;

    Color3d get_color(const Ray3d &ray);
};

#endif