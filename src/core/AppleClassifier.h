#pragma once

#include <QString>
#include <opencv2/core.hpp>
#include "NcnnInference.h"
#include "TfliteInference.h"
#include "ImageProcessor.h"

struct ClassifyResult {
    QString label;
    double confidence;
};

class AppleClassifier
{
public:
    AppleClassifier();
    ClassifyResult classify(const cv::Mat &mat);

private:
    ImageProcessor m_processor;
    NcnnInference m_ncnn;
    TfliteInference m_tflite;
};
