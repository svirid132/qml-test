import QtQuick 2.0
import QtQuick.Controls 2.12

Rectangle {

    id: root
    property alias title: textEl.text
    property string textText
    property alias text: textEdit.text
    property alias readOnly: textEdit.readOnly
    width: 200
    height: 51
    color: "transparent"

    Column {
        id: column
        spacing: 5

        Text {
            id: textEl
            font.pixelSize: 16
            horizontalAlignment: Text.AlignLeft
            maximumLineCount: 1
        }

        TextField {
            id: textEdit
            height: root.height - textEl.height
            font.pixelSize: 16
            selectByMouse: true
            width: 200
            background: Rectangle {
                implicitHeight: 20
                radius: 10
            }
        }
    }
}
