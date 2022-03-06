#ifndef RENDEROBJECT
#define RENDEROBJECT

#include "coordinate3d.h"
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
    RenderObject(const RenderObject &source);               // copy constructor
    RenderObject& operator=(const RenderObject &source);    // copy assignment operator
    RenderObject(const RenderObject &&source);              // move constructor
    RenderObject& operator=(const RenderObject &&source);   // move assignment operator

    RenderObject(Coordinate3d coordinate, Color3d color);

    virtual double hits_render_object( Scene &scene, const Ray3d &ray);

    virtual Color3d get_color(Scene &scene, const Ray3d &ray, const double distance, int depth);

protected:
    Coordinate3d _origin;
    Color3d _color;
};

#endif