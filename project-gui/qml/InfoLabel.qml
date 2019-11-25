import Felgo 3.0
import QtQuick 2.0

AppText {
    property string fieldName: "FIELD: "
    text: fieldName
    function change(newText){
        text = fieldName + newText
    }
}
