import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.1

Window {
    id: window
    width: 640
    height: 440
    visible: true
    title: qsTr("Qml-test")

    StackView {
        id: stack
        initialItem: mainScreen
        anchors.fill: parent
    }


    UpdateScreen {
        id: updateScreen
        buttonSave.onClicked: {
            stack.pop();
        }
        buttonClose.onClicked: {
            stack.pop();
        }
        visible: false
    }

    InsertScreen {
        id: insertScreen
        buttonSave.onClicked: {
            stack.pop();
        }
        buttonClose.onClicked: {
            stack.pop();
        }
        visible: false
    }

    MainScreen {
        id: mainScreen

        buttonInsert.onClicked:  {
            countryModel.setCheckCounties([]);
            stack.push( insertScreen )
        }

        Connections {
            target: mainScreen
            function onClickUpdate(index) {

                const empList = meddiator.getEmployee(index);
                updateScreen.currentIndex = index;
                updateScreen.firstNameText = empList[0];
                updateScreen.lastNameText = empList[1];
                updateScreen.addressText = empList[2];
                updateScreen.phoneText = empList[3];
                updateScreen.maritalStatusText = empList[4];

                stack.push( updateScreen );
            }
        }
    }

}
