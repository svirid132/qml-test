import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Dialogs 1.3

Rectangle {
    id: rectangle
    width: 640
    height: 440

    property int currentIndex: 0
    property alias buttonUpdate: buttonUpdate
    property alias buttonInsert: buttonInsert

    signal clickUpdate(int indexRow)
    property alias empIndex: listView.currentIndex

    Row {
        id: row
        x: 273
        y: 377
        width: 334
        height: 60
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 3
        spacing: 9

        Button {
            id: button
            text: qsTr("Удалить")
            onClicked: {
                const currentIndex = listView.currentIndex;
                if (!employeeModel.isValid(currentIndex)) return;
                if (meddiator.deleteEmployee(currentIndex)) {
                    dialogSuccess.open();
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
                rectangle.clickUpdate(index);
            }
        }

        Button {
            id: buttonInsert
            text: "Добваить"
        }
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
        onCurrentItemChanged: {
            const index = listView.currentIndex;
            if (employeeModel === null) return;
            if (!employeeModel.isValid(index)) {
                address.text = "";
                phone.text = "";
                maritalStatus.text = "";
                countryModel.setCheckCounties([]);
                return;
            }
            const empList = meddiator.getEmployee(index);
            address.text = empList[2];
            phone.text = empList[3];
            maritalStatus.text = empList[4];
            const cntList = meddiator.getCountries(index);
            countryModel.setCheckCounties(cntList);
        }

        delegate: Item {
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
        model: employeeModel
    }

    Rectangle {
        id: rectangle1
        x: 219
        width: 405
        height: 350
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.rightMargin: 10
        anchors.topMargin: 10

        Column {
            id: column3
            height: 173
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.topMargin: 5
            anchors.rightMargin: 5
            anchors.leftMargin: 5
            spacing: 10

            GroupText {
                id: address
                title: "Улица:"
                text: ""
                readOnly: true
            }

            GroupText {
                id: phone
                title: "Телефон:"
                text: ""
                readOnly: true
            }

            GroupText {
                id: maritalStatus
                title: "Cемейное положение:"
                text: ""
                readOnly: true
            }
        }

        ListCountries {
            width: 200
            height: 160
            enabled: false
            anchors.rightMargin: 10
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
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
