
#include "scene.h"

Scene::Scene() {}
Scene::~Scene() {}

void Scene::add_object(std::shared_ptr<RenderObject> obj)
{
    _scene_objects.push_back(obj);
}

Color3d Scene::simple_ray_trace(const Ray3d &ray, int depth)
{
    for (auto it = _scene_objects.begin(); it < _scene_objects.end(); ++it)
    {
        double distance = (*it)->hits_render_object(*this, ray);
        if (distance > 0.0)
        {
            return (*it)->get_color(*this, ray, distance, depth);
        }
    }
    return Color3d(0, 0, 0);
}