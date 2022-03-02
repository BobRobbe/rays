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

    RenderSphere(Coordinate3d coordinate, double radius);

    bool hits_render_object(const Ray3d &ray) override;


private:
    double _radius;
    Color3d _color;
};

#endif