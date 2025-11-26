#include "NcnnInference.h"
#include <ncnn/net.h>

NcnnInference::NcnnInference() = default;

bool NcnnInference::load(const QString &paramPath, const QString &binPath)
{
    // placeholder load logic using NCNN API; actual graph built at runtime
    ncnn::Net net;
    if (net.load_param(paramPath.toStdString().c_str()) || net.load_model(binPath.toStdString().c_str())) {
        m_loaded = true;
    }
    return m_loaded;
}

DetectionResult NcnnInference::infer(const cv::Mat &input) const
{
    DetectionResult result{QStringLiteral("Не яблоко"), 0.0f};
    if (!m_loaded)
        return result;

    ncnn::Mat ncnnIn = ncnn::Mat::from_pixels(input.data, ncnn::Mat::PIXEL_RGB, input.cols, input.rows);
    ncnn::Extractor ex;
    // simplified example; in real project we would hold the Net and use ex = net.create_extractor()
    // ex.input("input", ncnnIn);
    // ex.extract("output", ncnn::Mat out);
    // Post-processing to decode YOLO11-segm / YOLACT masks here

    // Demo decision
    result.label = QStringLiteral("Хорошее яблоко");
    result.confidence = 0.92f;
    return result;
}
