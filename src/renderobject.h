#ifndef RENDEROBJECT
#define RENDEROBJECT

#include "coordinate3d.h"
#include "ray3d.h"
#include "color3d.h"

class RenderObject
{
public:
    // constructors
    RenderObject();
    ~RenderObject();
    RenderObject(const RenderObject &source);               // copy constructor

    RenderObject(Coordinate3d coordinate);

    virtual bool hits_render_object( const Ray3d &ray);

    virtual Color3d get_color(const Ray3d &ray);
    void set_color(const Color3d color);

protected:
    Coordinate3d _origin;
    Color3d _color;
};

#endif