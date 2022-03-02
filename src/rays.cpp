#include <iostream>
#include <thread>
#include <vector>

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include "ray3d.h"
#include "color3d.h"

// simple sphere handling
// TODO: create class to handle sphere calculations
bool sphere(const Ray3d &ray, const Coordinate3d &center, double radius)
{
    Vector3d sphere_vector = ray.origin() - center;
    // implementing the sphere equation
    // https://gabrielgambetta.com/computer-graphics-from-scratch/02-basic-raytracing.html#the-sphere-equation
    double a = ray.direction().dot(ray.direction());
    double b = 2.0 * sphere_vector.dot(ray.direction());
    double c = sphere_vector.dot(sphere_vector) - radius * radius;
    // compute the value for the suare root
    double root = b * b - 4 * a * c;
    // no need to calculate the square root, just need to know whether
    // <= 0 : sphere is not in the rays path
    // > 0  : sphere got hit by the ray
    return (root > 0);
}

// testing raytracer
Color3d simple_ray_trace(const Ray3d &ray)
{
    // simple test, if ray hits sphere color that corresponding pixel red
    if (sphere(ray, Coordinate3d(0, 0, -1), 0.2))
    {
        return Color3d(1, 0, 0);
    }

    // no object has been hit, paint background sky gradient
    // get the ray vector normalized to length 1
    Vector3d direction = ray.direction().vector_unit();
    // check the height (y) amount to fetch the sky color
    double height = 0.3 * (direction.y() + 1.0);
    // calculate a color gradient for the sky
    return (Color3d(1.0, 1.0, 1.0) * (1.0 - height) + Color3d(0.3, 0.6, 1.0) * height);
}

/* Main function */
int main()
{
    std::cout << "Rays!" << std::endl;
    std::string _windowName{"Rays!"};

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
            // if you copy value
        }
    }

    cv::namedWindow(_windowName);
    cv::imshow(_windowName, img);

    cv::waitKey(0);

    return 0;
}
