import Felgo 3.0
import QtQuick 2.0

App {

    NavigationStack{
        id: mainStack

        ConfigPage{
            onFinished: mainStack.push(mainPage)
        }
    }

    Component{
        id: mainPage
        MainPage{

        }
    }
}
