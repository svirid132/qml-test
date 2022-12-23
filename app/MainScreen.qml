import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Dialogs 1.3
import Model 1.0
import Controller 1.0
import Slice 1.0

Rectangle {
    id: root

    readonly property var update: function() {
        empTable.update()
    }
    readonly property var decrementCurrentIndex: function() {
        listView.decrementCurrentIndex()
    }

    property var onClickEdit: function() {

    }
    property var onClickInsert: function() {

    }

    QtObject {
        id: _root
        property Employee emp: SliceMainScreen.employee
        property AdditionalEmp addEmp: emp.additionalEmp
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
            property var empObj: ({
                                      emp_id: id,
                                      emp_firstName: firstName,
                                      emp_lastName: lastName,
                                      additional_id: idAdditional
                                  })
            x: 5
            width: listView.width
            height: 40
            Rectangle {
                width: parent.width
                height: parent.height
                color: listView.currentIndex === index ? "#03a9f4" : "#D1C4E9"
                Text {
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    anchors.fill: parent
                    text: firstName + ' ' + lastName
                    font.bold: true
                    color: listView.currentIndex === index ? "#fff" : "#000";
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
            if (!currentItem) {
                return
            }
            SliceMainScreen.setEmployee(currentItem.empObj)
            SliceMainScreen.getAdditionalEmployee()
        }

        model: empTable
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
                text: _root.addEmp.address
                readOnly: true
            }

            GroupText {
                id: phone
                title: "Телефон:"
                text: _root.addEmp.phone
                readOnly: true
            }

            GroupText {
                id: maritalStatus
                title: "Cемейное положение:"
                text: _root.addEmp.maritalStatus
                readOnly: true
            }
        }

        ListCountries {
            width: additional.width
            height: additional.height - column.height - 20
            enabled: false
            anchors.top: column.bottom
            anchors.topMargin: 5
            model: countryTable
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
                deleteEmployeeController.del()
            }
        }

        Button {
            id: editButton
            text: qsTr("Редактировать")
            onClicked: {
                if (listView.currentIndex === -1) {
                    return
                }

                onClickEdit()
            }
        }

        Button {
            id: buttonInsert
            text: "Добваить"
            onClicked: {
                onClickInsert()
            }
        }
    }

    MessageDialog {
        id: successDialog
        title: "Успешно"
        text: "Операция прошла успешно"
    }

    MessageDialog {
        id: errorDialog
        title: "Ошибка"
        text: "Операция не выполнена"
    }

    EmployeTable {
        id: empTable
    }

    CountryTable {
        id: countryTable
        codeCountriesChecked: _root.addEmp.countryCodes
    }
}
