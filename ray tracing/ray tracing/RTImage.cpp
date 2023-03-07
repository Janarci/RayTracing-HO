#include "RTImage.h"

#include "rtweekend.h"


RTImage::RTImage(const int imageWidth, const int imageHeight)
{

	this->imageWidth = imageWidth;
	this->imageHeight = imageHeight;



	this->pixels = std::make_unique<cv::Mat>(cv::Mat::zeros(this->imageHeight, this->imageWidth, CV_8UC3));





}

void RTImage::setPixel(int x, int y, float r, float g, float b, int samplesPerPixel)
{

    auto scale = 1.0 / samplesPerPixel;

    r = sqrt(scale * r);
    g = sqrt(scale * g);
    b = sqrt(scale * b);


    int rInt = static_cast<uchar>(256 * clamp(r, 0.0, 0.999));
    int gInt = static_cast<uchar>(256 * clamp(r, 0.0, 0.999));
    int bInt = static_cast<uchar>(256 * clamp(r, 0.0, 0.999));

    cv::Mat imgChannels[3];
    cv::split(*this->pixels, imgChannels);

    imgChannels[0].at<uchar>(this->imageHeight - 1 - y, x) = bInt;
    imgChannels[1].at<uchar>(this->imageHeight - 1 - y, x) = gInt;
    imgChannels[2].at<uchar>(this->imageHeight - 1 - y, x) = rInt;

    cv::merge(imgChannels, 3, *this->pixels);

    // Write the translated [0,255] value of each color component.
   


}

void RTImage::saveImage(cv::String& fileName) const
{
	cv::imwrite(fileName, *this->pixels);
}