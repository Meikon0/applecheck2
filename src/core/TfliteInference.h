#pragma once

#include <QString>
#include <opencv2/core.hpp>
#include "NcnnInference.h"

class TfliteInference
{
public:
    TfliteInference();
    bool load(const QString &modelPath);
    DetectionResult infer(const cv::Mat &input) const;

private:
    bool m_loaded = false;
};
