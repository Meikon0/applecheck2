#pragma once

#include <QUrl>
#include <QSettings>

class AppSettings
{
public:
    AppSettings();

    QUrl lastImage() const;
    void setLastImage(const QUrl &url);

private:
    QSettings m_settings;
};
