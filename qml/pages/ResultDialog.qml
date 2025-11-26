import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Dialog {
    id: dialog
    modal: true
    title: qsTr("Результат")
    standardButtons: Dialog.Ok

    property string label: ""
    property double confidence: 0

    function openWithResult(text, conf) {
        label = text;
        confidence = conf;
        dialog.open();
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 12
        padding: 16

        Label {
            text: label
            font.pixelSize: 20
            wrapMode: Text.WordWrap
        }
        Label {
            text: qsTr("Уверенность: ") + Math.round(confidence * 100) + "%"
        }
    }
}
