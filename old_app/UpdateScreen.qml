import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Dialogs 1.3
import Elems 1.0

Rectangle {
    id: root
    width: parent.width
    height: parent.height
    color: "#c2c2c2"

    signal clickedUpdate(bool success)

    property alias buttonClose: buttonClose

    property MEmployee memployee
    property int currentIndex

    function updateEmp() {
        firstName.text = memployee.firstName;
        lastName.text = memployee.lastName;
        address.text = memployee.address;
        phone.text = memployee.phone;
        maritalStatus.text = memployee.maritalStatus;
        const codes = memployee.countryCodes;
        countryModel.setCheckCounties(codes);
    }

    Text {
        id: title
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
        anchors.top: title.bottom
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
            text: memployee.firstName
            title: "Имя"
        }

        GroupText {
            id: lastName
            text: memployee.lastName
            title: "Фамилия"
        }

        GroupText {
            id: address
            text: memployee.address
            title: "Адрес"
        }

        GroupText {
            id: phone
            text: memployee.phone
            title: "Телефон"
        }

        GroupText {
            id: maritalStatus
            text: memployee.maritalStatus
            title: "Семейное положение"
        }
    }

    ListCountries {
        anchors.top: grid.bottom
        anchors.topMargin: 15
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
        anchors.bottomMargin: 10
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

                memployee.firstName = firstName.text;
                memployee.lastName = lastName.text;
                memployee.address = address.text;
                memployee.phone = phone.text;
                memployee.maritalStatus = maritalStatus.text;
                const cnts = countryModel.getCheckCounties();
                memployee.countryCodes = cnts;

                const isSucces = meddiator.updateEmployee(currentIndex, memployee);
                if (isSucces) {
                    clickedUpdate(true);
                    dialogSuccess.open();
                } else {
                    clickedUpdate(false);
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
