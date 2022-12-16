import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Dialogs 1.3

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
            onClickEdit: function() {
                stack.pop()
                stack.push(updateScreen_comp)
            }

            onClickInsert: function() {
                stack.pop()
                stack.push(insertScreen_comp)
            }
        }
    }

    Component {
        id: updateScreen_comp
        UpdateScreen {
            id: updateScreen
            onClose: function() {
                stack.pop()
            }
        }
    }

    Component {
        id: insertScreen_comp
        InsertScreen {
            id: insertScreen
            onClose: function() {
                stack.pop();
            }
        }
    }
}
