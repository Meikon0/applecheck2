#pragma once

#include <QObject>
#include <QImage>
#include <QString>

class ImageClassifier : public QObject
{
    Q_OBJECT
public:
    explicit ImageClassifier(QObject *parent = nullptr);

    enum class Verdict {
        GoodApple,
        BadApple,
        NotApple
    };
    Q_ENUM(Verdict)

    struct ClassificationResult {
        Verdict verdict;
        double confidence;
    };

    ClassificationResult classify(const QImage &image) const;
    QString verdictToLabel(Verdict verdict) const;
};
