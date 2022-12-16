import QtQuick 2.0
import QtQuick.Controls 2.15

Rectangle {
    id: rect

    property alias model: listView.model
    property bool enabled: true
    border.color: "black"

    Column {
        id: column
        anchors.fill: parent

        Text {
            id: title
            text: qsTr("  Список посещенных стран:")
            font.pixelSize: 16
        }

        ListView {
            id: listView
            width: rect.width
            height: rect.height - title.height
            spacing: 5
            boundsBehavior: Flickable.StopAtBounds
            flickableDirection: Flickable.VerticalFlick
            interactive: true
            clip: true
            delegate: Item {
                x: 5
                width: 80
                height: 40
                Row {
                    id: row2

                    Text {
                        text: model.name
                        anchors.verticalCenter: parent.verticalCenter
                        font.bold: true
                    }

                    CheckBox {
                        id: checkBox
                        checked: model.isCheck
                        enabled: rect.enabled
                        onToggled: {
                            listView.model.setCheck(index, checkBox.checked);
                        }
                        anchors.verticalCenter: parent.verticalCenter
                    }
                    spacing: 10
                }
            }
        }
    }
}
