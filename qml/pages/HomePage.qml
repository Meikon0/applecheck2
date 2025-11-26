import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtMultimedia 5.15
import "/qml/components"

Page {
    id: home
    property var controller
    signal openTraining()
    signal showResult(string resultText, double confidence)

    title: qsTr("Классификация")

    ColumnLayout {
        anchors.fill: parent
        spacing: 16
        padding: 16

        Label {
            text: qsTr("Загрузите фото или сделайте снимок яблока")
            wrapMode: Text.WordWrap
            font.pixelSize: 20
            Layout.fillWidth: true
        }

        ImagePreview {
            id: preview
            Layout.fillWidth: true
            Layout.fillHeight: true
            source: controller ? controller.currentImage : ""
        }

        RowLayout {
            Layout.fillWidth: true
            spacing: 12

            Button {
                text: qsTr("Галерея")
                icon.name: "folder"
                Layout.fillWidth: true
                onClicked: controller && controller.pickFromGallery()
            }
            Button {
                text: qsTr("Камера")
                icon.name: "camera"
                Layout.fillWidth: true
                onClicked: controller && controller.captureFromCamera()
            }
        }

        Button {
            text: qsTr("Анализировать")
            Layout.fillWidth: true
            enabled: controller && controller.hasImage
            onClicked: {
                if (controller) {
                    const result = controller.runInference();
                    showResult(result.label, result.confidence);
                }
            }
        }

        BottomBar {
            onTrainClicked: openTraining()
        }
    }
}
