import Felgo 3.0
import QtQuick 2.0
import QtQuick.Controls 2.5

Item {

    property string name: "Volumen"

    width: childrenRect.width
    height: childrenRect.height

    signal volumeChanged(int newVol);

    AppText {
      text: name;
      anchors.centerIn: parent;
    }

    Dial{
        id: dial
        anchors.centerIn: parent
        stepSize: 1
        from: 0
        to: 127

        onMoved: volumeChanged(dial.value);
    }

}
