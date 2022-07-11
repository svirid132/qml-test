import QtQuick 2.15
import QtQuick.Controls 2.15
import "script.mjs" as Script
import QtQuick.Dialogs 1.1

Rectangle {
    id: rectangle
    width: 640
    height: 440
    color: "#c2c2c2"

    property alias buttonClose: buttonClose
    property alias buttonSave: buttonSave

    Text {
        id: text1
        text: "Добавить Сотрудника"
        anchors.left: parent.left
        anchors.top: parent.top
        font.pixelSize: 22
        anchors.leftMargin: 30
        anchors.topMargin: 10
    }

    Grid {
        id: grid
        height: 172
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: text1.bottom
        anchors.rightMargin: 10
        anchors.leftMargin: 10
        anchors.topMargin: 10
        verticalItemAlignment: Grid.AlignTop
        horizontalItemAlignment: Grid.AlignLeft
        spacing: 10
        rows: 3
        columns: 2

        GroupText {
            id: firstName
            title: "Имя"
        }

        GroupText {
            id: lastName
            title: "Фамилия"
        }

        GroupText {
            id: address
            title: "Адрес"
        }

        GroupText {
            id: phone
            title: "Телефон"
        }

        GroupText {
            id: maritalStatus
            title: "Семейное положение"
        }
    }

    Column {
        id: column
        x: 10
        y: 224
        width: 620
        height: 169
        spacing: 10

        Text {
            id: text2
            text: qsTr("Странны, в которых был")
            anchors.left: parent.left
            anchors.right: parent.right
            font.pixelSize: 16
            anchors.rightMargin: 0
            anchors.leftMargin: 0
        }
        ListView {
            id: listView
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: text2.bottom
            anchors.bottom: parent.bottom
            clip: true
            anchors.topMargin: 10
            boundsBehavior: Flickable.StopAtBounds
            anchors.bottomMargin: 0
            anchors.rightMargin: 0
            anchors.leftMargin: 0
            delegate: Item {
                x: 5
                width: 80
                height: 40
                Row {
                    id: row1
                    spacing: 10
                    Text {
                        text: model.name
                        anchors.verticalCenter: parent.verticalCenter
                    }

                    CheckBox {
                        id: checkBox
                        checked: model.isCheck
                        anchors.verticalCenter: parent.verticalCenter
                        onToggled: {
                            countryModel.setCheck(index, checkBox.checked);
                        }
                    }
                }
            }
            model: countryModel
        }
    }

    Row {
        id: row
        x: 351
        y: 399
        width: 289
        height: 41
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.rightMargin: 0
        anchors.bottomMargin: 5
        spacing: 20

        Button {
            id: buttonClose
            width: 115
            height: 41
            text: "Отмена"
        }
        Button {
            id: buttonSave
            width: 115
            height: 41
            text: "Сохранитьs"
            onClicked: {
                const listEmp = Script.getListEmp(firstName.text, lastName.text, address.text, phone.text, maritalStatus.text);
                const listCnts = countryModel.getCheckCounties();
                if (meddiator.saveEmployee(listEmp, listCnts)) {
                    dialogSuccess.open();
                } else {
                    dialogError.open();
                }
            }
        }
    }

    MessageDialog {
        id: dialogSuccess
        title: "Успешно"
        text: "Операция прошла успешно"
    }

    MessageDialog {
        id: dialogError
        title: "Ошибка"
        text: "Операция не выполнена"
    }
}
