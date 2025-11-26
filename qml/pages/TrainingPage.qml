import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Page {
    id: training
    property var controller
    signal back()

    title: qsTr("Дообучение офлайн")

    ColumnLayout {
        anchors.fill: parent
        spacing: 12
        padding: 16

        Label {
            text: qsTr("Добавьте примеры для локального дообучения. Файлы сохраняются в sandbox приложения.")
            wrapMode: Text.WordWrap
            Layout.fillWidth: true
        }

        Button {
            text: qsTr("Добавить метку 'Хорошее яблоко'")
            Layout.fillWidth: true
            onClicked: controller && controller.enqueueSample("good")
        }
        Button {
            text: qsTr("Добавить метку 'Плохое яблоко'")
            Layout.fillWidth: true
            onClicked: controller && controller.enqueueSample("bad")
        }
        Button {
            text: qsTr("Добавить метку 'Не яблоко'")
            Layout.fillWidth: true
            onClicked: controller && controller.enqueueSample("not_apple")
        }

        ProgressBar {
            Layout.fillWidth: true
            from: 0
            to: 1
            value: controller ? controller.trainingProgress : 0
        }

        Button {
            text: qsTr("Старт дообучения")
            enabled: controller && controller.canTrain
            Layout.fillWidth: true
            onClicked: controller && controller.startTraining()
        }

        Button {
            text: qsTr("Назад")
            Layout.alignment: Qt.AlignHCenter
            onClicked: back()
        }
    }
}
