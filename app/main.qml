import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Dialogs 1.3
import Model 1.0

Window {
    id: window
    width: 640
    height: 540
    visible: true
    title: qsTr("Qml-test")

    maximumHeight: height
    maximumWidth: width

    minimumHeight: height
    minimumWidth: width

    StackView {
        id: stack
        initialItem: mainScreen_comp
        anchors.fill: parent
        onCurrentItemChanged: {
            if(stack.currentItem instanceof MainScreen) {
                stack.currentItem.update()
            }
        }
    }

    Component {
        id: mainScreen_comp
        MainScreen {
            id: mainScreen
            buttonInsert.onClicked:  {
                insertScreen.clearData();
                stack.push( insertScreen )
            }

            onClickUpdate: {
                updateScreen.currentIndex = indexRow;
                updateScreen.updateEmp();
                stack.push( updateScreen );
            }
        }
    }

    Component {
        id: updateScreen_comp
        UpdateScreen {
            id: updateScreen
            onClickedUpdate: {
                if (success) {
                    mainScreen.updateView();
                    stack.pop();
                }
            }
            buttonClose.onClicked: {
                stack.pop();
            }
            visible: false
        }
    }

    Component {
        id: insertScreen_comp
        InsertScreen {
            id: insertScreen
            onClickedSave: {
                if (success) {
                    mainScreen.clickLastEmp();
                    stack.pop();
                }
            }
            buttonClose.onClicked: {
                stack.pop();
            }
            visible: false
        }
    }
}
