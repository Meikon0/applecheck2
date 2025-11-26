#include "image_classifier.h"

#include <QtMath>

ImageClassifier::ImageClassifier(QObject *parent)
    : QObject(parent)
{
}

static double computeSaturationScore(const QImage &image)
{
    if (image.isNull()) {
        return 0.0;
    }

    double totalS = 0.0;
    int count = 0;

    for (int y = 0; y < image.height(); ++y) {
        const QRgb *row = reinterpret_cast<const QRgb *>(image.constScanLine(y));
        for (int x = 0; x < image.width(); ++x) {
            QColor c(row[x]);
            totalS += c.saturationF();
            ++count;
        }
    }

    if (count == 0) {
        return 0.0;
    }

    return totalS / static_cast<double>(count);
}

static double computeRoundnessScore(const QImage &image)
{
    if (image.isNull()) {
        return 0.0;
    }

    // Simple heuristic: evaluate how centered brighter pixels are to infer roundness.
    const int centerX = image.width() / 2;
    const int centerY = image.height() / 2;
    double radialDeviation = 0.0;
    int samples = 0;

    for (int y = 0; y < image.height(); ++y) {
        const QRgb *row = reinterpret_cast<const QRgb *>(image.constScanLine(y));
        for (int x = 0; x < image.width(); ++x) {
            QColor c(row[x]);
            if (c.value() < 32) {
                continue;
            }
            const int dx = x - centerX;
            const int dy = y - centerY;
            radialDeviation += std::abs(dx) + std::abs(dy);
            ++samples;
        }
    }

    if (samples == 0) {
        return 0.0;
    }

    const double averageDeviation = radialDeviation / static_cast<double>(samples);
    const double maxDeviation = centerX + centerY + 1;
    double roundness = 1.0 - qBound(0.0, averageDeviation / maxDeviation, 1.0);
    return roundness;
}

ImageClassifier::ClassificationResult ImageClassifier::classify(const QImage &image) const
{
    if (image.isNull() || image.width() < 32 || image.height() < 32) {
        return {Verdict::NotApple, 0.1};
    }

    const double saturationScore = computeSaturationScore(image);
    const double roundnessScore = computeRoundnessScore(image);

    double appleLikelihood = (saturationScore * 0.6) + (roundnessScore * 0.4);
    appleLikelihood = qBound(0.0, appleLikelihood, 1.0);

    if (appleLikelihood < 0.25) {
        return {Verdict::NotApple, 1.0 - appleLikelihood};
    }

    // Use simple thresholds to approximate "good" vs "bad" apple.
    if (saturationScore > 0.45 && roundnessScore > 0.55) {
        return {Verdict::GoodApple, appleLikelihood};
    }

    return {Verdict::BadApple, 1.0 - std::abs(0.5 - appleLikelihood)};
}

QString ImageClassifier::verdictToLabel(ImageClassifier::Verdict verdict) const
{
    switch (verdict) {
    case Verdict::GoodApple:
        return tr("Хорошее яблоко");
    case Verdict::BadApple:
        return tr("Плохое яблоко");
    case Verdict::NotApple:
    default:
        return tr("Не яблоко");
    }
}
