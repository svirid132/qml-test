import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Dialogs 1.3
import Singelton 1.0 as S
import View 1.0
import Model 1.0
import Controllers 1.0
import Qt.labs.platform 1.1

Rectangle {
    id: root
    color: "#c2c2c2"

    property var onClose: function() {

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
            text: S.Employee.firstName
            title: "Имя"
        }

        GroupText {
            id: lastName
            text: S.Employee.lastName
            title: "Фамилия"
        }

        GroupText {
            id: address
            text: S.Employee.additionalEmp.address
            title: "Адрес"
        }

        GroupText {
            id: phone
            text: S.Employee.additionalEmp.phone
            title: "Телефон"
        }

        GroupText {
            id: maritalStatus
            text: S.Employee.additionalEmp.maritalStatus
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
        model: countryModel
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
            onClicked: {
                onClose()
            }
        }
        Button {
            id: buttonSave
            width: 115
            height: 41
            text: "Сохранить"
            onClicked: {
                putEmpController.put();
            }
        }
    }


    MessageDialog {
        id: dialogSuccess
        title: "Успешно"
        text: "Операция прошла успешно"
        onVisibleChanged: function() {
            if (!visible) {
                onClose()
            }
        }
    }

    MessageDialog {
        id: dialogError
        title: "Ошибка"
        text: "Операция не выполнена"
    }

    PutEmployeeController {
        id: putEmpController
        targetEmp: emp
        targetCntrModel: countryModel
        onAccess: function() {
            dialogSuccess.open()
        }
        onError: function() {
            dialogSuccess.open()
        }
    }

    Employee {
        id: emp
        mId: S.Employee.mId
        firstName: firstName.text
        lastName: lastName.text
        additionalEmp {
            mId: S.Employee.additionalEmp.mId
            phone: phone.text
            maritalStatus: maritalStatus.text
            address: address.text
        }
    }

    CountryModel {
        id: countryModel
        codeCountriesChecked: S.Employee.additionalEmp.countryCodes
    }
}
