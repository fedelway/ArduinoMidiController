import Felgo 3.0
import QtQuick 2.0
import QtQuick.Controls 2.5

Item {

    property string name: "Volumen"

    width: childrenRect.width
    height: childrenRect.height

    signal volumeChanged(int newVol);

    Dial{
        id: dial
        anchors.centerIn: parent
        stepSize: 1
        from: 0
        to: 127

        implicitWidth: nameText.width + dp(100)
        implicitHeight: nameText.width + dp(100)

        onMoved: volumeChanged(dial.value);

        AppText {
          id: nameText
          text: name;
          anchors.centerIn: parent;
        }
    }

    Connections{
        target: udpSender
        onDataChange: {
            dial.value = volume
        }
    }
}
