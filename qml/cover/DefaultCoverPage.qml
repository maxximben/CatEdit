import QtQuick 2.0
import Sailfish.Silica 1.0

CoverBackground {
    objectName: "defaultCover"

    CoverTemplate {
        objectName: "applicationCover"
        primaryText: "App"
        secondaryText: qsTr("CatEdit Ai Pro Six Seven Sigma Editor")
        icon {
            source: Qt.resolvedUrl("../icons/CatEditAiProSixSevenSigmaEditor.svg")
            sourceSize { width: icon.width; height: icon.height }
        }
    }
}
