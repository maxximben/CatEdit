#include <QtQuick>
#include <auroraapp.h>

#include <QQmlContext>

#include "imageprocessor.h"
#include "resultimageprovider.h"

int main(int argc, char *argv[])
{
    QScopedPointer<QGuiApplication> application(Aurora::Application::application(argc, argv));
    application->setOrganizationName(QStringLiteral("ru.template"));
    application->setApplicationName(QStringLiteral("CatEditAiProSixSevenSigmaEditor"));

    QScopedPointer<QQuickView> view(Aurora::Application::createView());
    ResultImageProvider *resultProvider = new ResultImageProvider;
    QScopedPointer<ImageProcessor> imageProcessor(new ImageProcessor(resultProvider));

    view->engine()->addImageProvider(QStringLiteral("result"), resultProvider);
    view->rootContext()->setContextProperty(QStringLiteral("imageProcessor"),
                                            imageProcessor.data());
    view->setSource(
        Aurora::Application::pathTo(QStringLiteral("qml/CatEditAiProSixSevenSigmaEditor.qml")));
    view->show();

    return application->exec();
}
