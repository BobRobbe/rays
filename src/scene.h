#ifndef SCENE
#define SCENE

#include <vector>
#include <memory>

#include <opencv2/core.hpp>
#include "ray3d.h"
#include "color3d.h"
#include "renderobject.h"

class RenderObject;

class Scene
{
public:
    Scene();
    ~Scene();

    // add a RenderObject, used for objects and lights
    void add_object(std::shared_ptr<RenderObject> obj);

    // method to be started as a thread
    // computes the part of the image given by start_y and end_y
    // no mutex required on the image (img) as all lauched threads operate on a different part of the image
    void compute_part(Coordinate3d camera_pos, int image_width, int image_height, int start_y, int end_y, cv::Mat3b img);

    // computes whether the given pixel has a direct visual line to a light source
    // return value gives the number of visible light sources
    int is_in_shadow(const Coordinate3d &ray);

    // computes the color of a specific ray cast into the scene
    // depth gives the number of mirror bounces already taken
    // if max_bounce is reached the color of the last hit object is returned
    Color3d ray_trace(const Ray3d &ray, int depth);

    // number of mirror bounces to be taken as max
    int max_bounce;

private:
    // internal method to collect all lights from the list of objects
    void collect_lights();
    // collection of objects (including lights)
    std::vector<std::shared_ptr<RenderObject>> _scene_objects;
    // collection of light only (created using collect_lights())
    std::vector<std::shared_ptr<RenderObject>> _lights;
};

#endif