#ifndef RENDERSPHERE
#define RENDERSPHERE

#include "renderobject.h"

class RenderSphere : public RenderObject
{
public:
    // constructors
    RenderSphere();
    ~RenderSphere();
    RenderSphere(const RenderSphere &source);               // copy constructor
    RenderSphere& operator=(const RenderSphere &source);    // copy assignment operator
    RenderSphere(const RenderSphere &&source);               // move constructor
    RenderSphere& operator=(const RenderSphere &&source);    // move assignment operator

    RenderSphere(Coordinate3d coordinate, double radius);

    double hits_render_object(const Ray3d &ray) override;

    Color3d get_color(const Ray3d &ray, const double distance) override;

private:
    double _radius;
};

#endif