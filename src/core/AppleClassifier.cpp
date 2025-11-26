#include "AppleClassifier.h"
#include <algorithm>

AppleClassifier::AppleClassifier()
{
    m_ncnn.load(":/models/yolo11.param", ":/models/yolo11.bin");
    m_tflite.load(":/models/applecheck.tflite");
}

ClassifyResult AppleClassifier::classify(const cv::Mat &mat)
{
    cv::Mat pre = m_processor.preprocess(mat);

    DetectionResult fast = m_ncnn.infer(pre);
    DetectionResult precise = m_tflite.infer(pre);

    // Fuse results: prefer highest confidence
    DetectionResult best = fast.confidence > precise.confidence ? fast : precise;

    ClassifyResult out;
    out.label = best.label;
    out.confidence = best.confidence;

    // Decision smoothing
    if (out.confidence < 0.5) {
        out.label = QStringLiteral("Не яблоко");
        out.confidence = 0.5;
    }
    return out;
}
