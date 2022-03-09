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

    RenderPlane(Coordinate3d coordinate, Vector3d normal, Color3d material);

    double hits_render_object(Scene &scene, const Ray3d &ray) override;

    Color3d get_color(Scene &scene, const Ray3d &ray, const double distance, int depth) override;

private:
    Vector3d _normal;
};

#endif