#pragma once

#include <QObject>
#include <QImage>
#include <QUrl>
#include <QVariantMap>

#include "CameraHandler.h"
#include "ImageProcessor.h"
#include "AppleClassifier.h"
#include "MlPackTrainer.h"
#include "AppSettings.h"

class AppController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QUrl currentImage READ currentImage NOTIFY imageChanged)
    Q_PROPERTY(bool hasImage READ hasImage NOTIFY imageChanged)
    Q_PROPERTY(double trainingProgress READ trainingProgress NOTIFY trainingProgressChanged)
    Q_PROPERTY(bool canTrain READ canTrain NOTIFY trainingStateChanged)

public:
    explicit AppController(QObject *parent = nullptr);

    QUrl currentImage() const { return m_currentImage; }
    bool hasImage() const { return !m_currentImage.isEmpty(); }

    Q_INVOKABLE void pickFromGallery();
    Q_INVOKABLE void captureFromCamera();
    Q_INVOKABLE QVariantMap runInference();
    Q_INVOKABLE void enqueueSample(const QString &label);
    Q_INVOKABLE void startTraining();

    double trainingProgress() const { return m_trainer.progress(); }
    bool canTrain() const { return m_trainer.canTrain(); }

signals:
    void imageChanged();
    void trainingProgressChanged();
    void trainingStateChanged();

private:
    void setImage(const QUrl &url);

    QUrl m_currentImage;
    CameraHandler m_camera;
    ImageProcessor m_processor;
    AppleClassifier m_classifier;
    MlPackTrainer m_trainer;
    AppSettings m_settings;
};
