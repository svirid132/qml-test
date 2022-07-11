import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Dialogs 1.3

Window {
    id: window
    width: 640
    height: 440
    visible: true
    title: qsTr("Qml-test")

    maximumHeight: height
    maximumWidth: width

    minimumHeight: height
    minimumWidth: width

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
            const currentIndex = mainScreen.empIndex;
            if (!employeeModel.isValid(currentIndex)) {
                countryModel.setCheckCounties([]);
                stack.pop();
                return;
            }
            const cntList = meddiator.getCountries(currentIndex);
            countryModel.setCheckCounties(cntList);

            stack.pop();
        }
        visible: false
    }

    InsertScreen {
        id: insertScreen
        buttonSave.onClicked: {
            const currentIndex = mainScreen.empIndex;
            if (!employeeModel.isValid(currentIndex)) {
                countryModel.setCheckCounties([]);
                stack.pop();
                return;
            }
            const cntList = meddiator.getCountries(currentIndex);
            countryModel.setCheckCounties(cntList);

            stack.pop();
        }
        buttonClose.onClicked: {
            const currentIndex = mainScreen.empIndex;
            if (!employeeModel.isValid(currentIndex)) {
                countryModel.setCheckCounties([]);
                stack.pop();
                return;
            }
            const cntList = meddiator.getCountries(currentIndex);
            countryModel.setCheckCounties(cntList);

            stack.pop();
        }
        visible: false
    }

    MainScreen {
        id: mainScreen

        buttonInsert.onClicked:  {

            insertScreen.firstNameText  = "";
            insertScreen.lastNameText = "";
            insertScreen.addressText = "";
            insertScreen.phoneText = "";
            insertScreen.maritalStatusText = "";

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
