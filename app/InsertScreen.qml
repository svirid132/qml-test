import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Dialogs 1.3
import Elems 1.0

Rectangle {
    id: root
    width: parent.width
    height: parent.height
    color: "#c2c2c2"

    signal clickedSave(bool success)

    property alias buttonClose: buttonClose

    function clearData() {
        firstName.text = "";
        lastName.text = "";
        address.text = "";
        phone.text = "";
        maritalStatus.text = "";
        const codes = [];
        countryModel.setCheckCounties(codes);
    }

    MEmployee {
        id: memployee
    }

    Text {
        id: title
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
            text: "Сохранитьs"
            onClicked: {

                memployee.firstName = firstName.text;
                memployee.lastName = lastName.text;
                memployee.address = address.text;
                memployee.phone = phone.text;
                memployee.maritalStatus = maritalStatus.text;
                const cnts = countryModel.getCheckCounties();
                memployee.countryCodes = cnts;

                if (meddiator.saveEmployee(memployee)) {
                    clickedSave(true);
                    dialogSuccess.open();
                } else {
                    clickedSave(false);
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
