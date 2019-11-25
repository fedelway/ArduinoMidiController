import Felgo 3.0
import QtQuick 2.0

Page{
    id: configPage
    title: "Configuración"

    signal finished();

    Column{
        anchors.centerIn: parent

        AppTextField{
            id: ipInput
            borderWidth: 1
            showClearButton: true
            placeholderText: "Dirección IP"
        }

        AppTextField{
            id: portInput
            borderWidth: 1
            showClearButton: true
            placeholderText: "Puerto"
        }

        AppButton{
            text: "Configurar";
            onClicked: {
                //Configuro el sender

                //Marco como finalizado
                configPage.finished()
            }
        }
    }
}
