#ifndef SCENE
#define SCENE

#include <vector>
#include <memory>

#include "renderobject.h"

class RenderObject;

class Scene
{
public:
    Scene();
    ~Scene();

    void add_object(std::shared_ptr<RenderObject> obj);

    Color3d simple_ray_trace(const Ray3d &ray, int depth);

private:
    std::vector<std::shared_ptr<RenderObject>> _scene_objects;
};

#endif