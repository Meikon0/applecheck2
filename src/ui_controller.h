#pragma once

#include <QObject>
#include <QImage>
#include <QUrl>

#include "image_classifier.h"

class UiController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString verdict READ verdict NOTIFY verdictChanged)
    Q_PROPERTY(double confidence READ confidence NOTIFY verdictChanged)
    Q_PROPERTY(bool busy READ busy NOTIFY busyChanged)
    Q_PROPERTY(QString lastImagePath READ lastImagePath NOTIFY lastImagePathChanged)
public:
    explicit UiController(QObject *parent = nullptr);

    QString verdict() const { return m_verdict; }
    double confidence() const { return m_confidence; }
    bool busy() const { return m_busy; }
    QString lastImagePath() const { return m_lastImagePath; }

    Q_INVOKABLE void classifyImage(const QUrl &url);
    Q_INVOKABLE void trainOnDataset(const QUrl &url);
    Q_INVOKABLE void reset();

signals:
    void verdictChanged();
    void busyChanged();
    void lastImagePathChanged();
    void showToast(const QString &message);

private:
    void setBusy(bool value);
    void setVerdict(const QString &label, double confidence);
    bool loadImageFromUrl(const QUrl &url, QImage &outImage, QString &localPath);

    ImageClassifier m_classifier;
    QString m_verdict;
    double m_confidence = 0.0;
    bool m_busy = false;
    QString m_lastImagePath;
};
