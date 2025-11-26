#pragma once

#include <opencv2/core.hpp>
#include <QImage>

class ImageProcessor
{
public:
    ImageProcessor();
    cv::Mat toMat(const QImage &image) const;
    cv::Mat preprocess(const cv::Mat &input) const;
};
