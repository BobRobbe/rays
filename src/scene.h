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

    void add_object(std::shared_ptr<RenderObject> obj);

    void compute_part(Coordinate3d camera_pos, int image_width, int image_height, int start_y, int end_y, cv::Mat3b img);

    int is_in_shadow(const Coordinate3d &ray);

    Color3d ray_trace(const Ray3d &ray, int depth);

    int max_bounce;

private:
    void collect_lights();
    std::vector<std::shared_ptr<RenderObject>> _scene_objects;
    std::vector<std::shared_ptr<RenderObject>> _lights;
};

#endif