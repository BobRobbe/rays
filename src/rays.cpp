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

Scene scene{};

/* Main function */
int main()
{
    std::string _windowName{"Rays!"};

    // test scene setup
    scene.add_object(std::make_shared<RenderSphere>(Coordinate3d(0, 0, -1), Color3d(1.0, 0.0, 0.0), 0.2));
    scene.add_object(std::make_shared<RenderSphere>(Coordinate3d(-0.6, -0.7, -2), Color3d(0.5, 0.5, 0.0), 0.2));
    scene.add_object(std::make_shared<RenderPlane>(Coordinate3d(0, 2, 0), Color3d(0.3, 0.3, 0.3), Vector3d(0, 1.0, 0)));
    scene.add_object(std::make_shared<RenderSky>(Coordinate3d(INFINITY, INFINITY, INFINITY), Color3d(1.0, 1.0, 1.0)));

    // https://en.wikipedia.org/wiki/Ray_tracing_(graphics)
    // picture
    const int image_width = 600;
    const int image_height = 600;

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
            Color3d pixel_color = scene.simple_ray_trace(ray, 0);

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

    cv::imwrite("../image.png", img);

    cv::waitKey(0);

    return 0;
}
