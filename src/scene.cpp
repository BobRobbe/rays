#include <cmath>

#include "scene.h"

Scene::Scene() {}
Scene::~Scene() {}

void Scene::add_object(std::shared_ptr<RenderObject> obj)
{
    _scene_objects.push_back(obj);
}

void Scene::compute_part(Coordinate3d camera_pos, int image_width, int image_height, int start_y, int end_y, cv::Mat3b img)
{
    double viewport_width = 1.0;
    double viewport_height = 1.0;
    double viewport_d = 1.0;

    Vector3d unit_horizontal{viewport_width, 0, 0};
    Vector3d unit_vertical{0, viewport_height, 0};
    Vector3d unit_distance{0, 0, viewport_d};
    Vector3d viewport_lower_left{camera_pos - unit_horizontal / 2 - unit_vertical / 2 - unit_distance};

    double viewport_u, viewport_v;
    cv::Vec3b color;
    Color3d pixel_color;
    int x, y;

    for (y = end_y; y >= start_y; --y)
    {
        for (x = 0; x < img.cols; ++x)
        {
            // get pixel
            color = img.at<cv::Vec3b>(y, x);

            viewport_u = static_cast<double>(x) / (image_width - 1);
            viewport_v = static_cast<double>(y) / (image_height - 1);
            Ray3d ray(camera_pos, viewport_lower_left + unit_horizontal * viewport_u + unit_vertical * viewport_v - camera_pos);

            // compute color of hit object
            // might bounce due to reflection, initial bounce counter = 0
            pixel_color = this->simple_ray_trace(ray, 0);

            // change color
            color[0] = pixel_color.b_integer();
            color[1] = pixel_color.g_integer();
            color[2] = pixel_color.r_integer();

            // set pixel
            img.at<cv::Vec3b>(cv::Point(x, y)) = color;
        }
    }
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