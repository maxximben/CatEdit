#ifndef RESULTIMAGEPROVIDER_H
#define RESULTIMAGEPROVIDER_H

#include <QImage>
#include <QHash>
#include <QMutex>
#include <QQuickImageProvider>

class ResultImageProvider : public QQuickImageProvider
{
public:
    ResultImageProvider();

    QImage requestImage(const QString &id, QSize *size,
                        const QSize &requestedSize) override;
    void setImage(const QString &key, const QImage &image);
    void clear();

private:
    QMutex m_mutex;
    QHash<QString, QImage> m_images;
};

#endif // RESULTIMAGEPROVIDER_H
