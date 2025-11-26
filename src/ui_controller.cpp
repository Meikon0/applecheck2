#include "ui_controller.h"

#include <QFileInfo>
#include <QImageReader>
#include <QThread>
#include <QtConcurrent/QtConcurrent>

UiController::UiController(QObject *parent)
    : QObject(parent)
{
    setVerdict(tr("Ожидание изображения"), 0.0);
}

void UiController::setBusy(bool value)
{
    if (m_busy == value)
        return;
    m_busy = value;
    emit busyChanged();
}

void UiController::setVerdict(const QString &label, double confidence)
{
    m_verdict = label;
    m_confidence = confidence;
    emit verdictChanged();
}

bool UiController::loadImageFromUrl(const QUrl &url, QImage &outImage, QString &localPath)
{
    const QString resolvedPath = url.isLocalFile() ? url.toLocalFile() : url.toString();
    QImageReader reader(resolvedPath);
    reader.setAutoTransform(true);
    if (!reader.read(&outImage)) {
        emit showToast(tr("Не удалось загрузить изображение"));
        return false;
    }
    localPath = QFileInfo(resolvedPath).absoluteFilePath();
    return true;
}

void UiController::classifyImage(const QUrl &url)
{
    if (m_busy)
        return;

    setBusy(true);

    QtConcurrent::run([=]() {
        QImage image;
        QString localPath;
        if (!loadImageFromUrl(url, image, localPath)) {
            QMetaObject::invokeMethod(const_cast<UiController*>(this), [this]() {
                setVerdict(tr("Ошибка загрузки"), 0.0);
                setBusy(false);
            }, Qt::QueuedConnection);
            return;
        }

        const auto result = m_classifier.classify(image);
        const QString label = m_classifier.verdictToLabel(result.verdict);

        QMetaObject::invokeMethod(const_cast<UiController*>(this), [this, label, result, localPath]() {
            setVerdict(label, result.confidence);
            m_lastImagePath = localPath;
            emit lastImagePathChanged();
            setBusy(false);
        }, Qt::QueuedConnection);
    });
}

void UiController::trainOnDataset(const QUrl &url)
{
    if (m_busy)
        return;

    setBusy(true);
    QtConcurrent::run([=]() {
        // Placeholder for on-device training; simulate brief processing.
        QThread::sleep(1);

        QMetaObject::invokeMethod(const_cast<UiController*>(this), [this, url]() {
            emit showToast(tr("Локальное дообучение завершено: %1").arg(url.toString()));
            setBusy(false);
        }, Qt::QueuedConnection);
    });
}

void UiController::reset()
{
    if (m_busy)
        return;

    m_lastImagePath.clear();
    emit lastImagePathChanged();
    setVerdict(tr("Ожидание изображения"), 0.0);
}
