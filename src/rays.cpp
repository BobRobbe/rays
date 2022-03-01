#include <iostream>
#include <thread>
#include <vector>

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include "ray3d.h"


/* Main function */
int main()
{
    std::cout << "Rays!" << std::endl;

    std::string _windowName{"Rays!"};

    cv::Mat3b img(255, 255, cv::Vec3b(100, 100, 100));

    cv::namedWindow(_windowName);

    cv::imshow(_windowName, img);

    for (int y = 0; y < img.rows; y++)
    {
        for (int x = 0; x < img.cols; x++)
        {
            // get pixel
            cv::Vec3b color = img.at<cv::Vec3b>(y, x);

            // ... do something to the color ....
            color[0] = y;
            color[1] = y;
            color[2] = x;

            // set pixel
            img.at<cv::Vec3b>(cv::Point(x,y)) = color;
            // if you copy value
        }
    }

    cv::imshow(_windowName, img);

    cv::waitKey(0);


    Coordinate3d coord1{10, 20, 30};
    Vector3d dir1{1, 2, 3};

    Ray3d ray1{coord1, dir1};

    std::cout << "x= " << ray1.x() << " dir.x= " << ray1.direction().x() << std::endl;

    return 0;
}
