import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: rectangle
    width: 640
    height: 440

    property int currentIndex: 0
    property alias buttonUpdate: buttonUpdate
    property alias buttonInsert: buttonInsert

    signal clickUpdate(int indexRow)
    property alias currentIndex: listView.currentIndex

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
                if (meddiator.deleteEmployee(currentIndex)) {
                    console.log("delete employee!!!");
                };
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
            console.log("Hello");
            const index = listView.currentIndex;
            if (!employeeModel.isValid(index)) return;
            const empList = meddiator.getEmployee(index);
            address.text = empList[2];
            phone.text = empList[3];
            maritalStatus.text = empList[4];
            const cntList = meddiator.getCountries(index);
            countryModel.setCheckCounties(cntList);
        }

        delegate: Item {
            x: 5
            width: 80
            height: 40
            Rectangle {
                width: parent.width
                height: parent.height
                color: listView.currentIndex === index ? "#D1C400" : "#D1C4E9";
                Text {
                    anchors.centerIn: parent
                    text: firstName + ' ' + lastName
                    anchors.verticalCenter: parent.verticalCenter
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

        onModelChanged: {
            console.log("update!!");
        }
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
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.leftMargin: 0
                title: "Улица:"
                text: ""
                readOnly: true
            }

            GroupText {
                id: phone
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.leftMargin: 0
                title: "Телефон:"
                text: ""
                readOnly: true
            }

            GroupText {
                id: maritalStatus
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.leftMargin: 0
                title: "Cемейное положение:"
                text: ""
                readOnly: true
            }
        }

        Column {
            id: column4
            width: 200
            height: 150
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            spacing: 10
            anchors.rightMargin: 10
            anchors.leftMargin: 10
            anchors.bottomMargin: 10

            Text {
                id: text4
                text: qsTr("Список посещенных стран:")
                anchors.left: parent.left
                anchors.right: parent.right
                font.pixelSize: 16
                anchors.rightMargin: 0
                anchors.leftMargin: 0
            }
            ListView {
                id: listView1
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: text4.bottom
                anchors.bottom: parent.bottom
                spacing: 5
                boundsBehavior: Flickable.StopAtBounds
                flickableDirection: Flickable.VerticalFlick
                interactive: true
                clip: true
                anchors.topMargin: 5
                anchors.rightMargin: 0
                anchors.leftMargin: 0
                anchors.bottomMargin: 0
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
                            enabled: false;
                            anchors.verticalCenter: parent.verticalCenter
                        }
                        spacing: 10
                    }
                }
                model: countryModel
            }

        }
    }
}
