import QtQuick 2.0
import QtQuick.Controls 2.15

Rectangle {
    id: rect

    property bool enabled: true
    border.color: "black"

    Column {
        id: column4
        anchors.fill: parent

        Text {
            id: text4
            text: qsTr("  Список посещенных стран:")
            font.pixelSize: 16
        }

        ListView {
            id: listView1
            width: rect.width
            height: rect.height - text4.height
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
                            countryModel.setCheck(index, checkBox.checked);
                        }
                        anchors.verticalCenter: parent.verticalCenter
                    }
                    spacing: 10
                }
            }
            model: countryModel
        }
    }
}