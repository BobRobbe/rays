
#include <cmath>
#include "rendersky.h"


// constructors
RenderSky::RenderSky() : RenderObject() {}

RenderSky::~RenderSky() {}

RenderSky::RenderSky(const RenderSky &source) {
    _origin = Coordinate3d(source._origin);
}

RenderSky::RenderSky(Coordinate3d coordinate) : RenderObject{coordinate} {}


double RenderSky::hits_render_object(const Ray3d &ray) {   // override
    return INFINITY;
}

Color3d RenderSky::get_color(const Ray3d &ray, const double distance) {    // override
    // no object has been hit, paint background sky gradient
    // get the ray vector normalized to length 1
    Vector3d direction = ray.direction().vector_unit();
    // check the height (y) amount to fetch the sky color
    double height = 0.3 * (direction.y() + 1.0);
    // calculate a color gradient for the sky
    return (_color * (1.0 - height) + Color3d(0.3, 0.6, 1.0) * height);
}