import QtQuick 2.0
import QtQuick.Controls 2.12

Column {
    id: column
    width: 200
    height: 51
    spacing: 5
    property alias title: text.text
    property string textText
    property alias text: textEdit.text
    property alias readOnly: textEdit.readOnly

    Text {
        id: text
        anchors.left: parent.left
        anchors.right: parent.right
        font.pixelSize: 16
        horizontalAlignment: Text.AlignLeft
        anchors.rightMargin: 5
        anchors.leftMargin: 5
        maximumLineCount: 1
        minimumPixelSize: 16
        minimumPointSize: 16
    }

    TextField {
        id: textEdit
        anchors.left: parent.left
        anchors.right: parent.right
        font.pixelSize: 16
        anchors.rightMargin: 5
        anchors.leftMargin: 5
        selectByMouse: true

        background: Rectangle {
            implicitHeight: 20
        }
    }

}
