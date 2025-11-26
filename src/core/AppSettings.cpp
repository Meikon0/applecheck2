#include "AppSettings.h"

AppSettings::AppSettings()
    : m_settings("aurora", "AppleCheck")
{
}

QUrl AppSettings::lastImage() const
{
    return m_settings.value("lastImage").toUrl();
}

void AppSettings::setLastImage(const QUrl &url)
{
    m_settings.setValue("lastImage", url);
}
