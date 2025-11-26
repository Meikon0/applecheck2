import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

RowLayout {
    id: bar
    signal trainClicked()
    Layout.fillWidth: true
    spacing: 12

    Button {
        text: qsTr("Справка")
        icon.name: "help"
        Layout.fillWidth: true
        onClicked: dialog.open()
    }

    Button {
        text: qsTr("Дообучение")
        icon.name: "brain"
        Layout.fillWidth: true
        onClicked: trainClicked()
    }

    Dialog {
        id: dialog
        title: qsTr("Подсказки")
        standardButtons: Dialog.Ok
        modal: true

        contentItem: ColumnLayout {
            padding: 16
            spacing: 8
            Label { text: qsTr("• Снимайте яблоко крупным планом, без бликов.") }
            Label { text: qsTr("• Поддерживается офлайн-дообучение модели.") }
            Label { text: qsTr("• Результаты: хорошее / плохое яблоко или не яблоко.") }
        }
    }
}
