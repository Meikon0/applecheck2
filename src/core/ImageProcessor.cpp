#include "ImageProcessor.h"
#include <opencv2/imgproc.hpp>

ImageProcessor::ImageProcessor() = default;

cv::Mat ImageProcessor::toMat(const QImage &image) const
{
    QImage conv = image.convertToFormat(QImage::Format_RGBA8888);
    cv::Mat mat(conv.height(), conv.width(), CV_8UC4, const_cast<uchar*>(conv.bits()), conv.bytesPerLine());
    return mat.clone();
}

cv::Mat ImageProcessor::preprocess(const cv::Mat &input) const
{
    cv::Mat resized;
    cv::resize(input, resized, cv::Size(320, 320));
    cv::Mat rgb;
    cv::cvtColor(resized, rgb, cv::COLOR_BGRA2RGB);
    rgb.convertTo(rgb, CV_32F, 1.0 / 255.0);
    return rgb;
}
