#include "resultimageprovider.h"

#include <QMutexLocker>

ResultImageProvider::ResultImageProvider() : QQuickImageProvider(QQuickImageProvider::Image)
{
}

QImage ResultImageProvider::requestImage(const QString &id, QSize *size,
                                         const QSize &requestedSize)
{
    QMutexLocker locker(&m_mutex);
    const QString key = id.section(QLatin1Char('/'), 0, 0);
    QImage result = m_images.value(key);

    if (size)
        *size = result.size();

    if (!requestedSize.isEmpty() && !result.isNull()) {
        return result.scaled(requestedSize, Qt::KeepAspectRatio,
                             Qt::SmoothTransformation);
    }

    return result;
}

void ResultImageProvider::setImage(const QString &key, const QImage &image)
{
    QMutexLocker locker(&m_mutex);
    if (image.isNull())
        m_images.remove(key);
    else
        m_images.insert(key, image);
}

void ResultImageProvider::clear()
{
    QMutexLocker locker(&m_mutex);
    m_images.clear();
}
