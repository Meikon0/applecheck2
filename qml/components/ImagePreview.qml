import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: preview
    property alias source: image.source
    color: "#20252b"
    radius: 12
    border.color: "#3a3f45"
    border.width: 1
    implicitHeight: 320

    Image {
        id: image
        anchors.fill: parent
        fillMode: Image.PreserveAspectFit
        smooth: true
    }

    Label {
        anchors.centerIn: parent
        text: image.source === "" ? qsTr("Нет изображения") : ""
        color: "#8fa1b3"
    }
}
