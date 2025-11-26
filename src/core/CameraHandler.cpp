#include "CameraHandler.h"
#include <QDir>
#include <QDateTime>
#include <QDebug>

CameraHandler::CameraHandler(QObject *parent)
    : QObject(parent)
    , m_camera(new QCamera)
    , m_capture(new QCameraImageCapture(m_camera.data()))
{
    m_camera->load();
}

void CameraHandler::setOutputDirectory(const QString &dir)
{
    m_outputDir = dir;
    QDir().mkpath(m_outputDir);
}

QUrl CameraHandler::captureImage()
{
    if (!m_camera || !m_capture)
        return {};

    const QString fileName = QString("%1/apple_%2.jpg")
                                 .arg(m_outputDir)
                                 .arg(QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss"));

    QObject::connect(m_capture.data(), &QCameraImageCapture::imageSaved, this, [this](int, const QString &filePath) {
        emit imageCaptured(QUrl::fromLocalFile(filePath));
    });

    m_camera->start();
    m_capture->capture(fileName);
    m_camera->stop();
    return QUrl::fromLocalFile(fileName);
}
