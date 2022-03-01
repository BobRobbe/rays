#include <iostream>
#include <thread>
#include <vector>

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>


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

    return 0;
}
