#include "AppController.h"
#include <QStandardPaths>
#include <QDir>
#include <QDebug>

AppController::AppController(QObject *parent)
    : QObject(parent)
{
    m_camera.setOutputDirectory(QStandardPaths::writableLocation(QStandardPaths::PicturesLocation));
}

void AppController::pickFromGallery()
{
    // In Aurora, QFileDialog can be used via QML FileDialog; here we simulate by using last stored path
    const QUrl last = m_settings.lastImage();
    if (last.isEmpty()) {
        qDebug() << "No gallery image configured";
        return;
    }
    setImage(last);
}

void AppController::captureFromCamera()
{
    const QUrl captured = m_camera.captureImage();
    if (!captured.isEmpty()) {
        m_settings.setLastImage(captured);
        setImage(captured);
    }
}

QVariantMap AppController::runInference()
{
    QVariantMap map;
    if (!hasImage()) {
        map["label"] = QStringLiteral("Нет изображения");
        map["confidence"] = 0.0;
        return map;
    }

    QImage image(m_currentImage.toLocalFile());
    cv::Mat mat = m_processor.toMat(image);
    const auto result = m_classifier.classify(mat);

    map["label"] = result.label;
    map["confidence"] = result.confidence;
    return map;
}

void AppController::enqueueSample(const QString &label)
{
    if (!hasImage()) {
        qWarning() << "No image to enqueue";
        return;
    }
    m_trainer.addSample(m_currentImage.toLocalFile(), label);
    emit trainingStateChanged();
}

void AppController::startTraining()
{
    if (!m_trainer.canTrain())
        return;
    m_trainer.trainAsync();
    connect(&m_trainer, &MlPackTrainer::progressChanged, this, [this]() {
        emit trainingProgressChanged();
    });
}

void AppController::setImage(const QUrl &url)
{
    m_currentImage = url;
    emit imageChanged();
}
