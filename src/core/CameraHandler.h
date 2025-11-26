#pragma once

#include <QObject>
#include <QUrl>
#include <QString>
#include <QCamera>
#include <QCameraImageCapture>

class CameraHandler : public QObject
{
    Q_OBJECT
public:
    explicit CameraHandler(QObject *parent = nullptr);

    void setOutputDirectory(const QString &dir);
    QUrl captureImage();

signals:
    void imageCaptured(const QUrl &path);

private:
    QString m_outputDir;
    QScopedPointer<QCamera> m_camera;
    QScopedPointer<QCameraImageCapture> m_capture;
};
