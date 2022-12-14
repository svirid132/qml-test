import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Dialogs 1.3
import Model 1.0
import View 1.0
import Controllers 1.0

Rectangle {
    id: root
    width: parent.width
    height: parent.height

    signal clickUpdate(int indexRow)

    property alias buttonUpdate: buttonUpdate
    property alias buttonInsert: buttonInsert
    readonly property var update: function() {

    }

    ListView {
        id: listView
        width: 200
        height: 350
        anchors.left: parent.left
        anchors.top: parent.top
        boundsBehavior: Flickable.StopAtBounds
        spacing: 10
        anchors.leftMargin: 10
        anchors.topMargin: 10
        currentIndex: -1

        delegate: Item {
            id: item
            property int emp_id: id
            property string emp_firstName: firstName
            property string emp_lastName: lastName
            property int additional_id: idAdditional
            x: 5
            width: listView.width
            height: 40
            Rectangle {
                width: parent.width
                height: parent.height
                color: listView.currentIndex === index ? "#D1C400" : "#D1C4E9";
                Text {
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    anchors.fill: parent
                    text: firstName + ' ' + lastName
                    font.bold: true
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        listView.currentIndex = index;
                    }
                }
            }
        }
        onCurrentItemChanged: {
            emp.id = currentItem.emp_id
            emp.firstName = currentItem.emp_firstName
            emp.lastName = currentItem.emp_lastName
            getAddEmpController.additionalId = currentItem.additional_id
            getAddEmpController.exec()
        }

        model: empModel
    }

    Rectangle {
        id: additional
        x: 219
        width: 400
        anchors.right: root.right
        anchors.top: root.top
        anchors.bottom: row.top
        anchors.rightMargin: 10
        anchors.topMargin: 5
        anchors.leftMargin: 5

        Column {
            id: column
            height: 173
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            spacing: 10

            GroupText {
                id: address
                title: "Улица:"
                text: addEmp.address
                readOnly: true
            }

            GroupText {
                id: phone
                title: "Телефон:"
                text: addEmp.phone
                readOnly: true
            }

            GroupText {
                id: maritalStatus
                title: "Cемейное положение:"
                text: addEmp.maritalStatus
                readOnly: true
            }
        }

        ListCountries {
            width: additional.width
            height: additional.height - column.height - 20
            enabled: false
            anchors.top: column.bottom
            anchors.topMargin: 5
            model: countryModel
        }
    }

    Row {
        id: row
        x: 273
        width: 334
        anchors.bottom: root.bottom
        anchors.bottomMargin: 10
        spacing: 9

        Button {
            id: buttonDelete
            text: qsTr("Удалить")
            onClicked: {
                const currentIndex = listView.currentIndex;
                if (!employeeModel.isValid(currentIndex)) return;
                if (meddiator.deleteEmployee(currentIndex)) {
                    dialogSuccess.open();
                    listView.currentIndex = currentIndex - 1;
                    updateView();
                } else {
                    dialogError.open();
                }
            }
        }

        Button {
            id: buttonUpdate
            text: qsTr("Редактировать")
            onClicked: {
                const index = listView.currentIndex;
                if (!employeeModel.isValid(index)) return;
                root.clickUpdate(index);
            }
        }

        Button {
            id: buttonInsert
            text: "Добваить"
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

    Employee {
        id: emp
        additionalEmp: AdditionalEmp {
            id: addEmp
        }
    }

    EmpModel {
        id: empModel
    }

    CountryModel {
        id: countryModel
        codeCountriesChecked: addEmp.countryCodes
    }

    GetAdditionalEmpController {
        id: getAddEmpController
        target: addEmp
    }
}
