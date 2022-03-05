#include <iostream>
#include <thread>
#include <vector>
#include <memory>

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include "ray3d.h"
#include "color3d.h"
#include "rendersphere.h"
#include "rendersky.h"
#include "renderplane.h"

std::vector<std::shared_ptr<RenderObject>> scene_objects;

// testing raytracer
Color3d simple_ray_trace(const Ray3d &ray)
{
    for (auto it = scene_objects.begin(); it < scene_objects.end(); ++it)
    {
        double distance = (*it)->hits_render_object(ray);
        if ( distance > 0.0 )
        {
            return (*it)->get_color(ray, distance);
        }
    }
    return Color3d(0, 0, 0);
}

/* Main function */
int main()
{
    std::cout << "Rays!" << std::endl;
    std::string _windowName{"Rays!"};

    // test scene setup
    auto s1 = std::make_shared<RenderSphere>(Coordinate3d(0, 0, -1), 0.2);
    s1->set_color(Color3d(1.0, 0.0, 0.0));
    scene_objects.push_back(s1);

    auto s2 = std::make_shared<RenderSphere>(Coordinate3d(-0.6, -0.7, -2), 0.2);
    s2->set_color(Color3d(0.0, 1.0, 0.0));
    scene_objects.push_back(s2);

    auto p1 = std::make_shared<RenderPlane>(Coordinate3d(0, 2, 0), Vector3d(0, 1.0, 0));
    p1->set_color(Color3d(0.0, 1.0, 0.0));
    scene_objects.push_back(p1);

    auto rs = std::make_shared<RenderSky>(Coordinate3d(INFINITY, INFINITY, INFINITY));
    rs->set_color(Color3d(1.0, 1.0, 1.0));
    scene_objects.push_back(rs);

    // https://en.wikipedia.org/wiki/Ray_tracing_(graphics)
    // picture
    const int image_width = 400;
    const int image_height = 400;

    // camera
    // https://gabrielgambetta.com/computer-graphics-from-scratch/02-basic-raytracing.html#canvas-to-viewport

    double viewport_width = 1.0;
    double viewport_height = 1.0;
    double viewport_d = 1.0;

    Coordinate3d camera_pos{0, 0, 0};
    Vector3d unit_horizontal{viewport_width, 0, 0};
    Vector3d unit_vertical{0, viewport_height, 0};
    Vector3d unit_distance{0, 0, viewport_d};
    Vector3d viewport_lower_left{camera_pos - unit_horizontal / 2 - unit_vertical / 2 - unit_distance};

    cv::Mat3b img(image_height, image_width, cv::Vec3b(100, 100, 100));

    for (int y = image_height - 1; y >= 0; --y)
    {
        for (int x = 0; x < img.cols; ++x)
        {
            // get pixel
            cv::Vec3b color = img.at<cv::Vec3b>(y, x);

            double viewport_u = static_cast<double>(x) / (image_width - 1);
            double viewport_v = static_cast<double>(y) / (image_height - 1);
            Ray3d ray(camera_pos, viewport_lower_left + unit_horizontal * viewport_u + unit_vertical * viewport_v - camera_pos);

            // testing raytracing
            Color3d pixel_color = simple_ray_trace(ray);

            // change color
            color[0] = pixel_color.b_integer();
            color[1] = pixel_color.g_integer();
            color[2] = pixel_color.r_integer();

            // set pixel
            img.at<cv::Vec3b>(cv::Point(x, y)) = color;
        }
    }

    cv::namedWindow(_windowName);
    cv::imshow(_windowName, img);

    cv::waitKey(0);

    return 0;
}
