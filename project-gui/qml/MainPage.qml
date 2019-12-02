import Felgo 3.0
import QtQuick 2.0

Page {
  title: "Controlador MIDI"

  TabControl {
    NavigationItem {
      title: "Controlador"
      icon: IconType.calculator

      ControllerPage{

      }
    }
    NavigationItem {
      title: "Estadísticas"
      icon: IconType.check

      StatsPage{

      }
    }
  }
}
