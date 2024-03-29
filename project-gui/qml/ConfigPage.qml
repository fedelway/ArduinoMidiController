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
            width: Math.min( configPage.width * 0.7, dp(200) )
            placeholderText: "Dirección IP"
        }

        AppTextField{
            id: portInput
            borderWidth: 1
            showClearButton: true
            width: Math.min( configPage.width * 0.7, dp(200) )
            placeholderText: "Puerto"
        }

        AppButton{
            text: "Configurar";
            anchors.horizontalCenter: parent.horizontalCenter;
            onClicked: {
                //Quito focus de los textfields
                ipInput.focus = false
                portInput.focus = false
                //Configuro el sender
                udpSender.setConfiguration(ipInput.text,parseInt(portInput.text,10))
            }
        }
    }

    Connections {
        target: udpSender
        onConfigurationFinished: {
            if(udpSender.valid)
                configPage.finished();
        }

    }
}
