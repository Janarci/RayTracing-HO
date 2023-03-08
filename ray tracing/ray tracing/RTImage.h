#pragma once
#pragma once

#include <vector>
#include "opencv2/core.hpp"
#include <opencv2\highgui\highgui.hpp>
#include <opencv2/imgproc.hpp>

class RTImage
{

public:
	RTImage(const int imageWidth, const int imageHeight);

	void setPixel(int x, int y, float r, float g, float b, int samplesPerPixel);
	void saveImage(cv::String &filename) const;

	bool critical;

private:
	
	std::unique_ptr<cv::Mat> pixels;
	int imageWidth;
	int imageHeight;

};
