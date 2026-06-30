TARGET = ru.template.CatEditAiProSixSevenSigmaEditor

CONFIG += \
    auroraapp

PKGCONFIG += \

OPENCV_BUILD_NAME = $$basename(OUT_PWD)
OPENCV_BUILD_PATH = $$PWD/third_party/opencv/build/$$OPENCV_BUILD_NAME/opencv
OPENCV_SOURCE_PATH = $$PWD/third_party/opencv/source

!exists($$OPENCV_BUILD_PATH/lib) {
    warning("Local OpenCV libraries were not found for this kit/configuration.")
}

opencv_library_install.path = /usr/share/ru.template.CatEditAiProSixSevenSigmaEditor/lib/
opencv_library_install.files = \
    $$OPENCV_BUILD_PATH/lib/libopencv_core.so.407 \
    $$OPENCV_BUILD_PATH/lib/libopencv_imgproc.so.407
opencv_library_install.CONFIG = no_check_exist
INSTALLS += opencv_library_install

INCLUDEPATH += \
    $$OPENCV_BUILD_PATH/include \
    $$OPENCV_BUILD_PATH \
    $$OPENCV_SOURCE_PATH/modules/core/include \
    $$OPENCV_SOURCE_PATH/modules/imgproc/include \
    $$OPENCV_SOURCE_PATH/include

LIBS += \
    $$OPENCV_BUILD_PATH/lib/libopencv_core.so.407 \
    $$OPENCV_BUILD_PATH/lib/libopencv_imgproc.so.407

SOURCES += \
    src/imageprocessor.cpp \
    src/main.cpp \
    src/processingworker.cpp \
    src/resultimageprovider.cpp

HEADERS += \
    src/imageprocessor.h \
    src/processingworker.h \
    src/resultimageprovider.h

DISTFILES += \
    rpm/ru.template.CatEditAiProSixSevenSigmaEditor.spec

AURORAAPP_ICONS = 86x86 108x108 128x128 172x172

CONFIG += auroraapp_i18n

TRANSLATIONS += \
    translations/ru.template.CatEditAiProSixSevenSigmaEditor.ts \
    translations/ru.template.CatEditAiProSixSevenSigmaEditor-ru.ts \
