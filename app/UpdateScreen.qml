import QtQuick 2.15
import QtQuick.Controls 2.15
import "script.mjs" as Script
import QtQuick.Dialogs 1.3

Rectangle {
    id: rectangle
    width: 640
    height: 440
    color: "#c2c2c2"

    property alias buttonClose: buttonClose
    property alias buttonSave: buttonSave

    property int currentIndex
    property alias firstNameText: firstName.text
    property alias lastNameText: lastName.text
    property alias addressText: address.text
    property alias phoneText: phone.text
    property alias maritalStatusText: maritalStatus.text

    Text {
        id: text1
        text: "Редактировать"
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

    ListCountries {
        anchors.top: grid.bottom
        anchors.topMargin: 10
        anchors.bottom: row.top
        anchors.bottomMargin: 10
        width: 620
        x: 10
        y: 224
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
            text: "Сохранить"
            onClicked: {
                const cnts = countryModel.getCheckCounties();
                const emp = Script.getListEmp(firstName.text, lastName.text, address.text, phone.text, maritalStatus.text);
                const isSucces = meddiator.updateEmployee(currentIndex, emp, cnts);
                if (isSucces) {
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
        title: "Оошбка"
        text: "Операция не выполнена"
    }
}
