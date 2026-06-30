import QtQuick 2.0
import Sailfish.Silica 1.0
import Sailfish.Pickers 1.0

Page {
    id: page
    objectName: "mainPage"
    allowedOrientations: Orientation.All

    property string selectedPath
    property string selectedFileName

    function processSelectedContent(properties) {
        selectedPath = properties.filePath || ""
        selectedFileName = properties.fileName || ""
        imageProcessor.process(selectedPath)
    }

    SilicaFlickable {
        objectName: "flickable"
        anchors.fill: parent
        contentHeight: layout.height + Theme.paddingLarge

        Column {
            id: layout
            objectName: "layout"
            width: parent.width
            spacing: Theme.paddingMedium

            PageHeader {
                objectName: "pageHeader"
                title: qsTr("CatEdit Ai Pro Six Seven Sigma Editor")
                extraContent.children: [
                    IconButton {
                        objectName: "aboutButton"
                        icon.source: "image://theme/icon-m-about"
                        anchors.verticalCenter: parent.verticalCenter

                        onClicked: pageStack.push(Qt.resolvedUrl("AboutPage.qml"))
                    }
                ]
            }

            Button {
                objectName: "openFileButton"
                anchors.horizontalCenter: parent.horizontalCenter
                enabled: !imageProcessor.busy
                text: qsTr("Choose from files")
                onClicked: pageStack.push(filePickerComponent)
            }

            BusyIndicator {
                objectName: "processingIndicator"
                anchors.horizontalCenter: parent.horizontalCenter
                running: imageProcessor.busy
                visible: imageProcessor.busy
            }

            Label {
                objectName: "statusLabel"
                anchors {
                    left: parent.left
                    right: parent.right
                    margins: Theme.horizontalPageMargin
                }
                color: palette.highlightColor
                font.pixelSize: Theme.fontSizeSmall
                horizontalAlignment: Text.AlignHCenter
                wrapMode: Text.WordWrap
                text: imageProcessor.statusText
            }

            SectionHeader {
                text: qsTr("Original")
            }

            Rectangle {
                objectName: "originalFrame"
                anchors.horizontalCenter: parent.horizontalCenter
                width: parent.width - 2 * Theme.horizontalPageMargin
                height: width * 0.62
                color: "transparent"
                border.color: Theme.rgba(palette.secondaryColor, 0.35)
                border.width: 1

                Image {
                    objectName: "originalImage"
                    anchors.fill: parent
                    anchors.margins: Theme.paddingMedium
                    source: imageProcessor.originalSource
                    fillMode: Image.PreserveAspectFit
                    cache: false
                    visible: imageProcessor.originalSource.length > 0
                }

                Label {
                    anchors.centerIn: parent
                    width: parent.width - 2 * Theme.paddingLarge
                    color: palette.secondaryColor
                    horizontalAlignment: Text.AlignHCenter
                    wrapMode: Text.WordWrap
                    text: qsTr("No original image")
                    visible: imageProcessor.originalSource.length === 0
                }
            }

            SectionHeader {
                text: qsTr("Working copy")
            }

            Rectangle {
                objectName: "resultFrame"
                anchors.horizontalCenter: parent.horizontalCenter
                width: parent.width - 2 * Theme.horizontalPageMargin
                height: width * 0.62
                color: "transparent"
                border.color: Theme.rgba(palette.secondaryColor, 0.35)
                border.width: 1

                Image {
                    objectName: "resultImage"
                    anchors.fill: parent
                    anchors.margins: Theme.paddingMedium
                    source: imageProcessor.resultSource
                    fillMode: Image.PreserveAspectFit
                    cache: false
                    visible: imageProcessor.resultSource.length > 0
                }

                Label {
                    objectName: "emptyStateLabel"
                    anchors.centerIn: parent
                    width: parent.width - 2 * Theme.paddingLarge
                    color: palette.secondaryColor
                    horizontalAlignment: Text.AlignHCenter
                    wrapMode: Text.WordWrap
                    text: qsTr("No processed image")
                    visible: imageProcessor.resultSource.length === 0
                }
            }

            SectionHeader {
                text: qsTr("Background")
            }

            Button {
                objectName: "removeBackgroundButton"
                anchors.horizontalCenter: parent.horizontalCenter
                enabled: imageProcessor.hasImage && !imageProcessor.busy
                text: qsTr("Remove background")
                onClicked: imageProcessor.removeBackground()
            }

            SectionHeader {
                text: qsTr("Enhancement")
            }

            Button {
                objectName: "enhanceButton"
                anchors.horizontalCenter: parent.horizontalCenter
                enabled: imageProcessor.hasImage && !imageProcessor.busy
                text: qsTr("Auto correct")
                onClicked: imageProcessor.enhance()
            }

            SectionHeader {
                text: qsTr("Style")
            }

            Column {
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: Theme.paddingMedium

                Button {
                    objectName: "blackWhiteButton"
                    enabled: imageProcessor.hasImage && !imageProcessor.busy
                    text: qsTr("B/W")
                    onClicked: imageProcessor.blackWhite()
                }

                Button {
                    objectName: "sepiaButton"
                    enabled: imageProcessor.hasImage && !imageProcessor.busy
                    text: qsTr("Sepia")
                    onClicked: imageProcessor.sepia()
                }
            }

            SectionHeader {
                text: qsTr("Pipeline")
            }

            Column {
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: Theme.paddingMedium

                Button {
                    objectName: "undoButton"
                    enabled: imageProcessor.canUndo && !imageProcessor.busy
                    text: qsTr("Undo")
                    onClicked: imageProcessor.undo()
                }

                Button {
                    objectName: "resetButton"
                    enabled: imageProcessor.hasImage && !imageProcessor.busy
                    text: qsTr("Reset")
                    onClicked: imageProcessor.reset()
                }
            }

            Button {
                objectName: "exportButton"
                anchors.horizontalCenter: parent.horizontalCenter
                enabled: imageProcessor.hasImage && !imageProcessor.busy
                text: qsTr("Export to gallery")
                onClicked: imageProcessor.exportResult()
            }

            Label {
                objectName: "selectedFileLabel"
                anchors {
                    left: parent.left
                    right: parent.right
                    margins: Theme.horizontalPageMargin
                }
                color: palette.secondaryColor
                font.pixelSize: Theme.fontSizeExtraSmall
                horizontalAlignment: Text.AlignHCenter
                wrapMode: Text.WrapAnywhere
                text: page.selectedFileName.length > 0 ? page.selectedFileName : page.selectedPath
                visible: page.selectedPath.length > 0
            }
        }
    }

    Component {
        id: filePickerComponent

        FilePickerPage {
            nameFilters: ["*.jpg", "*.jpeg", "*.png", "*.bmp", "*.gif", "*.webp"]
            onSelectedContentPropertiesChanged: page.processSelectedContent(selectedContentProperties)
        }
    }
}
