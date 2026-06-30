#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <QObject>
#include <QThread>

class ProcessingWorker;
class ResultImageProvider;

class ImageProcessor : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString originalSource READ originalSource NOTIFY originalSourceChanged)
    Q_PROPERTY(QString resultSource READ resultSource NOTIFY resultSourceChanged)
    Q_PROPERTY(QString statusText READ statusText NOTIFY statusTextChanged)
    Q_PROPERTY(bool busy READ busy NOTIFY busyChanged)
    Q_PROPERTY(bool hasImage READ hasImage NOTIFY hasImageChanged)
    Q_PROPERTY(bool canUndo READ canUndo NOTIFY canUndoChanged)

public:
    explicit ImageProcessor(ResultImageProvider *provider, QObject *parent = nullptr);
    ~ImageProcessor();

    QString originalSource() const;
    QString resultSource() const;
    QString statusText() const;
    bool busy() const;
    bool hasImage() const;
    bool canUndo() const;

    Q_INVOKABLE void process(const QString &filePath);
    Q_INVOKABLE void removeBackground();
    Q_INVOKABLE void enhance();
    Q_INVOKABLE void blackWhite();
    Q_INVOKABLE void sepia();
    Q_INVOKABLE void undo();
    Q_INVOKABLE void reset();
    Q_INVOKABLE void exportResult();
    Q_INVOKABLE void clear();

signals:
    void importRequested(const QString &filePath);
    void backgroundRequested();
    void enhanceRequested();
    void blackWhiteRequested();
    void sepiaRequested();
    void undoRequested();
    void resetRequested();
    void exportRequested();
    void originalSourceChanged();
    void resultSourceChanged();
    void statusTextChanged();
    void busyChanged();
    void hasImageChanged();
    void canUndoChanged();

private slots:
    void handleStateReady(const QImage &original, const QImage &current, bool canUndo,
                          const QString &statusText, const QString &errorText);

private:
    void setStatusText(const QString &statusText);
    void setBusy(bool busy);
    void setHasImage(bool hasImage);
    void setCanUndo(bool canUndo);
    bool requestOperation(const QString &statusText);

    ResultImageProvider *m_provider = nullptr;
    ProcessingWorker *m_worker = nullptr;
    QThread m_thread;
    QString m_originalSource;
    QString m_resultSource;
    QString m_statusText;
    bool m_busy = false;
    bool m_hasImage = false;
    bool m_canUndo = false;
    int m_version = 0;
};

#endif // IMAGEPROCESSOR_H
