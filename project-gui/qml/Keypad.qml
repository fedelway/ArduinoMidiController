import Felgo 3.0
import QtQuick 2.0
import QtQuick.Layouts 1.12

Item {
    id: keypad

    property int buttonSize: dp(30)
    width: childrenRect.width
    height: childrenRect.height

    signal buttonPressed(string key);

    Column{
        anchors.centerIn: parent;

        Row{
            AppButton{
                text: "1"
                minimumHeight: buttonSize
                minimumWidth: buttonSize
                onClicked: keypad.buttonPressed(text);
            }
            AppButton{
                text: "2"
                minimumHeight: buttonSize
                minimumWidth: buttonSize
                onClicked: keypad.buttonPressed(text);
            }
            AppButton{
                text: "3"
                minimumHeight: buttonSize
                minimumWidth: buttonSize
                onClicked: keypad.buttonPressed(text);
            }
            AppButton{
                text: "A"
                minimumHeight: buttonSize
                minimumWidth: buttonSize
                onClicked: keypad.buttonPressed(text);
            }
        }

        Row{
            AppButton{
                text: "4"
                minimumHeight: buttonSize
                minimumWidth: buttonSize
                onClicked: keypad.buttonPressed(text);
            }
            AppButton{
                text: "5"
                minimumHeight: buttonSize
                minimumWidth: buttonSize
                onClicked: keypad.buttonPressed(text);
            }
            AppButton{
                text: "6"
                minimumHeight: buttonSize
                minimumWidth: buttonSize
                onClicked: keypad.buttonPressed(text);
            }
            AppButton{
                text: "B"
                minimumHeight: buttonSize
                minimumWidth: buttonSize
                onClicked: keypad.buttonPressed(text);
            }
        }

        Row{
            AppButton{
                text: "7"
                minimumHeight: buttonSize
                minimumWidth: buttonSize
                onClicked: keypad.buttonPressed(text);
            }
            AppButton{
                text: "8"
                minimumHeight: buttonSize
                minimumWidth: buttonSize
                onClicked: keypad.buttonPressed(text);
            }
            AppButton{
                text: "9"
                minimumHeight: buttonSize
                minimumWidth: buttonSize
                onClicked: keypad.buttonPressed(text);
            }
            AppButton{
                text: "C"
                minimumHeight: buttonSize
                minimumWidth: buttonSize
                onClicked: keypad.buttonPressed(text);
            }
        }

        Row{
            AppButton{
                text: "*"
                minimumHeight: buttonSize
                minimumWidth: buttonSize
                onClicked: keypad.buttonPressed(text);
            }
            AppButton{
                text: "0"
                minimumHeight: buttonSize
                minimumWidth: buttonSize
                onClicked: keypad.buttonPressed(text);
            }
            AppButton{
                text: "#"
                minimumHeight: buttonSize
                minimumWidth: buttonSize
                onClicked: keypad.buttonPressed(text);
            }
            AppButton{
                text: "D"
                minimumHeight: buttonSize
                minimumWidth: buttonSize
                onClicked: keypad.buttonPressed(text);
            }
        }
    }
}
