import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtMultimedia 5.15

ApplicationWindow {
    id: root
    width: 720
    height: 1280
    visible: true
    title: qsTr("AppleCheck")
    Material.theme: Material.Dark

    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: homePage
    }

    Component {
        id: homePage
        HomePage {
            controller: appController
            onOpenTraining: stackView.push(trainingPage)
            onShowResult: resultDialog.openWithResult(resultText, confidence)
        }
    }

    Component {
        id: trainingPage
        TrainingPage {
            controller: appController
            onBack: stackView.pop()
        }
    }

    ResultDialog {
        id: resultDialog
    }
}
