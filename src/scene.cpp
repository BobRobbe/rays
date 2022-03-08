#include <cmath>

#include "scene.h"

Scene::Scene() {}
Scene::~Scene() {}

void Scene::add_object(std::shared_ptr<RenderObject> obj)
{
    _scene_objects.push_back(obj);
}

Color3d Scene::simple_ray_trace(const Ray3d &ray, int depth)
{
    // store candidates for the object which is closest to the ray origin
    std::shared_ptr<RenderObject> closestObject = nullptr;
    double closestDistance = INFINITY;

    // iterate through all RenderObjects to find the collision of the ray
    for (auto it = _scene_objects.begin(); it < _scene_objects.end(); ++it)
    {
        // check whether iterated object is hit by the ray
        double distance = (*it)->hits_render_object(*this, ray);
        // if ray hits the object AND the hit is closer than the previous candidate,
        // then current object becomes the new candidate
        if (distance > 0 && distance <= closestDistance)
        {
            closestObject = *it;
            closestDistance = distance;
        }
    }
    // we have found an object where ray hits and is closest
    if (closestObject != nullptr)
    {
        // calculate the color of the ray
        return closestObject->get_color(*this, ray, closestDistance, depth);
    }
    else
    {
        return Color3d(0, 0, 0);
    }
}