#pragma once

#include <QObject>
#include <QString>
#include <vector>

class MlPackTrainer : public QObject
{
    Q_OBJECT
public:
    explicit MlPackTrainer(QObject *parent = nullptr);

    void addSample(const QString &path, const QString &label);
    bool canTrain() const;
    void trainAsync();
    double progress() const { return m_progress; }

signals:
    void progressChanged();

private:
    std::vector<std::pair<QString, QString>> m_samples;
    double m_progress = 0.0;
};
