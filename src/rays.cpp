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

// parse arguments
// https://stackoverflow.com/questions/865668/parsing-command-line-arguments-in-c
class InputParser
{
public:
    InputParser(int &argc, char **argv)
    {
        for (int i = 1; i < argc; ++i)
            this->tokens.push_back(std::string(argv[i]));
    }
    /// @author iain
    const std::string &getCmdOption(const std::string &option) const
    {
        std::vector<std::string>::const_iterator itr;
        itr = std::find(this->tokens.begin(), this->tokens.end(), option);
        if (itr != this->tokens.end() && ++itr != this->tokens.end())
        {
            return *itr;
        }
        static const std::string empty_string("");
        return empty_string;
    }
    /// @author iain
    bool cmdOptionExists(const std::string &option) const
    {
        return std::find(this->tokens.begin(), this->tokens.end(), option) != this->tokens.end();
    }

private:
    std::vector<std::string> tokens;
};

// example Scene to be filled in main()
Scene scene{};

void print_usage()
{
    std::cout << "usage: rays [options]" << std::endl;
    std::cout << "  -h    this help" << std::endl;
    std::cout << "  -f    output file name (../image.png default)" << std::endl;
    std::cout << "  -b    number of mirror bounces to be considered (default 5)" << std::endl;
    std::cout << "  -t    number of threads to render in parallel (default 4)" << std::endl;
    std::cout << "  -s    size of the rendered image (default 800)" << std::endl;
}

/* Main function */
int main(int argc, char **argv)
{
    std::string _windowName{"Rays!"};

    // https://en.wikipedia.org/wiki/Ray_tracing_(graphics)
    // picture
    int image_width = 800;
    std::string file_name = "../image.png";
    int number_threads = 4;
    int max_bounce = 5;

    // parse input arguments
    InputParser input(argc, argv);

    // help
    if (input.cmdOptionExists("-h"))
    {
        print_usage();
        return 0;
    }

    // file name
    const std::string &filename = input.getCmdOption("-f");
    if (!filename.empty())
    {
        file_name = filename;
    }

    // number of threads
    const std::string &threads_string = input.getCmdOption("-t");
    if (!threads_string.empty())
    {
        try
        {
            number_threads = std::stoi(threads_string);
        }
        catch (...)
        {
            print_usage();
            return 0;
        }
    }

    // mirror bounce limit
    const std::string &bounce_string = input.getCmdOption("-b");
    if (!bounce_string.empty())
    {
        try
        {
            max_bounce = std::stoi(bounce_string);
        }
        catch (...)
        {
            print_usage();
            return 0;
        }
    }
    scene.max_bounce = max_bounce;

    // image size
    const std::string &size_string = input.getCmdOption("-s");
    if (!size_string.empty())
    {
        try
        {
            image_width = std::stoi(size_string);
        }
        catch (...)
        {
            print_usage();
            return 0;
        }
    }

    // test scene setup
    // lights
    scene.add_object(std::make_shared<RenderSphere>(Coordinate3d(2000, -2000, 1000),
                                                    600,
                                                    Color3d(1, 1, 1, MKind::light)));
    scene.add_object(std::make_shared<RenderSphere>(Coordinate3d(-2000, -2000, 1000),
                                                    600,
                                                    Color3d(1, 1, 1, MKind::light)));

    // spheres
    scene.add_object(std::make_shared<RenderSphere>(Coordinate3d(2, -2.2, -12),
                                                    2.0,
                                                    Color3d(0.8, 0.8, 0.8, MKind::mirror)));
    scene.add_object(std::make_shared<RenderSphere>(Coordinate3d(-2.5, -2.5, -8),
                                                    1.0,
                                                    Color3d(0.8, 0.8, 0.4, MKind::mirror)));
    scene.add_object(std::make_shared<RenderSphere>(Coordinate3d(0.5, 0.8, 1),
                                                    3.0,
                                                    Color3d(0.4, 0.8, 0.8, MKind::mirror)));
    // a line of spheres
    for (int i = -20; i < 20; ++i)
    {
        scene.add_object(std::make_shared<RenderSphere>(Coordinate3d(i, 0.8, -5),
                                                        0.3,
                                                        Color3d(0.9, 0.0, 0.0, MKind::mirror)));
    }

    // plane
    scene.add_object(std::make_shared<RenderPlane>(Coordinate3d(0, 1.5, 0),
                                                   Vector3d(0, 1.0, 0),
                                                   Color3d(0.8, 0.8, 0.8, MKind::checkered)));
    // sky
    scene.add_object(std::make_shared<RenderSky>(Coordinate3d(INFINITY, INFINITY, INFINITY),
                                                 Color3d(1.0, 1.0, 1.0, MKind::sky)));

    // camera
    // https://gabrielgambetta.com/computer-graphics-from-scratch/02-basic-raytracing.html#canvas-to-viewport
    Coordinate3d camera_pos{0, 0, 0};

    // calculate the image height based on the given width
    // limitation: current implementation only supports square images
    int image_height = image_width;
    // opencv image for final display/save
    cv::Mat3b img(image_height, image_width, cv::Vec3b(0, 0, 0));

    // grab timestamp to calculate the render time
    auto start = std::chrono::high_resolution_clock::now();

    // consider number of threads to partition the image into slices
    int slice = image_height / number_threads;

    // create number_threads to calculate the slices
    std::vector<std::thread> threads;
    for (size_t i = 0; i < number_threads; ++i)
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
    std::cout << "Elapsed time: " << elapsed.count() << "seconds using " << number_threads << " of thread(s).\n";

    // display image and save to file
    cv::namedWindow(_windowName);
    cv::imshow(_windowName, img);
    cv::imwrite(file_name, img);

    // wait for key before quiting
    cv::waitKey(0);

    return 0;
}
