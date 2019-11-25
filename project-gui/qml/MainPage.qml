import Felgo 3.0
import QtQuick 2.0

Page {
  title: "Controlador MIDI"

  Column{
      anchors.centerIn: parent
      VolumeDiag{
          onVolumeChanged: udpSender.sendVolumeChange(newVol)
      }
      StatusInformation{

      }
      Keypad{
          buttonSize: 30
          onButtonPressed: udpSender.sendModeChange(key);
      }
  }
}
