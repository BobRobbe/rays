#ifndef RENDERPLANE
#define RENDERPLANE

#include "renderobject.h"

class RenderPlane : public RenderObject
{
public:
    // constructors
    RenderPlane();
    ~RenderPlane();
    RenderPlane(const RenderPlane &source);               // copy constructor
    RenderPlane& operator=(const RenderPlane &source);    // copy assignment operator
    RenderPlane(const RenderPlane &&source);               // move constructor
    RenderPlane& operator=(const RenderPlane &&source);    // move assignment operator

    RenderPlane(Coordinate3d coordinate, Vector3d normal);

    double hits_render_object(const Ray3d &ray) override;

    Color3d get_color(const Ray3d &ray, const double distance) override;

private:
    Vector3d _normal;
};

#endif