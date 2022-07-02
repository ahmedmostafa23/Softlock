import QtQuick 2.11
import QtQuick.Window 2.12
import QtQuick.Controls 2.14

Window {
    id: root
    width: 640
    height: 480
    visible: true
    title: qsTr("Softlock Encryption")

    Rectangle {
        id: footer
        color: "green"
        opacity: 1
        width: root.width
        height: root.height * 0.1
        anchors.bottom: parent.bottom

        Label {
            id: footer_text
            text: qsTr("Softlock - Information Security Solutions")
            y: footer.height/2 - 7
            x: 25
            color: "white"
            font.family: "Arial"
            font.pointSize: 9
        }
    }

    Button {
        id: browse_button
        text: qsTr("hi")
        x: 100
        y: 100
        width: 100
        height: 25
        flat: false
        display: AbstractButton.TextBesideIcon
        icon.color: "transparent"
        icon.height: 18
        icon.width: 18
        icon.source: url_to_img
    }

//        background: Item object e.g. rectangle. you can give that rectangle borders, a background color, opacity, radius, pretty much everything! but you’ll also need to handle hover/pressed highlight
//    and shit. radius: width/4 makes the sides perfect circles (duh) preferably give an
//        horizontal/verticalPadding: 30
//        left/right/top/bottomPadding: 30
//        padding: 30

//        font.family:
//        font.bold/italic/underline:
//        font.pointSize:

//    and for text styling: (where control is parent id or component id)
//        contentItem: Text {
//                text: control.text
//                font: control.font
//                opacity:
//                color: control.down ? "#17a81a" : "#21be2b"
//                horizontalAlignment: Text.AlignHCenter
//                verticalAlignment: Text.AlignVCenter
//                elide: Text.ElideRight
//        }
//    }
}
