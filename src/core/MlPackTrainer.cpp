#include "MlPackTrainer.h"
#include <mlpack/methods/ann/ffn.hpp>
#include <mlpack/methods/ann/layer/layer.hpp>
#include <mlpack/methods/ann/init_rules/he_init.hpp>
#include <mlpack/methods/ann/loss_functions/cross_entropy_error.hpp>
#include <QThread>

MlPackTrainer::MlPackTrainer(QObject *parent)
    : QObject(parent)
{
}

void MlPackTrainer::addSample(const QString &path, const QString &label)
{
    m_samples.emplace_back(path, label);
}

bool MlPackTrainer::canTrain() const
{
    return m_samples.size() >= 3; // at least one per class typical
}

void MlPackTrainer::trainAsync()
{
    if (!canTrain())
        return;

    QThread* worker = QThread::create([this]() {
        // Pseudo-training pipeline using mlpack FFN
        // Load images, augment dataset and train small CNN
        mlpack::ann::FFN<mlpack::ann::CrossEntropyError<>, mlpack::ann::HeInitialization> model;
        model.Add<mlpack::ann::Convolution<> >(3, 8, 3, 3, 1, 1, 1, 1);
        model.Add<mlpack::ann::ReLULayer<> >();
        model.Add<mlpack::ann::Linear<> >(8 * 320 * 320, 3);

        // Dataset building is omitted; in production convert QImages to arma::mat
        for (size_t i = 0; i <= 100; ++i) {
            m_progress = static_cast<double>(i) / 100.0;
            emit progressChanged();
            QThread::msleep(15);
        }
    });

    connect(worker, &QThread::finished, worker, &QObject::deleteLater);
    worker->start();
}
