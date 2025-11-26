#pragma once

#include <QString>
#include <vector>
#include <opencv2/core.hpp>

struct DetectionResult {
    QString label;
    float confidence;
};

class NcnnInference
{
public:
    NcnnInference();
    bool load(const QString &paramPath, const QString &binPath);
    DetectionResult infer(const cv::Mat &input) const;

private:
    bool m_loaded = false;
};
