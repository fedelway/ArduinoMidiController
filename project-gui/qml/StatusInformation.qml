import Felgo 3.0
import QtQuick 2.0

Item {

    width: childrenRect.width
    height: childrenRect.height

    Column{
        InfoLabel{
            id: modeText
            fieldName: "Modo: "
        }
        InfoLabel{
            id: volText
            fieldName: "Volumen: "
        }
        InfoLabel{
            id: noteText
            fieldName: "Nota: "
        }
        InfoLabel{
            id: scaleText
            fieldName: "Escala: "
        }
    }

    Connections{
        target: udpSender
        onDataChange: {
            volText.change(volume)
            modeText.change(selectedMode)
            noteText.change(currentNote)
            scaleText.change(currentScale)
        }
    }

}
