import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtMultimedia

ApplicationWindow {
    id: app
    width: 480
    height: 720
    visible: true
    title: qsTr("AppleCheck")

    property string selectedImage: ""

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 16
        spacing: 12

        Label {
            text: qsTr("AppleCheck - проверка качества яблок")
            font.pixelSize: 20
            Layout.alignment: Qt.AlignHCenter
        }

        Rectangle {
            id: previewFrame
            Layout.fillWidth: true
            Layout.preferredHeight: 260
            radius: 12
            color: "#f2f2f2"
            border.color: "#cccccc"
            clip: true

            Image {
                id: preview
                anchors.centerIn: parent
                width: parent.width
                height: parent.height
                fillMode: Image.PreserveAspectFit
                source: selectedImage
                sourceSize.width: parent.width
                sourceSize.height: parent.height
            }

            Label {
                anchors.centerIn: parent
                text: selectedImage === "" ? qsTr("Выберите изображение или сделайте снимок") : ""
                color: "#666"
            }
        }

        RowLayout {
            Layout.fillWidth: true
            spacing: 8

            Button {
                text: qsTr("Выбрать из галереи")
                enabled: !uiController.busy
                onClicked: fileDialog.open()
            }

            Button {
                text: uiController.busy ? qsTr("Обработка...") : qsTr("Классифицировать")
                enabled: selectedImage !== "" && !uiController.busy
                onClicked: uiController.classifyImage(preview.source)
            }
        }

        RowLayout {
            Layout.fillWidth: true
            spacing: 8

            Button {
                text: qsTr("Очистить")
                enabled: !uiController.busy
                onClicked: {
                    selectedImage = ""
                    uiController.reset()
                }
            }

            Button {
                text: qsTr("Дообучить")
                enabled: !uiController.busy
                onClicked: trainingDialog.open()
            }
        }

        GroupBox {
            title: qsTr("Результат")
            Layout.fillWidth: true
            ColumnLayout {
                anchors.fill: parent
                spacing: 6

                Label {
                    text: uiController.verdict
                    font.pixelSize: 18
                }

                ProgressBar {
                    from: 0
                    to: 1
                    value: uiController.confidence
                }

                Label {
                    text: selectedImage === "" ? "" : uiController.lastImagePath
                    color: "#666"
                    wrapMode: Label.Wrap
                }
            }
        }

        Frame {
            Layout.fillWidth: true
            Layout.fillHeight: true
            ColumnLayout {
                anchors.fill: parent
                spacing: 8

                Label {
                    text: qsTr("Шаги использования")
                    font.bold: true
                }

                Text {
                    text: qsTr("1. Выберите фото яблока или сделайте снимок камеры.\n2. Нажмите 'Классифицировать'.\n3. При необходимости запустите дообучение на своей подборке.")
                    wrapMode: Text.Wrap
                }
            }
        }
    }

    FileDialog {
        id: fileDialog
        title: qsTr("Выберите изображение яблока")
        nameFilters: [qsTr("Изображения (*.png *.jpg *.jpeg)")]
        onAccepted: {
            selectedImage = selectedFile
            uiController.classifyImage(selectedFile)
        }
    }

    FileDialog {
        id: trainingDialog
        title: qsTr("Папка с данными для дообучения")
        selectFolder: true
        onAccepted: uiController.trainOnDataset(selectedFile)
    }

    Connections {
        target: uiController
        function onShowToast(message) {
            toast.text = message
            toast.visible = true
            toast.opacity = 0.9
            toastTimer.restart()
        }
    }

    Rectangle {
        id: toast
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 24
        radius: 8
        color: "#333"
        opacity: 0.0
        visible: false

        Behavior on opacity { NumberAnimation { duration: 250 } }

        Text {
            id: toastText
            text: toast.text
            color: "white"
            padding: 12
        }
    }

    property string toastTextValue: ""

    Timer {
        id: toastTimer
        interval: 2000
        repeat: false
        onTriggered: {
            toast.opacity = 0.0
            toast.visible = false
        }
    }
}
