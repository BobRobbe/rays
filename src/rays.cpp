#include <iostream>
#include <thread>
#include <vector>
#include <memory>
#include <chrono>

// include opencv
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

// include Rays headers
#include "ray3d.h"
#include "color3d.h"
#include "rendersphere.h"
#include "rendersky.h"
#include "renderplane.h"

// example Scene to be filled in main()
Scene scene{};

/* Main function */
int main()
{
    std::string _windowName{"Rays!"};

    // test scene setup
    scene.add_object(std::make_shared<RenderSphere>(Coordinate3d(2, -2, -12),
                                                    2.0,
                                                    Color3d(0.8, 0.8, 0.8, MKind::mirror)));
    scene.add_object(std::make_shared<RenderSphere>(Coordinate3d(-3, -3, -8),
                                                    1.0,
                                                    Color3d(0.8, 0.8, 0.4, MKind::phong)));
    scene.add_object(std::make_shared<RenderSphere>(Coordinate3d(0.5, 0.8, 1),
                                                    3.0,
                                                    Color3d(0.4, 0.8, 0.8, MKind::mirror)));

    for (int i = -20; i < 20; ++i)
    {
        scene.add_object(std::make_shared<RenderSphere>(Coordinate3d(i, 0.8, -5),
                                                        0.3,
                                                        Color3d(0.9, 0.0, 0.0, MKind::mirror)));
    }

    scene.add_object(std::make_shared<RenderPlane>(Coordinate3d(0, 10, 0),
                                                   Vector3d(0, 1.0, 0),
                                                   Color3d(0.7, 0.7, 0.7, MKind::checkered)));

    scene.add_object(std::make_shared<RenderSky>(Coordinate3d(INFINITY, INFINITY, INFINITY),
                                                 Color3d(1.0, 1.0, 1.0, MKind::sky)));

    // https://en.wikipedia.org/wiki/Ray_tracing_(graphics)
    // picture
    const int image_width = 800;
    const int image_height = 800;

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

    // opencv image for final display/save
    cv::Mat3b img(image_height, image_width, cv::Vec3b(0, 0, 0));

    // grab timestamp to calculate the render time
    auto start = std::chrono::high_resolution_clock::now();

    const int no_threads = 4;
    int slice = image_height / no_threads;

    std::vector<std::thread> threads;
    for (size_t i = 0; i < no_threads; ++i)
    {
        // create new thread
        threads.emplace_back(std::thread(&Scene::compute_part, scene, camera_pos, image_width, image_height,
                                         slice * i, slice * i + slice - 1, img));
    }

    // call join on all thread objects using a range-based loop
    for (auto &t : threads)
        t.join();

    // grab timestamp to calculate the render time
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Elapsed time: " << elapsed.count() << " s\n";

    // display image and save to file
    cv::namedWindow(_windowName);
    cv::imshow(_windowName, img);
    cv::imwrite("../image.png", img);

    // wait for key before quiting
    cv::waitKey(0);

    return 0;
}
