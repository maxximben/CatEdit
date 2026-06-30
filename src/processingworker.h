#ifndef PROCESSINGWORKER_H
#define PROCESSINGWORKER_H

#include <QImage>
#include <QObject>
#include <QString>
#include <QVector>

class ProcessingWorker : public QObject
{
    Q_OBJECT

public slots:
    void importImage(const QString &filePath);
    void removeBackground();
    void enhance();
    void blackWhite();
    void sepia();
    void undo();
    void reset();
    void exportResult();

signals:
    void stateReady(const QImage &original, const QImage &current, bool canUndo,
                    const QString &statusText, const QString &errorText);

private:
    bool ensureImage();
    void pushHistory();
    void emitState(const QString &statusText, const QString &errorText = QString());

    QImage m_original;
    QImage m_current;
    QVector<QImage> m_history;
};

#endif // PROCESSINGWORKER_H
