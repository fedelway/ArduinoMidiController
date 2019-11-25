import Felgo 3.0
import QtQuick 2.0

Page {
  title: "Controlador MIDI"

  Column{
      anchors.centerIn: parent
      VolumeDiag{
          anchors.horizontalCenter: parent.horizontalCenter;
          onVolumeChanged: console.log(newVol);
      }
      Keypad{
          anchors.horizontalCenter: parent.horizontalCenter
          buttonSize: 30
          onButtonPressed: console.log(key);
      }
  }
}
