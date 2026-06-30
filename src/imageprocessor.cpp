#include "imageprocessor.h"

#include "processingworker.h"
#include "resultimageprovider.h"

#include <QImage>
#include <QMetaType>

ImageProcessor::ImageProcessor(ResultImageProvider *provider, QObject *parent)
    : QObject(parent), m_provider(provider), m_worker(new ProcessingWorker)
{
    qRegisterMetaType<QImage>("QImage");

    m_worker->moveToThread(&m_thread);

    connect(&m_thread, &QThread::finished, m_worker, &QObject::deleteLater);
    connect(this, &ImageProcessor::importRequested,
            m_worker, &ProcessingWorker::importImage);
    connect(this, &ImageProcessor::backgroundRequested,
            m_worker, &ProcessingWorker::removeBackground);
    connect(this, &ImageProcessor::enhanceRequested,
            m_worker, &ProcessingWorker::enhance);
    connect(this, &ImageProcessor::blackWhiteRequested,
            m_worker, &ProcessingWorker::blackWhite);
    connect(this, &ImageProcessor::sepiaRequested,
            m_worker, &ProcessingWorker::sepia);
    connect(this, &ImageProcessor::undoRequested,
            m_worker, &ProcessingWorker::undo);
    connect(this, &ImageProcessor::resetRequested,
            m_worker, &ProcessingWorker::reset);
    connect(this, &ImageProcessor::exportRequested,
            m_worker, &ProcessingWorker::exportResult);
    connect(m_worker, &ProcessingWorker::stateReady,
            this, &ImageProcessor::handleStateReady);

    m_thread.start();
    setStatusText(tr("Select an image"));
}

ImageProcessor::~ImageProcessor()
{
    m_thread.quit();
    m_thread.wait();
}

QString ImageProcessor::originalSource() const
{
    return m_originalSource;
}

QString ImageProcessor::resultSource() const
{
    return m_resultSource;
}

QString ImageProcessor::statusText() const
{
    return m_statusText;
}

bool ImageProcessor::busy() const
{
    return m_busy;
}

bool ImageProcessor::hasImage() const
{
    return m_hasImage;
}

bool ImageProcessor::canUndo() const
{
    return m_canUndo;
}

void ImageProcessor::process(const QString &filePath)
{
    if (filePath.isEmpty()) {
        setStatusText(tr("Select an image"));
        return;
    }

    if (!requestOperation(tr("Importing image...")))
        return;
    emit importRequested(filePath);
}

void ImageProcessor::removeBackground()
{
    if (!requestOperation(tr("Removing background...")))
        return;
    emit backgroundRequested();
}

void ImageProcessor::enhance()
{
    if (!requestOperation(tr("Enhancing image...")))
        return;
    emit enhanceRequested();
}

void ImageProcessor::blackWhite()
{
    if (!requestOperation(tr("Applying black and white style...")))
        return;
    emit blackWhiteRequested();
}

void ImageProcessor::sepia()
{
    if (!requestOperation(tr("Applying sepia style...")))
        return;
    emit sepiaRequested();
}

void ImageProcessor::undo()
{
    if (!requestOperation(tr("Undoing last action...")))
        return;
    emit undoRequested();
}

void ImageProcessor::reset()
{
    if (!requestOperation(tr("Resetting to original...")))
        return;
    emit resetRequested();
}

void ImageProcessor::exportResult()
{
    if (!requestOperation(tr("Exporting image...")))
        return;
    emit exportRequested();
}

void ImageProcessor::clear()
{
    if (m_provider)
        m_provider->clear();

    m_originalSource.clear();
    emit originalSourceChanged();
    m_resultSource.clear();
    emit resultSourceChanged();
    setStatusText(tr("Select an image"));
    setBusy(false);
    setHasImage(false);
    setCanUndo(false);
}

void ImageProcessor::handleStateReady(const QImage &original, const QImage &current, bool canUndo,
                                      const QString &statusText, const QString &errorText)
{
    setBusy(false);

    if (!original.isNull() && !current.isNull() && m_provider) {
        m_provider->setImage(QStringLiteral("original"), original);
        m_provider->setImage(QStringLiteral("current"), current);

        ++m_version;
        m_originalSource = QStringLiteral("image://result/original/%1").arg(m_version);
        emit originalSourceChanged();
        m_resultSource = QStringLiteral("image://result/current/%1").arg(m_version);
        emit resultSourceChanged();
        setHasImage(true);
    }

    setCanUndo(canUndo);
    setStatusText(errorText.isEmpty() ? statusText : errorText);
}

void ImageProcessor::setStatusText(const QString &statusText)
{
    if (m_statusText == statusText)
        return;

    m_statusText = statusText;
    emit statusTextChanged();
}

void ImageProcessor::setBusy(bool busy)
{
    if (m_busy == busy)
        return;

    m_busy = busy;
    emit busyChanged();
}

void ImageProcessor::setHasImage(bool hasImage)
{
    if (m_hasImage == hasImage)
        return;

    m_hasImage = hasImage;
    emit hasImageChanged();
}

void ImageProcessor::setCanUndo(bool canUndo)
{
    if (m_canUndo == canUndo)
        return;

    m_canUndo = canUndo;
    emit canUndoChanged();
}

bool ImageProcessor::requestOperation(const QString &statusText)
{
    if (m_busy)
        return false;

    setBusy(true);
    setStatusText(statusText);
    return true;
}
